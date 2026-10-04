#include <iostream>
#include <iomanip>

#include "industrial_monitor.h"
#include "sensor_simulator.h"

void displaySensorData(
    const SensorData& data,
    const FaultStatus& status,
    const IndustrialMonitor& monitor)
{
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Temperature : " << data.temperature
              << " C ["
              << monitor.faultLevelToString(status.temperature_status)
              << "]\n";

    std::cout << "Vibration   : " << data.vibration
              << " mm/s ["
              << monitor.faultLevelToString(status.vibration_status)
              << "]\n";

    std::cout << "Motor RPM   : " << data.rpm
              << " RPM ["
              << monitor.faultLevelToString(status.rpm_status)
              << "]\n";

    std::cout << "Voltage     : " << data.voltage
              << " V ["
              << monitor.faultLevelToString(status.voltage_status)
              << "]\n";

    std::cout << "Current     : " << data.current
              << " A ["
              << monitor.faultLevelToString(status.current_status)
              << "]\n";

    std::cout << "----------------------------------------\n";

    std::cout << "Overall Status: "
              << monitor.faultLevelToString(status.overall_status)
              << "\n";
}

int main()
{
    IndustrialMonitor monitor;
    SensorSimulator simulator;

    std::cout << "\n========================================\n";
    std::cout << " INDUSTRIAL EQUIPMENT MONITOR\n";
    std::cout << "========================================\n";

    // NORMAL CONDITION
    std::cout << "\n[1] NORMAL OPERATING CONDITION\n";
    std::cout << "----------------------------------------\n";

    SensorData normalData = simulator.generateNormalData();
    FaultStatus normalStatus = monitor.analyze(normalData);

    displaySensorData(normalData, normalStatus, monitor);

    // WARNING CONDITION
    std::cout << "\n[2] WARNING OPERATING CONDITION\n";
    std::cout << "----------------------------------------\n";

    SensorData warningData = simulator.generateWarningData();
    FaultStatus warningStatus = monitor.analyze(warningData);

    displaySensorData(warningData, warningStatus, monitor);

    // CRITICAL CONDITION
    std::cout << "\n[3] CRITICAL OPERATING CONDITION\n";
    std::cout << "----------------------------------------\n";

    SensorData criticalData = simulator.generateCriticalData();
    FaultStatus criticalStatus = monitor.analyze(criticalData);

    displaySensorData(criticalData, criticalStatus, monitor);

    std::cout << "\n========================================\n";
    std::cout << " MONITORING TEST COMPLETED\n";
    std::cout << "========================================\n";

    return 0;
}
