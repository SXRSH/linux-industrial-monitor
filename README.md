# Linux-Based Industrial Equipment Monitoring and Fault Detection System

## Project Overview

The Linux-Based Industrial Equipment Monitoring and Fault Detection System is a C/C++ based Linux project that demonstrates communication between user space and kernel space using a custom Linux character device driver.

The system monitors industrial equipment parameters such as:

- Temperature
- Vibration
- Motor RPM
- Voltage
- Current

The collected sensor data is transferred from the monitoring application to the Linux kernel through IOCTL-based communication. The system analyzes the sensor values and classifies equipment conditions into NORMAL, WARNING, and CRITICAL states.

The project demonstrates Linux system programming, device driver development, fault detection, software architecture, kernel-user space communication, logging, testing, and Git-based project management.

---

# Stage 1 – Project Introduction

## 1.1 Problem Statement

Industrial equipment must be continuously monitored to detect abnormal operating conditions before they result in equipment damage, production downtime, or safety issues.

Traditional monitoring systems may require dedicated industrial hardware and proprietary monitoring software. This project demonstrates a software-based prototype that uses Linux system programming and a custom character device driver to simulate industrial equipment monitoring.

The system detects abnormal sensor conditions and reports the severity of the detected fault.

## 1.2 Project Objective

The main objectives of the project are:

- Monitor important industrial equipment parameters.
- Develop a custom Linux character device driver.
- Establish communication between user space and kernel space.
- Transfer sensor data using IOCTL interfaces.
- Detect abnormal operating conditions.
- Classify faults into NORMAL, WARNING, and CRITICAL levels.
- Maintain driver statistics.
- Detect state transitions such as WARNING, CRITICAL, and recovery to NORMAL.
- Maintain application-level monitoring logs.
- Provide automatic sensor simulation and manual sensor input.
- Demonstrate Linux device driver concepts and system-level programming.

## 1.3 Project Scope

The project covers:

- C/C++ application development.
- Linux kernel module development.
- Character device driver implementation.
- User-space and kernel-space communication.
- Sensor data simulation.
- Manual sensor data input.
- Fault detection and severity classification.
- State-transition detection.
- Driver statistics and IOCTL operations.
- Event logging.
- Error handling.
- Driver testing.
- Build and installation workflow.

The project is implemented as a software prototype and does not directly interface with physical industrial sensors.

## 1.4 Expected Outcome

The expected outcome is a working Linux-based monitoring system capable of:

1. Starting the custom device driver.
2. Creating the `/dev/industrial_monitor` character device.
3. Sending sensor data from user space to the kernel.
4. Receiving sensor data from the kernel.
5. Detecting abnormal equipment conditions.
6. Reporting WARNING and CRITICAL faults.
7. Detecting recovery to NORMAL conditions.
8. Maintaining driver statistics.
9. Recording monitoring events in log files.
10. Handling invalid IOCTL requests.
11. Supporting automatic and manual monitoring modes.

## 1.5 Application

The prototype demonstrates concepts applicable to:

- Industrial equipment monitoring.
- Predictive maintenance systems.
- Embedded Linux monitoring systems.
- Machine health monitoring.
- Fault detection systems.
- Linux-based industrial automation.

---

# Stage 2 – Project Requirements & Development Plan

## 2.1 Functional Requirements

The system shall:

- Initialize a Linux character device driver.
- Create the `/dev/industrial_monitor` device.
- Open and close the device from the user application.
- Transfer sensor data between user space and kernel space.
- Support IOCTL commands.
- Monitor temperature.
- Monitor vibration.
- Monitor motor RPM.
- Monitor voltage.
- Monitor current.
- Classify sensor conditions.
- Detect WARNING conditions.
- Detect CRITICAL conditions.
- Detect recovery to NORMAL.
- Maintain driver statistics.
- Record fault events.
- Record warning events.
- Record critical events.
- Record timestamps for fault events.
- Reject invalid IOCTL commands.
- Support automatic sensor simulation.
- Support manual sensor input.
- Generate application monitoring logs.

## 2.2 Non-Functional Requirements

### Performance

- The monitoring application should operate continuously.
- Sensor monitoring should occur periodically.
- Kernel-user communication should have low overhead.

### Reliability

- Invalid IOCTL commands must be rejected.
- Driver errors should be handled safely.
- The application should properly close the device during shutdown.
- Driver statistics should remain consistent.

### Maintainability

- The project should use a modular architecture.
- Driver, application, sensor simulation, and fault detection logic should be separated.
- Source code should be organized into appropriate directories.

### Portability

The project is designed for Linux systems with compatible kernel headers and development tools.

### Security

- Kernel operations are performed through controlled IOCTL interfaces.
- Device access is controlled by Linux device permissions.
- Invalid commands are rejected by the driver.

