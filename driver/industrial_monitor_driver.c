#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#include <linux/timekeeping.h>

#include "../include/driver_interface.h"


#define DEVICE_NAME "industrial_monitor"
#define CLASS_NAME  "industrial_monitor_class"


/*
 * Driver state
 */
static int driver_status = 1;
static int driver_mode = 0;


/*
 * Sensor data stored by the kernel driver.
 */
static struct SensorData current_sensor_data;


/*
 * Driver statistics
 */
static struct DriverStats statistics;


/*
 * Character device variables
 */
static dev_t device_number;

static struct cdev industrial_cdev;

static struct class *industrial_class;

static struct device *industrial_device;


/*
 * Protect shared driver state.
 */
static DEFINE_MUTEX(driver_mutex);


/*
 * DEVICE OPEN
 */
static int industrial_open(
    struct inode *inode,
    struct file *file)
{
    mutex_lock(&driver_mutex);

    statistics.device_opens++;

    mutex_unlock(&driver_mutex);

    pr_info(
        "industrial_monitor: device opened\n"
    );

    return 0;
}


/*
 * DEVICE READ
 */
static ssize_t industrial_read(
    struct file *file,
    char __user *buffer,
    size_t length,
    loff_t *offset)
{
    const char response[] =
        "Industrial Monitor Driver Active\n";

    size_t response_length =
        sizeof(response) - 1;


    /*
     * Prevent repeated reads of the same message.
     */
    if (*offset >= response_length)
    {
        return 0;
    }


    if (length > response_length - *offset)
    {
        length = response_length - *offset;
    }


    if (copy_to_user(
        buffer,
        response + *offset,
        length))
    {
        return -EFAULT;
    }


    *offset += length;


    mutex_lock(&driver_mutex);

    statistics.sensor_reads++;

    mutex_unlock(&driver_mutex);


    pr_info(
        "industrial_monitor: device read\n"
    );


    return length;
}


/*
 * DEVICE RELEASE
 */
static int industrial_release(
    struct inode *inode,
    struct file *file)
{
    mutex_lock(&driver_mutex);

    statistics.device_closes++;

    mutex_unlock(&driver_mutex);


    pr_info(
        "industrial_monitor: device closed\n"
    );

    return 0;
}


/*
 * IOCTL HANDLER
 */
