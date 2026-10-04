# Linux-Based Industrial Equipment Monitoring and Fault Detection System

## 1. Project Overview

A Linux-based industrial equipment monitoring and fault detection system implemented entirely using **C/C++** and a custom **Linux character device driver**.

The system simulates industrial sensor data for:

- Temperature
- Vibration
- Motor RPM
- Voltage
- Current

The sensor data is transferred between **user space and kernel space** through a custom Linux character device using **IOCTL interfaces**.

The monitoring application analyzes the sensor values and classifies equipment conditions into:

- **NORMAL**
- **WARNING**
- **CRITICAL**

The system also maintains driver statistics, detects fault-state transitions, records events in kernel logs, and maintains application-level monitoring logs.

---

## 2. Project Objectives

The main objectives of this project are:

- Implement a custom Linux character device driver.
- Demonstrate communication between user space and kernel space.
- Use IOCTLs for sensor data and driver control.
- Monitor multiple industrial equipment parameters.
- Implement configurable sensor input and simulation.
- Detect abnormal equipment conditions.
- Classify faults based on severity.
- Detect transitions between NORMAL, WARNING, and CRITICAL states.
- Maintain driver statistics.
- Implement driver reset and error handling.
- Implement application and kernel-side logging.
- Demonstrate Linux system programming and software architecture concepts.

---

## 3. Technologies Used

### Programming Languages

- C
- C++17

### Operating System

- Linux

### System Programming

- Linux Kernel Modules
- Character Device Drivers
- IOCTL
- User Space / Kernel Space Communication
- File Operations
- Kernel Logging
- Linux Signals

### Development Tools

- GCC
- G++
- GNU Make
- Git
- GitHub

---

## 4. Project Requirements Compliance

| Requirement | Implementation |
|---|---|
| C/C++ only | Application written in C++17 and driver written in C |
| Linux OS | Implemented and tested exclusively on Linux |
| Linux Device Driver | Custom Linux character device driver |
| Software/Hardware Architecture | Layered monitoring and driver architecture |
| GitHub Submission | Complete source code, README, Makefiles, tests and documentation |

---

## 5. System Architecture

