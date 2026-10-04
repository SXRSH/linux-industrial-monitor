#ifndef SENSOR_SIMULATOR_H
#define SENSOR_SIMULATOR_H

#include "industrial_monitor.h"

class SensorSimulator
{
public:
    SensorSimulator();

    SensorData generateNormalData();
    SensorData generateWarningData();
    SensorData generateCriticalData();
};

#endif
