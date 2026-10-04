#include <iostream>
#include <iomanip>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cerrno>
#include <cstring>

#include "driver_interface.h"

int main()
{
    std::cout << "\n========================================\n";
    std::cout << " INDUSTRIAL MONITOR DRIVER TEST\n";
    std::cout << "========================================\n";

    /*
     * Open the character device
     */
    int fd = open(DEVICE_PATH, O_RDWR);

    if (fd < 0)
    {
        std::cerr << "Failed to open device: "
                  << std::strerror(errno)
                  << "\n";

        return 1;
    }

    std::cout << "[OK] Device opened successfully\n";


    /*
     * Test read()
     */
    char buffer[128] = {0};

    ssize_t bytesRead = read(
        fd,
        buffer,
        sizeof(buffer) - 1
    );

    if (bytesRead < 0)
    {
        std::cerr << "Read failed: "
                  << std::strerror(errno)
                  << "\n";

        close(fd);

        return 1;
    }

    buffer[bytesRead] = '\0';

    std::cout << "[OK] Driver response:\n";
    std::cout << buffer;


    /*
     * Get driver status
     */
    int status = 0;

    if (ioctl(
        fd,
        IOCTL_GET_STATUS,
        &status) < 0)
    {
        std::cerr << "IOCTL_GET_STATUS failed: "
                  << std::strerror(errno)
                  << "\n";

        close(fd);

        return 1;
    }

    std::cout << "[OK] Driver status: "
              << status
              << "\n";


    /*
     * Set driver mode
     */
    int mode = 1;

    if (ioctl(
        fd,
        IOCTL_SET_MODE,
        &mode) < 0)
    {
        std::cerr << "IOCTL_SET_MODE failed: "
                  << std::strerror(errno)
                  << "\n";

        close(fd);

        return 1;
    }

    std::cout << "[OK] Driver mode changed to: "
              << mode
              << "\n";


    /*
     * Prepare sensor data
     *
     * Sensor values are supplied from
     * user space to the kernel driver.
     */
    SensorData inputData{};

    inputData.temperature = 65.0;
    inputData.vibration = 3.0;
    inputData.rpm = 2200;
    inputData.voltage = 230.0;
    inputData.current_value = 7.0;


    /*
     * Send sensor data to kernel
     */
    if (ioctl(
        fd,
        IOCTL_SET_SENSOR_DATA,
        &inputData) < 0)
    {
        std::cerr << "IOCTL_SET_SENSOR_DATA failed: "
                  << std::strerror(errno)
                  << "\n";

        close(fd);

        return 1;
    }

    std::cout << "[OK] Sensor data sent to kernel driver\n";


    /*
     * Get sensor data back from kernel
     */
    SensorData data{};

    if (ioctl(
        fd,
        IOCTL_GET_SENSOR_DATA,
        &data) < 0)
    {
        std::cerr << "IOCTL_GET_SENSOR_DATA failed: "
                  << std::strerror(errno)
                  << "\n";

        close(fd);

        return 1;
    }

    std::cout << "[OK] Sensor data received from kernel\n";


    /*
     * Display sensor data
     */
    std::cout << "\n----------------------------------------\n";
    std::cout << " SENSOR DATA FROM KERNEL DRIVER\n";
    std::cout << "----------------------------------------\n";

    std::cout << std::fixed
              << std::setprecision(2);

    std::cout << "Temperature : "
              << data.temperature
              << " C\n";

    std::cout << "Vibration   : "
              << data.vibration
              << " mm/s\n";

    std::cout << "Motor RPM   : "
              << data.rpm
              << " RPM\n";

    std::cout << "Voltage     : "
              << data.voltage
              << " V\n";

    std::cout << "Current     : "
              << data.current_value
              << " A\n";

    std::cout << "----------------------------------------\n";


    /*
     * Get driver statistics
     */
    DriverStats stats{};

    if (ioctl(
        fd,
        IOCTL_GET_STATS,
        &stats) < 0)
    {
        std::cerr << "IOCTL_GET_STATS failed: "
                  << std::strerror(errno)
                  << "\n";

        close(fd);

        return 1;
    }


    /*
     * Display driver statistics
     */
    std::cout << "\n----------------------------------------\n";
    std::cout << " DRIVER STATISTICS\n";
    std::cout << "----------------------------------------\n";

    std::cout << "Device Opens     : "
              << stats.device_opens
              << "\n";

    std::cout << "Device Closes    : "
              << stats.device_closes
              << "\n";

    std::cout << "Sensor Reads     : "
              << stats.sensor_reads
              << "\n";

    std::cout << "Sensor Updates   : "
              << stats.sensor_updates
              << "\n";

    std::cout << "IOCTL Requests   : "
              << stats.ioctl_requests
              << "\n";

    std::cout << "Fault Events     : "
              << stats.fault_events
              << "\n";

    std::cout << "----------------------------------------\n";


    /*
     * Reset driver
     */
    if (ioctl(
        fd,
        IOCTL_RESET) < 0)
    {
        std::cerr << "IOCTL_RESET failed: "
                  << std::strerror(errno)
                  << "\n";

        close(fd);

        return 1;
    }

    std::cout << "[OK] Driver reset successful\n";


    /*
     * Close device
     */
    close(fd);

    std::cout << "[OK] Device closed successfully\n";


    std::cout << "\n========================================\n";
    std::cout << " DRIVER SENSOR TEST COMPLETED\n";
    std::cout << "========================================\n";

    return 0;
}