```text
                    INDUSTRIAL EQUIPMENT
                           │
                           ▼
                  ┌──────────────────┐
                  │   Sensor Layer   │
                  │                  │
                  │ Temperature      │
                  │ Vibration        │
                  │ Motor RPM        │
                  │ Voltage          │
                  │ Current          │
                  └────────┬─────────┘
                           │
                           ▼
                  ┌──────────────────┐
                  │ Monitoring       │
                  │ Application      │
                  │   C++17          │
                  └────────┬─────────┘
                           │
                     IOCTL Interface
                           │
                           ▼
              ┌──────────────────────────┐
              │ Linux Character Device   │
              │        Driver            │
              │                          │
              │ /dev/industrial_monitor  │
              └────────────┬─────────────┘
                           │
                           ▼
                  ┌──────────────────┐
                  │ Kernel Space     │
                  │                  │
                  │ Sensor Storage   │
                  │ Fault Events     │
                  │ Statistics       │
                  │ Reset Handling   │
                  │ Error Handling   │
                  └──────────────────┘

                           │
                           ▼
                  ┌──────────────────┐
                  │ Fault Detection  │
                  │                  │
                  │ NORMAL           │
                  │ WARNING          │
                  │ CRITICAL         │
                  └────────┬─────────┘
                           │
                           ▼
                  ┌──────────────────┐
                  │ Logging / Report │
                  │                  │
                  │ Application Log  │
                  │ Kernel dmesg     │
                  └──────────────────┘
# Linux-Based Industrial Equipment Monitoring and Fault Detection System

## 1. Project Overview

A Linux-based industrial equipment monitoring and fault detection system implemented entirely using **C/C++** and a custom **Linux character device driver**.

The system simulates industrial sensor data for:

- Temperature
- Vibration
- Motor RPM
- Voltage
- Current

The sensor data is transferred between **user space and kernel space** through a custom Linux character device using **IOCTL interfaces**.

The monitoring application analyzes the sensor values and classifies equipment conditions into:

- **NORMAL**
- **WARNING**
- **CRITICAL**

The system also maintains driver statistics, detects fault-state transitions, records events in kernel logs, and maintains application-level monitoring logs.

---

## 2. Project Objectives

The main objectives of this project are:

- Implement a custom Linux character device driver.
- Demonstrate communication between user space and kernel space.
- Use IOCTLs for sensor data and driver control.
- Monitor multiple industrial equipment parameters.
- Implement configurable sensor input and simulation.
- Detect abnormal equipment conditions.
- Classify faults based on severity.
- Detect transitions between NORMAL, WARNING, and CRITICAL states.
- Maintain driver statistics.
- Implement driver reset and error handling.
- Implement application and kernel-side logging.
- Demonstrate Linux system programming and software architecture concepts.

---

## 3. Technologies Used

### Programming Languages

- C
- C++17

### Operating System

- Linux

### System Programming

- Linux Kernel Modules
- Character Device Drivers
- IOCTL
- User Space / Kernel Space Communication
- File Operations
- Kernel Logging
- Linux Signals

### Development Tools

- GCC
- G++
- GNU Make
- Git
- GitHub

---

## 4. Project Requirements Compliance

| Requirement | Implementation |
|---|---|
| C/C++ only | Application written in C++17 and driver written in C |
| Linux OS | Implemented and tested exclusively on Linux |
| Linux Device Driver | Custom Linux character device driver |
| Software/Hardware Architecture | Layered monitoring and driver architecture |
| GitHub Submission | Complete source code, README, Makefiles, tests and documentation |

---

## 5. System Architecture

```text
                    INDUSTRIAL EQUIPMENT
                           │
                           ▼
                  ┌──────────────────┐
                  │   Sensor Layer   │
                  │                  │
                  │ Temperature      │
                  │ Vibration        │
                  │ Motor RPM        │
                  │ Voltage          │
                  │ Current          │
                  └────────┬─────────┘
                           │
                           ▼
                  ┌──────────────────┐
                  │ Monitoring       │
                  │ Application      │
                  │   C++17          │
                  └────────┬─────────┘
                           │
                     IOCTL Interface
                           │
                           ▼
              ┌──────────────────────────┐
              │ Linux Character Device   │
              │        Driver            │
              │                          │
              │ /dev/industrial_monitor  │
              └────────────┬─────────────┘
                           │
                           ▼
                  ┌──────────────────┐
                  │ Kernel Space     │
                  │                  │
                  │ Sensor Storage   │
                  │ Fault Events     │
                  │ Statistics       │
                  │ Reset Handling   │
                  │ Error Handling   │
                  └──────────────────┘

                           │
                           ▼
                  ┌──────────────────┐
                  │ Fault Detection  │
                  │                  │
                  │ NORMAL           │
                  │ WARNING          │
                  │ CRITICAL         │
                  └────────┬─────────┘
                           │
                           ▼
                  ┌──────────────────┐
                  │ Logging / Report │
                  │                  │
                  │ Application Log  │
                  │ Kernel dmesg     │
                  └──────────────────┘
# Linux-Based Industrial Equipment Monitoring and Fault Detection System

## 1. Project Overview

A Linux-based industrial equipment monitoring and fault detection system implemented entirely using **C/C++** and a custom **Linux character device driver**.

The system simulates industrial sensor data for:

- Temperature
- Vibration
- Motor RPM
- Voltage
- Current

The sensor data is transferred between **user space and kernel space** through a custom Linux character device using **IOCTL interfaces**.

The monitoring application analyzes the sensor values and classifies equipment conditions into:

- **NORMAL**
- **WARNING**
- **CRITICAL**

The system also maintains driver statistics, detects fault-state transitions, records events in kernel logs, and maintains application-level monitoring logs.

---

## 2. Project Objectives

The main objectives of this project are:

- Implement a custom Linux character device driver.
- Demonstrate communication between user space and kernel space.
- Use IOCTLs for sensor data and driver control.
- Monitor multiple industrial equipment parameters.
- Implement configurable sensor input and simulation.
- Detect abnormal equipment conditions.
- Classify faults based on severity.
- Detect transitions between NORMAL, WARNING, and CRITICAL states.
- Maintain driver statistics.
- Implement driver reset and error handling.
- Implement application and kernel-side logging.
- Demonstrate Linux system programming and software architecture concepts.

---

## 3. Technologies Used

### Programming Languages

- C
- C++17

### Operating System

- Linux

### System Programming

- Linux Kernel Modules
- Character Device Drivers
- IOCTL
- User Space / Kernel Space Communication
- File Operations
- Kernel Logging
- Linux Signals

### Development Tools