## 2.3 Project Modules

The project consists of the following major modules:

1. Sensor Simulation Module
2. Monitoring Application
3. Fault Detection Module
4. Linux Character Device Driver
5. Driver Interface / IOCTL Module
6. Logging Module
7. Testing Module
8. Build and Installation Module

## 2.4 Development Plan

| Stage | Work |
|------|------|
| Stage 1 | Project introduction, objectives, problem definition and scope |
| Stage 2 | Requirements, modules and development planning |
| Stage 3 | Architecture, data structures, interfaces and development environment |
| Stage 4 | Driver, application and fault detection implementation |
| Stage 5 | Integration, testing, debugging and logging |
| Stage 6 | Final implementation, documentation and presentation |

---

# Stage 3 – System Design & Architecture

## 3.1 System Architecture

The project follows a layered software architecture.

```text
+---------------------------------------------------+
|              Monitoring Application               |
|                 C++ User Space                   |
+-------------------------+-------------------------+
                          |
                          | IOCTL
                          | read/write
                          v
+---------------------------------------------------+
|          Linux Character Device Driver            |
|                  Kernel Space                     |
+-------------------------+-------------------------+
                          |
                          v
+---------------------------------------------------+
|             Driver State & Statistics             |
| Sensor Data | Fault State | Counters | Events    |
+---------------------------------------------------+

Supporting Modules:

+--------------------+     +-----------------------+
| Sensor Simulator   | --> | Fault Detection       |
+--------------------+     +-----------------------+
                                     |
                                     v
                           NORMAL / WARNING /
                              CRITICAL

                    +-----------------------+
                    | Logging System        |
                    +-----------------------+
3.2 Major Components
Sensor Simulator
Generates simulated industrial equipment sensor values.
Parameters include:
- Temperature
- Vibration
- Motor RPM
- Voltage
- Current
Monitoring Application
The C++ application:
- Opens the character device.
- Enables monitoring mode.
- Sends sensor data.
- Receives sensor data.
- Displays sensor values.
- Determines equipment status.
- Reports fault status.
- Requests driver statistics.
- Handles application shutdown.
Fault Detection Module
The fault detection module evaluates sensor values and determines the equipment severity:
NORMAL
   |
   v
WARNING
   |
   v
CRITICAL

The system also supports recovery:
CRITICAL / WARNING
        |
        v
     NORMAL

Linux Character Device Driver
The kernel module:
- Registers the character device.
- Creates /dev/industrial_monitor.
- Handles device open and close operations.
- Handles IOCTL commands.
- Stores sensor data.
- Maintains statistics.
- Detects fault events.
- Logs kernel events.
- Handles invalid IOCTL commands.
Logging System
The application maintains monitoring logs containing:
- Timestamp
- Monitoring cycle
- Sensor values
- Equipment status
- Fault events
- Warning events
- Critical events
- Driver statistics
- Session information
3.3 Data Structures
The project uses structured data to represent sensor information and driver statistics.
Typical sensor parameters include:
Temperature
Vibration
Motor RPM
Voltage
Current

Driver statistics include:
Device Opens
Device Closes
Sensor Reads
Sensor Updates
IOCTL Requests
Fault Events
Warning Events
Critical Events
Last Fault Severity
Last Fault Time

3.4 IOCTL Interface
The monitoring application communicates with the kernel driver using IOCTL operations.
The interface supports operations for:
- Sensor data update
- Sensor data retrieval
- Monitoring mode
- Fault reporting
- Statistics retrieval
- Driver reset
Invalid IOCTL commands are rejected by the driver.
Example tested result:
[OK] Invalid IOCTL rejected
Error: Invalid argument

3.5 State Machine
The equipment monitoring state can be represented as:
              +----------+
              |  NORMAL  |
              +----+-----+
                   |
             Abnormal values
                   |
                   v
             +-----+------+
             |   WARNING  |
             +-----+------+
                   |
             Severe values
                   |
                   v
             +-----+------+
             |  CRITICAL  |
             +-----+------+
                   |
              Recovery
                   |
                   v
              +----+-----+
              |  NORMAL   |
              +----------+

3.6 Development Environment
The project uses:
- Linux OS
- GCC
- G++
- GNU Make
- Linux Kernel Headers
- C
- C++
- Git
- GitHub
- Linux Kernel Module APIs
The project is developed and tested on an ARM64 Linux environment.
3.7 Git Repository
Git is used for:
- Source code management.
- Version control.
- Project history.
- Documentation management.
- Final GitHub submission.
The main development branch is:
main

Stage 4 – Initial Implementation & Prototype
4.1 Driver Implementation
A custom Linux character device driver was implemented.
The driver creates:
/dev/industrial_monitor

The driver supports:
- Device initialization.
- Device opening.
- Device closing.
- IOCTL handling.
- Sensor data updates.
- Sensor data requests.
- Fault reporting.
- Statistics retrieval.
- Driver reset.
4.2 Monitoring Application
The C++ monitoring application was implemented to communicate with the kernel driver.
The application provides:
Automatic Simulation Mode
The application automatically generates sensor values representing:
NORMAL
WARNING
CRITICAL

Example:
Temperature : 65.00 C [NORMAL]
Vibration   : 3.00 mm/s [NORMAL]
Motor RPM   : 2200 RPM [NORMAL]
Voltage     : 230.00 V [NORMAL]
Current     : 7.00 A [NORMAL]

WARNING example:
Temperature : 80.00 C [WARNING]
Vibration   : 5.00 mm/s [WARNING]
Motor RPM   : 3200 RPM [WARNING]
Voltage     : 245.00 V [WARNING]
Current     : 12.00 A [WARNING]

CRITICAL example:
Temperature : 100.00 C [CRITICAL]
Vibration   : 9.00 mm/s [CRITICAL]
Motor RPM   : 3800 RPM [CRITICAL]
Voltage     : 260.00 V [CRITICAL]
Current     : 18.00 A [CRITICAL]

Manual Input Mode
The application also supports manual sensor input for testing different operating conditions.
4.3 Fault Detection
The system detects:
- Normal operation.
- Warning conditions.
- Critical conditions.
- Recovery to normal operation.
The kernel driver logs state transitions such as:
NEW WARNING fault event
NEW CRITICAL fault event
equipment recovered to NORMAL

4.4 Prototype Demonstration
A complete monitoring cycle successfully performs:
Sensor Generation
       |
       v
User Application
       |
       v
IOCTL
       |
       v
Linux Kernel Driver
       |
       v
Sensor Data Processing
       |
       v
Fault Detection
       |
       v
Statistics + Logging

Stage 5 – Testing, Integration & Improvement
5.1 Build Testing
The complete project can be built using:
make

The build successfully generates:
industrial_monitor
driver/industrial_monitor_driver.ko

5.2 Driver Testing
The driver was tested using:
sudo insmod driver/industrial_monitor_driver.ko

The loaded module can be verified using:
lsmod | grep industrial_monitor

The device can be verified using:
ls -l /dev/industrial_monitor

5.3 Monitoring Application Testing
The application was tested using:
sudo ./industrial_monitor

The system successfully demonstrated:
- NORMAL state.
- WARNING state.
- CRITICAL state.
- Recovery to NORMAL.
- Sensor data transfer.
- Fault reporting.
- Driver statistics.
- Monitoring shutdown.
5.4 State Transition Testing
The driver successfully generated events such as:
NEW WARNING fault event
NEW CRITICAL fault event
equipment recovered to NORMAL

This verifies the implemented state-transition fault handling.
5.5 Statistics Testing
Example driver statistics:
Device Opens       : 5
Device Closes      : 4
Sensor Reads       : 0
Sensor Updates     : 3
IOCTL Requests     : 11
Fault Events       : 2
Warning Events     : 1
Critical Events    : 1
Last Fault Severity: 2

The counters demonstrate successful interaction between the monitoring application and kernel driver.
5.6 Invalid IOCTL Testing
Invalid IOCTL handling was tested using a dedicated test program.
Result:
[OK] Invalid IOCTL rejected
Error: Invalid argument

Kernel log:
industrial_monitor: unknown ioctl command

This confirms that unsupported IOCTL requests are rejected safely.
5.7 Kernel Log Verification
Kernel events were verified using:
sudo dmesg | tail -30

Example events:
industrial_monitor: sensor data updated
industrial_monitor: sensor data requested
industrial_monitor: NEW WARNING fault event
industrial_monitor: NEW CRITICAL fault event
industrial_monitor: equipment recovered to NORMAL
industrial_monitor: statistics requested
industrial_monitor: driver reset
industrial_monitor: device closed

5.8 Application Logging
Monitoring events are recorded in:
logs/industrial_monitor.log

The log contains:
- Monitoring cycles.
- Sensor readings.
- Equipment status.
- Warning events.
- Critical events.
- Driver statistics.
- Session start and stop information.
5.9 Error Handling
The project includes handling for:
- Invalid IOCTL commands.
- Device access errors.
- Driver communication failures.
- Monitoring shutdown.
- Driver reset.
- Invalid operating conditions.
5.10 Testing Summary
Test	Result
Application compilation	PASS
Kernel module compilation	PASS
Driver loading	PASS
Character device creation	PASS
Sensor data update	PASS
Sensor data retrieval	PASS
NORMAL detection	PASS
WARNING detection	PASS
CRITICAL detection	PASS
Recovery detection	PASS
Statistics IOCTL	PASS
Driver reset	PASS
Invalid IOCTL handling	PASS
Kernel logging	PASS
Application logging	PASS
Application shutdown	PASS


Stage 6 – Final Implementation & Presentation
6.1 Final Project Structure
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
│   └── sensor_simulator.cpp
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

6.2 Build Instructions
Clone the repository:
git clone <YOUR_GITHUB_REPOSITORY_URL>
cd industrial-monitor

Build the complete project:
make

6.3 Load the Driver
sudo insmod driver/industrial_monitor_driver.ko

Verify:
lsmod | grep industrial_monitor

Verify the character device:
ls -l /dev/industrial_monitor

6.4 Run the Monitoring Application
sudo ./industrial_monitor

Stop the application using:
Ctrl + C

6.5 Run Tests
Build the test program:
make test

Run:
sudo ./driver_test

6.6 Unload the Driver
sudo rmmod industrial_monitor_driver

6.7 Complete Build Workflow
The complete build can be performed using:
make clean
make

The project Makefile builds both:
- User-space monitoring application.
- Linux kernel module.
6.8 Final Results
The final implementation successfully demonstrates:
- Linux character device driver development.
- Kernel-space and user-space communication.
- IOCTL-based sensor data transfer.
- Industrial sensor monitoring.
- Fault severity classification.
- State-transition fault handling.
- Driver statistics.
- Error handling.
- Kernel event logging.
- Application logging.
- Automatic sensor simulation.
- Manual sensor input.
- Invalid IOCTL rejection.
- Build and installation workflow.
6.9 Project Achievements
The major achievements of the project are:
1. Developed a custom Linux character device driver.
2. Implemented user-space to kernel-space communication.
3. Implemented IOCTL-based communication.
4. Implemented industrial sensor monitoring.
5. Implemented fault severity classification.
6. Implemented WARNING and CRITICAL fault detection.
7. Implemented recovery-to-NORMAL state detection.
8. Implemented driver statistics.
9. Implemented invalid IOCTL handling.
10. Implemented application and kernel logging.
11. Implemented automatic and manual monitoring modes.
12. Integrated the complete system into a single build workflow.
13. Tested the system on Linux.
14. Maintained the project using Git and GitHub.
6.10 Limitations
The current system has the following limitations:
- Sensor values are simulated or manually entered.
- No physical industrial sensors are connected.
- The system is a prototype rather than a production industrial monitoring system.
- The monitoring application currently runs from the command line.
- No graphical dashboard is included.
- No network-based remote monitoring is implemented.
- No real-time hardware acquisition interface is included.
6.11 Future Improvements
Possible future improvements include:
- Integration with real industrial sensors.
- Support for hardware interfaces such as GPIO, I2C, SPI, or ADC.
- Real-time sensor acquisition.
- Web-based monitoring dashboard.
- Remote monitoring and alerting.
- Database-based historical data storage.
- Advanced anomaly detection.
- Predictive maintenance.
- Configurable threshold values.
- Email or notification-based alerts.
- Improved security and device access control.
- System service integration for automatic startup.
- Performance and stress testing under continuous operation.
6.12 Presentation Demonstration Flow
The final project demonstration can follow this sequence:
1. Introduce the problem
        ↓
2. Explain project objectives
        ↓
3. Explain system architecture
        ↓
4. Explain Linux character driver
        ↓
5. Show project structure
        ↓
6. Build the project
        ↓
7. Load the kernel module
        ↓
8. Verify /dev/industrial_monitor
        ↓
9. Run monitoring application
        ↓
10. Demonstrate NORMAL condition
        ↓
11. Demonstrate WARNING condition
        ↓
12. Demonstrate CRITICAL condition
        ↓
13. Demonstrate recovery to NORMAL
        ↓
14. Show driver statistics
        ↓
15. Show dmesg kernel logs
        ↓
16. Show application log
        ↓
17. Demonstrate invalid IOCTL rejection
        ↓
18. Explain limitations and future scope

Conclusion
The Linux-Based Industrial Equipment Monitoring and Fault Detection System demonstrates how a custom Linux character device driver can be integrated with a C++ monitoring application to create a software-based industrial monitoring architecture.
The completed system provides sensor monitoring, kernel-user space communication, IOCTL interfaces, fault detection, state transitions, statistics, logging, error handling, testing, and a complete build workflow.
The project satisfies the core requirements of a Linux-based C/C++ system-level project and provides a foundation for future integration with real industrial hardware and advanced monitoring technologies.

## System Documentation

Detailed architecture and UML documentation is available in the `docs/` directory.

- [System Architecture](docs/architecture.md)
- [Class Diagram](docs/class_diagram.md)
- [Sequence Diagram](docs/sequence_diagram.md)
- [State Machine Diagram](docs/state_machine.md)
