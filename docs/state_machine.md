# State Machine Diagram

```mermaid
stateDiagram-v2

[*] --> NORMAL

NORMAL --> WARNING : Sensor threshold exceeded
WARNING --> CRITICAL : Critical threshold exceeded
CRITICAL --> WARNING : Condition improves
WARNING --> NORMAL : Parameters return to normal
CRITICAL --> NORMAL : Equipment recovers

NORMAL --> NORMAL : Normal sensor values
WARNING --> WARNING : Warning condition persists
CRITICAL --> CRITICAL : Critical condition persists

NORMAL --> [*] : Monitoring stopped
WARNING --> [*] : Monitoring stopped
CRITICAL --> [*] : Monitoring stopped
Equipment States
NORMAL
Equipment parameters are within acceptable operating limits.
WARNING
One or more parameters exceed warning thresholds and require attention.
CRITICAL
One or more parameters exceed critical thresholds and require immediate attention.
Recovery
When sensor parameters return to acceptable limits, the equipment transitions back toward NORMAL.
