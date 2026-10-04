#include "industrial_monitor.h"

IndustrialMonitor::IndustrialMonitor()
{
}

FaultLevel IndustrialMonitor::checkTemperature(double temperature) const
{
    if (temperature > 90.0)
        return FaultLevel::CRITICAL;

    if (temperature >= 70.0)
        return FaultLevel::WARNING;

    return FaultLevel::NORMAL;
}

FaultLevel IndustrialMonitor::checkVibration(double vibration) const
{
    if (vibration > 7.0)
        return FaultLevel::CRITICAL;

    if (vibration >= 4.0)
        return FaultLevel::WARNING;

    return FaultLevel::NORMAL;
}

FaultLevel IndustrialMonitor::checkRPM(int rpm) const
{
    if (rpm > 3500)
        return FaultLevel::CRITICAL;

    if (rpm > 3000)
        return FaultLevel::WARNING;

    return FaultLevel::NORMAL;
}

FaultLevel IndustrialMonitor::checkVoltage(double voltage) const
{
    if (voltage < 200.0 || voltage > 250.0)
        return FaultLevel::CRITICAL;

    if (voltage < 210.0 || voltage > 240.0)
        return FaultLevel::WARNING;

    return FaultLevel::NORMAL;
}

FaultLevel IndustrialMonitor::checkCurrent(double current) const
{
    if (current > 15.0)
        return FaultLevel::CRITICAL;

    if (current >= 10.0)
        return FaultLevel::WARNING;

    return FaultLevel::NORMAL;
}

FaultLevel IndustrialMonitor::determineOverallStatus(
    FaultLevel temperatureStatus,
    FaultLevel vibrationStatus,
    FaultLevel rpmStatus,
    FaultLevel voltageStatus,
    FaultLevel currentStatus) const
{
    FaultLevel statuses[] = {
        temperatureStatus,
        vibrationStatus,
        rpmStatus,
        voltageStatus,
        currentStatus
    };

    FaultLevel overall = FaultLevel::NORMAL;

    for (FaultLevel status : statuses)
    {
        if (status == FaultLevel::CRITICAL)
            return FaultLevel::CRITICAL;

        if (status == FaultLevel::WARNING)
            overall = FaultLevel::WARNING;
    }

    return overall;
}

FaultStatus IndustrialMonitor::analyze(const SensorData& data) const
{
    FaultStatus status;

    status.temperature_status = checkTemperature(data.temperature);
    status.vibration_status = checkVibration(data.vibration);
    status.rpm_status = checkRPM(data.rpm);
    status.voltage_status = checkVoltage(data.voltage);
    status.current_status = checkCurrent(data.current);

    status.overall_status = determineOverallStatus(
        status.temperature_status,
        status.vibration_status,
        status.rpm_status,
        status.voltage_status,
        status.current_status
    );

    return status;
}

std::string IndustrialMonitor::faultLevelToString(FaultLevel level) const
{
    switch (level)
    {
        case FaultLevel::NORMAL:
            return "NORMAL";

        case FaultLevel::WARNING:
            return "WARNING";

        case FaultLevel::CRITICAL:
            return "CRITICAL";
    }

    return "UNKNOWN";
}
