#ifndef INDUSTRIAL_MONITOR_H
#define INDUSTRIAL_MONITOR_H

#include <string>

enum class FaultLevel
{
    NORMAL,
    WARNING,
    CRITICAL
};

struct SensorData
{
    double temperature;
    double vibration;
    int rpm;
    double voltage;
    double current;
};

struct FaultStatus
{
    FaultLevel temperature_status;
    FaultLevel vibration_status;
    FaultLevel rpm_status;
    FaultLevel voltage_status;
    FaultLevel current_status;

    FaultLevel overall_status;
};

class IndustrialMonitor
{
public:
    IndustrialMonitor();

    FaultStatus analyze(const SensorData& data) const;

    std::string faultLevelToString(FaultLevel level) const;

private:
    FaultLevel checkTemperature(double temperature) const;
    FaultLevel checkVibration(double vibration) const;
    FaultLevel checkRPM(int rpm) const;
    FaultLevel checkVoltage(double voltage) const;
    FaultLevel checkCurrent(double current) const;

    FaultLevel determineOverallStatus(
        FaultLevel temperatureStatus,
        FaultLevel vibrationStatus,
        FaultLevel rpmStatus,
        FaultLevel voltageStatus,
        FaultLevel currentStatus
    ) const;
};

#endif
