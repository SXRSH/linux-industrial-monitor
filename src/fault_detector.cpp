#include "fault_detector.h"

Severity checkTemperature(double temperature)
{
    if (temperature >= 95.0)
        return Severity::CRITICAL;

    if (temperature >= 75.0)
        return Severity::WARNING;

    return Severity::NORMAL;
}

Severity checkVibration(double vibration)
{
    if (vibration >= 8.0)
        return Severity::CRITICAL;

    if (vibration >= 5.0)
        return Severity::WARNING;

    return Severity::NORMAL;
}

Severity checkRPM(int rpm)
{
    if (rpm >= 3600)
        return Severity::CRITICAL;

    if (rpm >= 3000)
        return Severity::WARNING;

    return Severity::NORMAL;
}

Severity checkVoltage(double voltage)
{
    if (voltage >= 255.0)
        return Severity::CRITICAL;

    if (voltage >= 240.0)
        return Severity::WARNING;

    return Severity::NORMAL;
}

Severity checkCurrent(double current)
{
    if (current >= 16.0)
        return Severity::CRITICAL;

    if (current >= 10.0)
        return Severity::WARNING;

    return Severity::NORMAL;
}

Severity getOverallSeverity(
    Severity temperature,
    Severity vibration,
    Severity rpm,
    Severity voltage,
    Severity current)
{
    Severity values[] =
    {
        temperature,
        vibration,
        rpm,
        voltage,
        current
    };

    Severity overall = Severity::NORMAL;

    for (Severity value : values)
    {
        if (value == Severity::CRITICAL)
            return Severity::CRITICAL;

        if (value == Severity::WARNING)
            overall = Severity::WARNING;
    }

    return overall;
}

const char* severityToString(Severity severity)
{
    switch (severity)
    {
        case Severity::NORMAL:
            return "NORMAL";

        case Severity::WARNING:
            return "WARNING";

        case Severity::CRITICAL:
            return "CRITICAL";

        default:
            return "UNKNOWN";
    }
}
