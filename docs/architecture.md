# System Architecture

```mermaid
flowchart TD
    A[Sensor Simulation / Input] --> B[Monitoring Application]

    B --> C[Fault Detection Module]

    B --> D[Linux Character Device Driver]

    D --> E[Kernel Space]

    D --> F[Device File<br>/dev/industrial_monitor]

    B --> G[Logging Module]

    G --> H[industrial_monitor.log]

    D --> I[Driver Statistics]

    D --> J[Kernel Logs<br>dmesg]
Components
- Sensor Layer: Provides simulated or manual industrial sensor values.
- Monitoring Application: User-space C++ application responsible for monitoring cycles.
- Fault Detection Module: Classifies sensor conditions as NORMAL, WARNING, or CRITICAL.
- Linux Character Device Driver: Kernel-space component responsible for communication between user space and kernel space.
- Device File: /dev/industrial_monitor provides the user-space interface to the driver.
- Logging Module: Records monitoring cycles and fault events.
- Driver Statistics: Maintains device opens, sensor updates, IOCTL requests, and fault statistics.