static long industrial_ioctl(
    struct file *file,
    unsigned int command,
    unsigned long argument)
{
    int mode;
    int fault_severity;

    struct DriverStats stats_copy;


    /*
     * Count every IOCTL request.
     */
    mutex_lock(&driver_mutex);

    statistics.ioctl_requests++;

    mutex_unlock(&driver_mutex);


    switch (command)
    {

        /*
         * GET DRIVER STATUS
         */
        case IOCTL_GET_STATUS:

            mutex_lock(&driver_mutex);

            if (copy_to_user(
                (int __user *)argument,
                &driver_status,
                sizeof(driver_status)))
            {
                mutex_unlock(&driver_mutex);
                return -EFAULT;
            }

            mutex_unlock(&driver_mutex);


            pr_info(
                "industrial_monitor: status requested = %d\n",
                driver_status
            );

            break;


        /*
         * SET DRIVER MODE
         */
        case IOCTL_SET_MODE:

            if (copy_from_user(
                &mode,
                (int __user *)argument,
                sizeof(mode)))
            {
                return -EFAULT;
            }


            mutex_lock(&driver_mutex);

            driver_mode = mode;

            mutex_unlock(&driver_mutex);


            pr_info(
                "industrial_monitor: mode changed to %d\n",
                driver_mode
            );

            break;


        /*
         * RESET DRIVER
         */
        case IOCTL_RESET:

            mutex_lock(&driver_mutex);

            driver_status = 1;
            driver_mode = 0;

            memset(
                &current_sensor_data,
                0,
                sizeof(current_sensor_data)
            );

            statistics.sensor_reads = 0;
            statistics.sensor_updates = 0;
            statistics.ioctl_requests = 0;

            statistics.fault_events = 0;
            statistics.warning_events = 0;
            statistics.critical_events = 0;

            statistics.last_fault_severity =
                FAULT_NORMAL;

            statistics.last_fault_time = 0;

            mutex_unlock(&driver_mutex);


            pr_info(
                "industrial_monitor: driver reset\n"
            );

            break;


        /*
         * GET SENSOR DATA
         */
        case IOCTL_GET_SENSOR_DATA:

            mutex_lock(&driver_mutex);

            if (copy_to_user(
                (struct SensorData __user *)argument,
                &current_sensor_data,
                sizeof(current_sensor_data)))
            {
                mutex_unlock(&driver_mutex);
                return -EFAULT;
            }

            mutex_unlock(&driver_mutex);


            pr_info(
                "industrial_monitor: sensor data requested\n"
            );

            break;


        /*
         * SET SENSOR DATA
         */
        case IOCTL_SET_SENSOR_DATA:

            if (copy_from_user(
                &current_sensor_data,
                (struct SensorData __user *)argument,
                sizeof(current_sensor_data)))
            {
                return -EFAULT;
            }


            mutex_lock(&driver_mutex);

            statistics.sensor_updates++;

            mutex_unlock(&driver_mutex);


            pr_info(
                "industrial_monitor: sensor data updated\n"
            );

            break;


        /*
         * GET DRIVER STATISTICS
         */
        case IOCTL_GET_STATS:

            mutex_lock(&driver_mutex);

            stats_copy = statistics;

            mutex_unlock(&driver_mutex);


            if (copy_to_user(
                (struct DriverStats __user *)argument,
                &stats_copy,
                sizeof(stats_copy)))
            {
                return -EFAULT;
            }


            pr_info(
                "industrial_monitor: statistics requested\n"
            );

            break;


        /*
         * REPORT FAULT
         *
         * Fault events are generated only when
         * the reported severity changes.
         */
        case IOCTL_REPORT_FAULT:

            if (copy_from_user(
                &fault_severity,
                (int __user *)argument,
                sizeof(fault_severity)))
            {
                return -EFAULT;
            }


            /*
             * Validate severity.
             */
            if (fault_severity != FAULT_NORMAL &&
                fault_severity != FAULT_WARNING &&
                fault_severity != FAULT_CRITICAL)
            {
                pr_err(
                    "industrial_monitor: invalid fault severity: %d\n",
                    fault_severity
                );

                return -EINVAL;
            }


            mutex_lock(&driver_mutex);


            /*
             * NORMAL CONDITION
             */
            if (fault_severity == FAULT_NORMAL)
            {
                /*
                 * Only report recovery when the
                 * previous state was a fault.
                 */
                if (statistics.last_fault_severity !=
                    FAULT_NORMAL)
                {
                    pr_info(
                        "industrial_monitor: equipment recovered to NORMAL\n"
                    );
                }

                statistics.last_fault_severity =
                    FAULT_NORMAL;

                statistics.last_fault_time = 0;


                mutex_unlock(&driver_mutex);

                break;
            }


            /*
             * WARNING CONDITION
             */
            if (fault_severity == FAULT_WARNING)
            {
                /*
                 * Generate an event only when
                 * entering WARNING state.
                 */
                if (statistics.last_fault_severity !=
                    FAULT_WARNING)
                {
                    statistics.fault_events++;

                    statistics.warning_events++;

                    statistics.last_fault_time =
                        ktime_get_real_seconds();


                    pr_info(
                        "industrial_monitor: NEW WARNING fault event\n"
                    );
                }
                else
                {
                    /*
                     * Same warning condition continues.
                     */
                    pr_info(
                        "industrial_monitor: WARNING condition continues\n"
                    );
                }


                statistics.last_fault_severity =
                    FAULT_WARNING;


                mutex_unlock(&driver_mutex);

                break;
            }


            /*
             * CRITICAL CONDITION
             */
            if (fault_severity == FAULT_CRITICAL)
            {
                /*
                 * Generate an event only when
                 * entering CRITICAL state.
                 */
                if (statistics.last_fault_severity !=
                    FAULT_CRITICAL)
                {
                    statistics.fault_events++;

                    statistics.critical_events++;

                    statistics.last_fault_time =
                        ktime_get_real_seconds();


                    pr_info(
                        "industrial_monitor: NEW CRITICAL fault event\n"
                    );
                }
                else
                {
                    /*
                     * Same critical condition continues.
                     */
                    pr_info(
                        "industrial_monitor: CRITICAL condition continues\n"
                    );
                }


                statistics.last_fault_severity =
                    FAULT_CRITICAL;


                mutex_unlock(&driver_mutex);

                break;
            }


            mutex_unlock(&driver_mutex);

            break;


        /*
         * UNKNOWN IOCTL
         */
        default:

            pr_err(
                "industrial_monitor: unknown ioctl command: 0x%x\n",
                command
            );

            return -EINVAL;
    }


    return 0;
}


