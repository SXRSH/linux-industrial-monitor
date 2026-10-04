#include "sensor_simulator.h"

SensorSimulator::SensorSimulator()
{
}

SensorData SensorSimulator::generateNormalData()
{
    SensorData data;

    data.temperature = 65.0;
    data.vibration = 3.0;
    data.rpm = 2200;
    data.voltage = 230.0;
    data.current = 7.0;

    return data;
}

SensorData SensorSimulator::generateWarningData()
{
    SensorData data;

    data.temperature = 80.0;
    data.vibration = 5.0;
    data.rpm = 3200;
    data.voltage = 245.0;
    data.current = 12.0;

    return data;
}

SensorData SensorSimulator::generateCriticalData()
{
    SensorData data;

    data.temperature = 100.0;
    data.vibration = 9.0;
    data.rpm = 3800;
    data.voltage = 260.0;
    data.current = 18.0;

    return data;
}