- GCC
- G++
- GNU Make
- Git
- GitHub

---

## 4. Project Requirements Compliance

| Requirement | Implementation |
|---|---|
| C/C++ only | Application written in C++17 and driver written in C |
| Linux OS | Implemented and tested exclusively on Linux |
| Linux Device Driver | Custom Linux character device driver |
| Software/Hardware Architecture | Layered monitoring and driver architecture |
| GitHub Submission | Complete source code, README, Makefiles, tests and documentation |

---

## 5. System Architecture

```text
                    INDUSTRIAL EQUIPMENT
                           │
                           ▼
                  ┌──────────────────┐
                  │   Sensor Layer   │
                  │                  │
                  │ Temperature      │
                  │ Vibration        │
                  │ Motor RPM        │
                  │ Voltage          │
                  │ Current          │
                  └────────┬─────────┘
                           │
                           ▼
                  ┌──────────────────┐
                  │ Monitoring       │
                  │ Application      │
                  │   C++17          │
                  └────────┬─────────┘
                           │
                     IOCTL Interface
                           │
                           ▼
              ┌──────────────────────────┐
              │ Linux Character Device   │
              │        Driver            │
              │                          │
              │ /dev/industrial_monitor  │
              └────────────┬─────────────┘
                           │
                           ▼
                  ┌──────────────────┐
                  │ Kernel Space     │
                  │                  │
                  │ Sensor Storage   │
                  │ Fault Events     │
                  │ Statistics       │
                  │ Reset Handling   │
                  │ Error Handling   │
                  └──────────────────┘

                           │
                           ▼
                  ┌──────────────────┐
                  │ Fault Detection  │
                  │                  │
                  │ NORMAL           │
                  │ WARNING          │
                  │ CRITICAL         │
                  └────────┬─────────┘
                           │
                           ▼
                  ┌──────────────────┐
                  │ Logging / Report │
                  │                  │
                  │ Application Log  │
                  │ Kernel dmesg     │
                  └──────────────────┘
6. Project Structure
industrial-monitor/
│
├── driver/
│   ├── industrial_monitor_driver.c
│   └── Makefile
│
├── include/
│   ├── driver_interface.h
│   ├── fault_detector.h
│   ├── industrial_monitor.h
│   └── sensor_simulator.h
│
├── src/
│   ├── industrial_monitor.cpp
│   ├── fault_detector.cpp
│   ├── sensor_simulator.cpp
│   └── main.cpp
│
├── tests/
│   └── driver_test.cpp
│
├── logs/
│   └── industrial_monitor.log
│
├── Makefile
├── README.md
└── .gitignore
Generated kernel build artifacts such as .o, .ko, .mod, .cmd, and other temporary files are excluded using .gitignore.
7. Sensor Parameters
The system monitors five industrial parameters.
Parameter	Unit	Purpose
Temperature	°C	Detect overheating
Vibration	mm/s	Detect excessive mechanical vibration
Motor RPM	RPM	Monitor motor operating speed
Voltage	V	Monitor electrical voltage
Current	A	Monitor electrical current


8. Fault Severity Classification
The monitoring application evaluates every sensor parameter and determines its severity.
NORMAL
Equipment is operating within the expected operating range.
WARNING
The equipment is operating outside the normal range and requires attention.
CRITICAL
The equipment has reached a critical operating condition and requires immediate attention.
The overall equipment status is determined from the individual sensor conditions.
9. State Transition Detection
The driver maintains the current fault state and detects meaningful state transitions.
Examples:
NORMAL → WARNING
WARNING → CRITICAL
CRITICAL → NORMAL
NORMAL → CRITICAL

Repeated reports of the same state do not unnecessarily generate new fault events.
The driver logs important transitions such as:
NEW WARNING fault event
NEW CRITICAL fault event
equipment recovered to NORMAL

This provides event-based fault tracking instead of simply counting every monitoring cycle as a new fault.
10. Linux Character Device Driver
The project implements a custom Linux character device.
Device:
/dev/industrial_monitor

The driver provides communication between the user-space monitoring application and kernel space.
The driver supports:
- Device open
- Device close
- IOCTL operations
- Sensor data update
- Sensor data retrieval
- Driver mode configuration
- Driver reset
- Driver statistics
- Fault event reporting
- Invalid IOCTL rejection
- Kernel logging
11. IOCTL Interface
The shared interface is defined in:
include/driver_interface.h

Supported IOCTLs
IOCTL	Purpose
IOCTL_GET_STATUS	Retrieve driver status
IOCTL_SET_MODE	Configure driver mode
IOCTL_RESET	Reset driver state
IOCTL_GET_SENSOR_DATA	Retrieve sensor data
IOCTL_SET_SENSOR_DATA	Update sensor data
IOCTL_GET_STATS	Retrieve driver statistics
IOCTL_REPORT_FAULT	Report fault severity


The same interface definition is shared between user space and kernel space to maintain a consistent communication contract.
12. Driver Statistics
The driver maintains runtime statistics including:
- Device opens
- Device closes
- Sensor reads
- Sensor updates
- IOCTL requests
- Fault events
- Warning events
- Critical events
- Last fault severity
- Last fault timestamp
Example:
----------------------------------------
 DRIVER STATISTICS
----------------------------------------
Device Opens       : 1
Device Closes      : 0
Sensor Reads       : 0
Sensor Updates     : 3
IOCTL Requests     : 11
Fault Events       : 2
Warning Events     : 1
Critical Events    : 1
Last Fault Severity: 2
Last Fault Time    : ...
----------------------------------------

13. User Space Monitoring Application
The monitoring application:
1. Opens /dev/industrial_monitor.
2. Enables monitoring mode.
3. Generates or accepts sensor values.
4. Sends sensor data to the kernel driver.
5. Retrieves sensor data from the driver.
6. Performs fault analysis.
7. Determines overall equipment status.
8. Reports fault severity to the driver.
9. Logs monitoring information.
10. Displays driver statistics when monitoring stops.
11. Resets the driver.
12. Closes the device.
14. Automatic Simulation Mode
The default monitoring mode uses simulated industrial sensor conditions.
Scenario 1 — NORMAL
Temperature : 65 C
Vibration   : 3 mm/s
Motor RPM   : 2200 RPM
Voltage     : 230 V
Current     : 7 A

Expected status:
NORMAL

Scenario 2 — WARNING
Temperature : 80 C
Vibration   : 5 mm/s
Motor RPM   : 3200 RPM
Voltage     : 245 V
Current     : 12 A

Expected status:
WARNING

Scenario 3 — CRITICAL
Temperature : 100 C
Vibration   : 9 mm/s
Motor RPM   : 3800 RPM
Voltage     : 260 V
Current     : 18 A

Expected status:
CRITICAL

The application cycles through these scenarios automatically.
15. Manual Sensor Input
The application also supports manual sensor input.
Example:
sudo ./industrial_monitor --manual

The user can enter sensor values directly for testing different operating conditions.
16. Logging
The project provides two levels of logging.
Application Logging
Monitoring events are stored in:
logs/industrial_monitor.log

The log contains:
- Monitoring cycles
- Sensor values
- Fault severity
- Overall equipment status
- Fault events
- Driver statistics
- Driver reset status
- Session start/stop events
Kernel Logging
Kernel-side driver events can be inspected using:
sudo dmesg | tail -30

Example:
industrial_monitor: device opened
industrial_monitor: mode changed to 1
industrial_monitor: sensor data updated
industrial_monitor: sensor data requested
industrial_monitor: NEW WARNING fault event
industrial_monitor: NEW CRITICAL fault event
industrial_monitor: equipment recovered to NORMAL
industrial_monitor: statistics requested
industrial_monitor: driver reset
industrial_monitor: device closed

17. Error Handling
The project implements error handling at both user and kernel levels.
Examples include:
- Device open failure
- IOCTL failure
- Invalid IOCTL command
- Sensor data transfer failure
- Driver reset failure
- Device close handling
Invalid IOCTL testing was performed and rejected correctly:
[OK] Invalid IOCTL rejected
Error: Invalid argument

18. Build Requirements
A Linux system with the following installed packages/tools is required:
- GCC
- G++
- GNU Make
- Linux kernel headers
- Build tools
The project must be executed on Linux because it depends on Linux kernel interfaces and kernel module infrastructure.
19. Build the Project
Clone the repository:
git clone <YOUR_GITHUB_REPOSITORY_URL>
cd industrial-monitor

Build the complete project:
make

This builds:
industrial_monitor
driver/industrial_monitor_driver.ko

20. Clean the Build
To remove generated application and kernel build files:
make clean

Then rebuild:
make

21. Load the Kernel Driver
Load the driver:
sudo insmod driver/industrial_monitor_driver.ko

Verify that the module is loaded:
lsmod | grep industrial_monitor

Verify the character device:
ls -l /dev/industrial_monitor

Expected device:
/dev/industrial_monitor

22. Run the Monitoring Application
Run automatic simulation mode:
sudo ./industrial_monitor

The application will cycle through:
NORMAL
   ↓
WARNING
   ↓
CRITICAL
   ↓
NORMAL

Press:
Ctrl+C

to stop monitoring.
The application then displays the final driver statistics, resets the driver, and closes the device.
23. Run Manual Mode
Run:
sudo ./industrial_monitor --manual

Enter sensor values when prompted.
This mode can be used to test custom operating conditions.
24. View Kernel Logs
Use:
sudo dmesg | tail -40

To monitor driver events while testing:
sudo dmesg -w

Press:
Ctrl+C

to stop following the kernel log.
25. Unload the Driver
After testing:
sudo rmmod industrial_monitor_driver

Verify:
lsmod | grep industrial_monitor

The module should no longer appear.
26. Makefile Commands
The top-level Makefile provides the following commands:
Build everything
make

Build application
make app

Build tests
make test

Build kernel driver
make driver

Clean build files
make clean

Install/load driver
make install

Unload driver
make uninstall

27. Testing
The project was tested using:
Functional Testing
- Character device opening
- Monitoring mode configuration
- Sensor data update
- Sensor data retrieval
- Fault reporting
- Driver statistics
- Driver reset
- Device close
Fault Testing
- NORMAL condition
- WARNING condition
- CRITICAL condition
- WARNING → CRITICAL transition
- CRITICAL → NORMAL recovery
- Repeated monitoring cycles
Error Testing
- Invalid IOCTL command
- Driver communication errors
- Device access errors
- Reset handling
Kernel Verification
Kernel events were verified using:
sudo dmesg

28. Example Monitoring Output
========================================
 MONITORING CYCLE 2
========================================

Temperature : 80.00 C [WARNING]
Vibration   : 5.00 mm/s [WARNING]
Motor RPM   : 3200 RPM [WARNING]
Voltage     : 245.00 V [WARNING]
Current     : 12.00 A [WARNING]

----------------------------------------
Overall Status: WARNING

[OK] Fault status reported to kernel
[WARNING] Equipment requires attention

Critical condition:
----------------------------------------
Overall Status: CRITICAL

[OK] Fault status reported to kernel
[CRITICAL] Immediate equipment attention required

29. Security and Privilege Requirements
Loading and unloading a Linux kernel module requires administrator privileges.
Therefore, commands such as:
sudo insmod ...
sudo rmmod ...
sudo ./industrial_monitor

may require sudo.
The project should be executed in a controlled Linux development environment.
30. Limitations
This project uses simulated or manually entered sensor data rather than physical industrial sensors.
The system is intended as an educational demonstration of:
- Linux device driver development
- Kernel/user-space communication
- Fault detection
- System programming
- Software architecture
It is not intended to directly control or protect real industrial machinery.
31. Key Learning Outcomes
This project demonstrates practical understanding of:
- C and C++ programming
- Linux system programming
- Linux kernel modules
- Character device drivers
- IOCTL interfaces
- User space and kernel space
- Kernel logging
- Fault detection
- State transition handling
- Error handling
- Runtime statistics
- GNU Make
- Git and GitHub
- Software architecture
32. Future Enhancements
Possible future improvements include:
- Integration with physical sensors
- Real-time sensor acquisition
- Configurable fault thresholds
- Persistent fault history
- Web-based monitoring dashboard
- Database-backed logging
- Alert notifications
- Hardware-specific sensor interfaces
- More advanced synchronization mechanisms
- Performance monitoring and benchmarking
33. Conclusion
The Linux-Based Industrial Equipment Monitoring and Fault Detection System demonstrates a complete software architecture combining a C++ monitoring application with a custom C-based Linux character device driver.
The project successfully demonstrates:
Sensor Simulation
       ↓
C++ Monitoring Application
       ↓
IOCTL Interface
       ↓
Linux Character Device
       ↓
Kernel Driver
       ↓
Fault Detection & Statistics
       ↓
Logging and Reporting

The system was implemented using C/C++ on Linux, incorporates relevant Linux Device Driver concepts, and provides a complete build, execution, testing, and documentation workflow.
