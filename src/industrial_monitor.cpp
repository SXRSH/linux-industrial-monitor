#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cerrno>
#include <cstring>
#include <csignal>
#include <chrono>
#include <thread>
#include <ctime>

#include "driver_interface.h"
#include "fault_detector.h"

static volatile sig_atomic_t running = 1;

const char* LOG_FILE = "logs/industrial_monitor.log";

void handleSignal(int signal)
{
    if (signal == SIGINT)
    {
        running = 0;
    }
}

std::string getTimestamp()
{
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    char buffer[32];

    std::strftime(
        buffer,
        sizeof(buffer),
        "%Y-%m-%d %H:%M:%S",
        localTime
    );

    return std::string(buffer);
}

void writeLog(const std::string& message)
{
    std::ofstream logFile(
        LOG_FILE,
        std::ios::app
    );

    if (logFile)
    {
        logFile
            << "["
            << getTimestamp()
            << "] "
            << message
            << "\n";
    }
}

void printSeparator()
{
    std::cout
        << "----------------------------------------\n";
}

void printSensorData(const SensorData& data)
{
    Severity temperatureStatus =
        checkTemperature(data.temperature);

    Severity vibrationStatus =
        checkVibration(data.vibration);

    Severity rpmStatus =
        checkRPM(data.rpm);

    Severity voltageStatus =
        checkVoltage(data.voltage);

    Severity currentStatus =
        checkCurrent(data.current_value);

    Severity overallStatus =
        getOverallSeverity(
            temperatureStatus,
            vibrationStatus,
            rpmStatus,
            voltageStatus,
            currentStatus
        );

    std::cout << std::fixed
              << std::setprecision(2);

    std::cout << "Temperature : "
              << data.temperature
              << " C ["
              << severityToString(temperatureStatus)
              << "]\n";

    std::cout << "Vibration   : "
              << data.vibration
              << " mm/s ["
              << severityToString(vibrationStatus)
              << "]\n";

    std::cout << "Motor RPM   : "
              << data.rpm
              << " RPM ["
              << severityToString(rpmStatus)
              << "]\n";

    std::cout << "Voltage     : "
              << data.voltage
              << " V ["
              << severityToString(voltageStatus)
              << "]\n";

    std::cout << "Current     : "
              << data.current_value
              << " A ["
              << severityToString(currentStatus)
              << "]\n";

    printSeparator();

    std::cout << "Overall Status: "
              << severityToString(overallStatus)
              << "\n";
}

bool sendSensorData(
    int fd,
    const SensorData& data)
{
    if (ioctl(
        fd,
        IOCTL_SET_SENSOR_DATA,
        &data) < 0)
    {
        std::cerr
            << "ERROR: Unable to send sensor data: "
            << std::strerror(errno)
            << "\n";

        writeLog(
            "ERROR: Failed to send sensor data"
        );

        return false;
    }

    return true;
}

bool receiveSensorData(
    int fd,
    SensorData& data)
{
    if (ioctl(
        fd,
        IOCTL_GET_SENSOR_DATA,
        &data) < 0)
    {
        std::cerr
            << "ERROR: Unable to retrieve sensor data: "
            << std::strerror(errno)
            << "\n";

        writeLog(
            "ERROR: Failed to retrieve sensor data"
        );

        return false;
    }

    return true;
}

Severity getOverallStatus(
    const SensorData& data)
{
    return getOverallSeverity(
        checkTemperature(data.temperature),
        checkVibration(data.vibration),
        checkRPM(data.rpm),
        checkVoltage(data.voltage),
        checkCurrent(data.current_value)
    );
}

bool reportFault(
    int fd,
    Severity severity)
{
    int faultSeverity = FAULT_NORMAL;

    if (severity == Severity::WARNING)
    {
        faultSeverity = FAULT_WARNING;
    }
    else if (severity == Severity::CRITICAL)
    {
        faultSeverity = FAULT_CRITICAL;
    }

    if (ioctl(
        fd,
        IOCTL_REPORT_FAULT,
        &faultSeverity) < 0)
    {
        std::cerr
            << "ERROR: Unable to report fault: "
            << std::strerror(errno)
            << "\n";

        writeLog(
            "ERROR: Failed to report fault to kernel"
        );

        return false;
    }

    return true;
}

void printStatusMessage(
    Severity severity)
{
    if (severity == Severity::NORMAL)
    {
        std::cout
            << "[STATUS] Equipment operating normally\n";

        writeLog(
            "Equipment operating normally"
        );
    }
    else if (severity == Severity::WARNING)
    {
        std::cout
            << "[WARNING] Equipment requires attention\n";

        writeLog(
            "WARNING: Equipment requires attention"
        );
    }
    else if (severity == Severity::CRITICAL)
    {
        std::cout
            << "[CRITICAL] Immediate equipment attention required\n";

        writeLog(
            "CRITICAL: Immediate equipment attention required"
        );
    }
}