/*
 * FILE OPERATIONS
 */
static const struct file_operations industrial_fops =
{
    .owner = THIS_MODULE,

    .open = industrial_open,

    .read = industrial_read,

    .release = industrial_release,

    .unlocked_ioctl = industrial_ioctl
};


/*
 * MODULE INITIALIZATION
 */
static int __init industrial_monitor_init(void)
{
    int result;


    pr_info(
        "industrial_monitor: initializing driver\n"
    );


    /*
     * Initialize driver statistics.
     */
    memset(
        &statistics,
        0,
        sizeof(statistics)
    );


    statistics.last_fault_severity =
        FAULT_NORMAL;

    statistics.last_fault_time = 0;


    /*
     * Initialize sensor data.
     */
    memset(
        &current_sensor_data,
        0,
        sizeof(current_sensor_data)
    );


    /*
     * Allocate character device number.
     */
    result = alloc_chrdev_region(
        &device_number,
        0,
        1,
        DEVICE_NAME
    );

    if (result < 0)
    {
        pr_err(
            "industrial_monitor: failed to allocate device number\n"
        );

        return result;
    }


    /*
     * Initialize character device.
     */
    cdev_init(
        &industrial_cdev,
        &industrial_fops
    );

    industrial_cdev.owner =
        THIS_MODULE;


    /*
     * Add character device.
     */
    result = cdev_add(
        &industrial_cdev,
        device_number,
        1
    );

    if (result < 0)
    {
        pr_err(
            "industrial_monitor: failed to add cdev\n"
        );

        unregister_chrdev_region(
            device_number,
            1
        );

        return result;
    }


    /*
     * Create device class.
     */
    industrial_class =
        class_create(CLASS_NAME);

    if (IS_ERR(industrial_class))
    {
        pr_err(
            "industrial_monitor: failed to create class\n"
        );

        cdev_del(
            &industrial_cdev
        );

        unregister_chrdev_region(
            device_number,
            1
        );

        return PTR_ERR(
            industrial_class
        );
    }


    /*
     * Create /dev/industrial_monitor.
     */
    industrial_device =
        device_create(
            industrial_class,
            NULL,
            device_number,
            NULL,
            DEVICE_NAME
        );

    if (IS_ERR(industrial_device))
    {
        pr_err(
            "industrial_monitor: failed to create device\n"
        );

        class_destroy(
            industrial_class
        );

        cdev_del(
            &industrial_cdev
        );

        unregister_chrdev_region(
            device_number,
            1
        );

        return PTR_ERR(
            industrial_device
        );
    }


    pr_info(
        "industrial_monitor: driver loaded successfully\n"
    );

    pr_info(
        "industrial_monitor: device /dev/%s created\n",
        DEVICE_NAME
    );


    return 0;
}


/*
 * MODULE CLEANUP
 */
static void __exit industrial_monitor_exit(void)
{
    device_destroy(
        industrial_class,
        device_number
    );

    class_destroy(
        industrial_class
    );

    cdev_del(
        &industrial_cdev
    );

    unregister_chrdev_region(
        device_number,
        1
    );


    pr_info(
        "industrial_monitor: driver unloaded\n"
    );
}


module_init(
    industrial_monitor_init
);

module_exit(
    industrial_monitor_exit
);


MODULE_LICENSE("GPL");

MODULE_AUTHOR(
    "Industrial Monitor Project"
);

MODULE_DESCRIPTION(
    "Linux Industrial Equipment Monitoring Character Driver"
);

MODULE_VERSION("1.0");
