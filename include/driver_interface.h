#ifndef DRIVER_INTERFACE_H
#define DRIVER_INTERFACE_H

#define DEVICE_PATH "/dev/industrial_monitor"

#ifdef __KERNEL__

#include <linux/ioctl.h>

#else

#include <sys/ioctl.h>

#endif


/*
 * Sensor data structure
 *
 * The kernel driver does not perform floating-point
 * calculations. These values are only transferred
 * between user space and kernel space.
 */
struct SensorData
{
    double temperature;
    double vibration;
    int rpm;
    double voltage;
    double current_value;
};


/*
 * Driver statistics
 */
struct DriverStats
{
    unsigned long device_opens;
    unsigned long device_closes;
    unsigned long sensor_reads;
    unsigned long sensor_updates;
    unsigned long ioctl_requests;

    unsigned long fault_events;

    unsigned long warning_events;
    unsigned long critical_events;

    int last_fault_severity;

    unsigned long last_fault_time;
};


/*
 * Fault severity values
 */
#define FAULT_NORMAL    0
#define FAULT_WARNING   1
#define FAULT_CRITICAL  2


/*
 * IOCTL definitions
 */

#define IOCTL_MAGIC 'I'


/* Get driver status */
#define IOCTL_GET_STATUS \
    _IOR(IOCTL_MAGIC, 1, int)


/* Set driver mode */
#define IOCTL_SET_MODE \
    _IOW(IOCTL_MAGIC, 2, int)


/* Reset driver */
#define IOCTL_RESET \
    _IO(IOCTL_MAGIC, 3)


/* Get sensor data */
#define IOCTL_GET_SENSOR_DATA \
    _IOR(IOCTL_MAGIC, 4, struct SensorData)


/* Set sensor data */
#define IOCTL_SET_SENSOR_DATA \
    _IOW(IOCTL_MAGIC, 5, struct SensorData)


/* Get driver statistics */
#define IOCTL_GET_STATS \
    _IOR(IOCTL_MAGIC, 6, struct DriverStats)


/* Report fault severity */
#define IOCTL_REPORT_FAULT \
    _IOW(IOCTL_MAGIC, 7, int)


#endif
