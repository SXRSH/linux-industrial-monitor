# Sequence Diagram

```mermaid
sequenceDiagram

participant User
participant Application
participant FaultDetector
participant Driver
participant Kernel
participant Logger

User->>Application: Start monitoring
Application->>Driver: Open /dev/industrial_monitor
Driver->>Kernel: Initialize device access
Kernel-->>Driver: Device ready
Driver-->>Application: Device opened

loop Monitoring Cycle
    Application->>Application: Generate/receive sensor data
    Application->>Driver: IOCTL_SET_SENSOR_DATA
    Driver->>Kernel: Update sensor data
    Kernel-->>Driver: Data accepted
    Driver-->>Application: Success

    Application->>Driver: IOCTL_GET_SENSOR_DATA
    Driver-->>Application: Sensor data

    Application->>FaultDetector: Analyze sensor data
    FaultDetector-->>Application: NORMAL/WARNING/CRITICAL

    Application->>Driver: IOCTL_REPORT_FAULT
    Driver->>Kernel: Update fault statistics

    Application->>Logger: Write monitoring result

    alt WARNING
        Driver-->>Application: Warning event
    else CRITICAL
        Driver-->>Application: Critical event
    else NORMAL
        Driver-->>Application: Equipment normal
    end
end

User->>Application: Ctrl+C
Application->>Driver: IOCTL_GET_STATISTICS
Driver-->>Application: Driver statistics
Application->>Driver: IOCTL_RESET_STATISTICS
Application->>Driver: Close device
Driver->>Kernel: Release resources
