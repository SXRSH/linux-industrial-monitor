#ifndef FAULT_DETECTOR_H
#define FAULT_DETECTOR_H

#include "driver_interface.h"

enum class Severity
{
    NORMAL,
    WARNING,
    CRITICAL
};

Severity checkTemperature(double temperature);

Severity checkVibration(double vibration);

Severity checkRPM(int rpm);

Severity checkVoltage(double voltage);

Severity checkCurrent(double current);

Severity getOverallSeverity(
    Severity temperature,
    Severity vibration,
    Severity rpm,
    Severity voltage,
    Severity current
);

const char* severityToString(Severity severity);

#endif