void printStatistics(int fd)
{
    DriverStats stats{};

    if (ioctl(
        fd,
        IOCTL_GET_STATS,
        &stats) < 0)
    {
        std::cerr
            << "ERROR: Unable to retrieve driver statistics: "
            << std::strerror(errno)
            << "\n";

        writeLog(
            "ERROR: Unable to retrieve driver statistics"
        );

        return;
    }

    std::cout << "\n";
    printSeparator();

    std::cout
        << " DRIVER STATISTICS\n";

    printSeparator();

    std::cout
        << "Device Opens       : "
        << stats.device_opens
        << "\n";

    std::cout
        << "Device Closes      : "
        << stats.device_closes
        << "\n";

    std::cout
        << "Sensor Reads       : "
        << stats.sensor_reads
        << "\n";

    std::cout
        << "Sensor Updates     : "
        << stats.sensor_updates
        << "\n";

    std::cout
        << "IOCTL Requests     : "
        << stats.ioctl_requests
        << "\n";

    std::cout
        << "Fault Events       : "
        << stats.fault_events
        << "\n";

    std::cout
        << "Warning Events     : "
        << stats.warning_events
        << "\n";

    std::cout
        << "Critical Events    : "
        << stats.critical_events
        << "\n";

    std::cout
        << "Last Fault Severity: "
        << stats.last_fault_severity
        << "\n";

    std::cout
        << "Last Fault Time    : "
        << stats.last_fault_time
        << "\n";

    printSeparator();

    std::ostringstream log;

    log
        << "Statistics - Opens: "
        << stats.device_opens
        << ", Closes: "
        << stats.device_closes
        << ", Reads: "
        << stats.sensor_reads
        << ", Updates: "
        << stats.sensor_updates
        << ", IOCTLs: "
        << stats.ioctl_requests
        << ", Faults: "
        << stats.fault_events
        << ", Warnings: "
        << stats.warning_events
        << ", Critical: "
        << stats.critical_events;

    writeLog(log.str());
}

int main()
{
    std::signal(SIGINT, handleSignal);

    writeLog(
        "========================================"
    );

    writeLog(
        "Industrial Equipment Monitor started"
    );

    std::cout
        << "\n========================================\n";

    std::cout
        << " INDUSTRIAL EQUIPMENT MONITOR\n";

    std::cout
        << "========================================\n";

    std::cout
        << "[INFO] Automatic simulation mode\n";

    std::cout
        << "[INFO] Press Ctrl+C to stop\n\n";

    int fd = open(
        DEVICE_PATH,
        O_RDWR
    );

    if (fd < 0)
    {
        std::cerr
            << "ERROR: Unable to open "
            << DEVICE_PATH
            << "\n";

        std::cerr
            << "Reason: "
            << std::strerror(errno)
            << "\n";

        writeLog(
            "ERROR: Unable to open character device"
        );

        return 1;
    }

    std::cout
        << "[OK] Character device opened\n";

    writeLog(
        "Character device opened successfully"
    );

    int mode = 1;

    if (ioctl(
        fd,
        IOCTL_SET_MODE,
        &mode) < 0)
    {
        std::cerr
            << "ERROR: Unable to set driver mode\n";

        writeLog(
            "ERROR: Unable to set monitoring mode"
        );

        close(fd);

        return 1;
    }

    std::cout
        << "[OK] Monitoring mode enabled\n";

    writeLog(
        "Monitoring mode enabled"
    );

    SensorData scenarios[] =
    {
        {
            65.0,
            3.0,
            2200,
            230.0,
            7.0
        },

        {
            80.0,
            5.0,
            3200,
            245.0,
            12.0
        },

        {
            100.0,
            9.0,
            3800,
            260.0,
            18.0
        }
    };

    int scenario = 0;
    unsigned long cycle = 0;

    while (running)
    {
        cycle++;

        std::cout
            << "\n========================================\n";

        std::cout
            << " MONITORING CYCLE "
            << cycle
            << "\n";

        std::cout
            << "========================================\n";

        std::ostringstream cycleLog;

        cycleLog
            << "Monitoring cycle "
            << cycle
            << " started";

        writeLog(cycleLog.str());

        SensorData input =
            scenarios[scenario];

        if (!sendSensorData(
            fd,
            input))
        {
            break;
        }

        std::cout
            << "[OK] Sensor data sent to kernel\n";

        SensorData data{};

        if (!receiveSensorData(
            fd,
            data))
        {
            break;
        }

        std::cout
            << "[OK] Sensor data received from kernel\n\n";

        printSensorData(data);

        Severity overallStatus =
            getOverallStatus(data);

        std::ostringstream sensorLog;

        sensorLog
            << std::fixed
            << std::setprecision(2)
            << "Cycle "
            << cycle
            << " - Temperature="
            << data.temperature
            << "C, Vibration="
            << data.vibration
            << "mm/s, RPM="
            << data.rpm
            << ", Voltage="
            << data.voltage
            << "V, Current="
            << data.current_value
            << "A, Status="
            << severityToString(overallStatus);

        writeLog(sensorLog.str());

        if (reportFault(
            fd,
            overallStatus))
        {
            std::cout
                << "[OK] Fault status reported to kernel\n";
        }

        printStatusMessage(
            overallStatus
        );

        scenario++;

        if (scenario >= 3)
        {
            scenario = 0;
        }

        if (running)
        {
            std::cout
                << "\n[INFO] Next monitoring cycle "
                   "in 3 seconds...\n";

            std::this_thread::sleep_for(
                std::chrono::seconds(3)
            );
        }
    }

    std::cout
        << "\n\n========================================\n";

    std::cout
        << " MONITORING STOPPED\n";

    std::cout
        << "========================================\n";

    writeLog(
        "Monitoring stopped by user"
    );

    printStatistics(fd);

    if (ioctl(
        fd,
        IOCTL_RESET) == 0)
    {
        std::cout
            << "[OK] Driver reset successful\n";

        writeLog(
            "Driver reset successful"
        );
    }
    else
    {
        std::cerr
            << "[WARNING] Driver reset failed: "
            << std::strerror(errno)
            << "\n";

        writeLog(
            "WARNING: Driver reset failed"
        );
    }

    close(fd);

    std::cout
        << "[OK] Device closed successfully\n";

    writeLog(
        "Character device closed"
    );

    writeLog(
        "Industrial Equipment Monitor session completed"
    );

    writeLog(
        "========================================"
    );

    std::cout
        << "\n========================================\n";

    std::cout
        << " MONITORING SESSION COMPLETED\n";

    std::cout
        << "========================================\n";

    return 0;
}
