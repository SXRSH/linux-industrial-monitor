# Class Diagram

```mermaid
classDiagram

class IndustrialMonitor {
    +openDevice()
    +enableMonitoring()
    +sendSensorData()
    +receiveSensorData()
    +reportFault()
    +displayStatistics()
    +closeDevice()
}

class FaultDetector {
    +detectFault()
    +getSeverity()
    +getStatusString()
}

class SensorSimulator {
    +generateSensorData()
    +getTemperature()
    +getVibration()
    +getRPM()
    +getVoltage()
    +getCurrent()
}

class SensorData {
    +temperature
    +vibration
    +motor_rpm
    +voltage
    +current
}

class DriverInterface {
    +IOCTL_SET_SENSOR_DATA
    +IOCTL_GET_SENSOR_DATA
    +IOCTL_REPORT_FAULT
    +IOCTL_GET_STATISTICS
    +IOCTL_RESET_STATISTICS
}

IndustrialMonitor --> FaultDetector
IndustrialMonitor --> SensorSimulator
IndustrialMonitor --> SensorData
IndustrialMonitor --> DriverInterface
FaultDetector --> SensorData
Responsibilities
IndustrialMonitor
Controls the overall monitoring workflow and communicates with the Linux device driver.
FaultDetector
Analyzes sensor values and determines the equipment severity.
SensorSimulator
Generates sensor values for automatic simulation mode.
SensorData
Represents temperature, vibration, RPM, voltage, and current values.
DriverInterface
Defines the user-space/kernel-space IOCTL interface.
