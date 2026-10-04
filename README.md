# Linux-Based Industrial Equipment Monitoring and Fault Detection System

## 1. Project Overview

A Linux-based industrial equipment monitoring and fault detection system implemented using C/C++ and a custom Linux character device driver.

The system simulates and monitors industrial equipment parameters including:

- Temperature
- Vibration
- Motor RPM
- Voltage
- Current

Sensor data is transferred between user space and kernel space through a custom character device driver using IOCTL interfaces.

The system classifies equipment conditions into:

- NORMAL
- WARNING
- CRITICAL

The driver maintains runtime statistics and records fault events and state transitions.

---

## 2. Objectives

- Monitor industrial equipment parameters.
- Implement a custom Linux character device driver.
- Demonstrate user-space to kernel-space communication.
- Implement a Linux character device interface.
- Transfer sensor data using IOCTLs.
- Detect abnormal operating conditions.
- Classify faults based on severity.
- Track state transitions between NORMAL, WARNING, and CRITICAL.
- Maintain driver statistics.
- Record fault events and recovery events.
- Provide automatic sensor simulation.
- Provide manual sensor input.
- Maintain application logs.
- Demonstrate Linux kernel programming and system programming concepts.

---

## 3. Technologies

- C
- C++
- Linux
- Linux Kernel Modules
- Character Device Driver
- IOCTL
- GCC
- G++
- Make
- Git
- GitHub

---

## 4. System Architecture

The system follows a user-space/kernel-space architecture.

```text
+------------------------------------------------------+
|                  USER SPACE                          |
|                                                      |
|  +--------------------+                              |
|  | Monitoring         |                              |
|  | Application        |                              |
|  | industrial_monitor |                              |
|  +---------+----------+                              |
|            |                                         |
|            | IOCTL                                   |
|            | Sensor Data / Fault Reports             |
|            v                                         |
+------------|-----------------------------------------+
             |
             | /dev/industrial_monitor
             |
+------------|-----------------------------------------+
|            v            KERNEL SPACE                  |
|                                                      |
|  +-----------------------------------------------+   |
|  | Industrial Monitor Character Device Driver    |   |
|  |                                               |   |
|  |  - Device management                          |   |
|  |  - Sensor data handling                       |   |
|  |  - IOCTL handling                             |   |
|  |  - Fault event tracking                       |   |
|  |  - Statistics                                 |   |
|  |  - State transition handling                  |   |
|  +-----------------------------------------------+   |
|                                                      |
+------------------------------------------------------+
             |
             v
      Kernel Log / dmesg

             +
             |
             v

      logs/industrial_monitor.log
5. Project Components
5.1 Sensor Layer
The application provides simulated industrial sensor values.
The monitored parameters are:
Parameter	Unit
Temperature	°C
Vibration	mm/s
Motor RPM	RPM
Voltage	         V
Current	         A

Two input modes are supported:
1. Automatic simulation mode
2. Manual sensor input mode

5.2 Linux Character Device Driver
The custom kernel module provides the character device:
/dev/industrial_monitor
The driver handles:
- Device open
- Device close
- Sensor data updates
- Sensor data retrieval
- Driver mode
- Driver reset
- Driver statistics
- Fault reporting

6. IOCTL Interface
The communication between the monitoring application and the kernel driver is implemented using IOCTL commands.
The shared interface is defined in:
include/driver_interface.h
Available IOCTLs:
IOCTL              	Purpose
IOCTL_GET_STATUS	Get driver status
IOCTL_SET_MODE  	Set monitoring mode
IOCTL_RESET     	Reset driver state
IOCTL_GET_SENSOR_DATA	Retrieve sensor data
IOCTL_SET_SENSOR_DATA	Send sensor data
IOCTL_GET_STATS  	Retrieve driver statistics
IOCTL_REPORT_FAULT	Report fault severity

7. Fault Detection
The monitoring application evaluates each sensor parameter independently.
Parameters checked:
- Temperature
- Vibration
- Motor RPM
- Voltage
- Current
Each parameter is classified as:
NORMAL
WARNING
CRITICAL
The overall equipment status is determined from the individual parameter states.
The highest severity condition determines the overall status.
Example:
Temperature : NORMAL
Vibration   : NORMAL
RPM         : WARNING
Voltage     : NORMAL
Current     : NORMAL

Overall Status: WARNING

8. Fault State Transitions
The driver tracks meaningful fault transitions rather than blindly counting every monitoring cycle.
Typical transitions are:
NORMAL
   |
   v
WARNING
   |
   v
CRITICAL
   |
   v
NORMAL

The driver records:
- Total fault events
- Warning events
- Critical events
- Last fault severity
- Last fault timestamp
Recovery to NORMAL is also reported in the kernel log.
Example kernel messages:
NEW WARNING fault event
NEW CRITICAL fault event
equipment recovered to NORMAL

9. Driver Statistics
The driver maintains runtime statistics including:
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

Example:
----------------------------------------
 DRIVER STATISTICS
----------------------------------------
Device Opens       : 2
Device Closes      : 1
Sensor Reads       : 0
Sensor Updates     : 9
IOCTL Requests     : 29
Fault Events       : 6
Warning Events     : 3
Critical Events    : 3
Last Fault Severity: 2
Last Fault Time    : <timestamp>
----------------------------------------

10. Logging
The monitoring application maintains an application log:
logs/industrial_monitor.log

The log records:
- Monitoring session start
- Device initialization
- Monitoring cycles
- Sensor values
- Equipment status
- Warning conditions
- Critical conditions
- Fault events
- Driver statistics
- Driver reset
- Device closure
- Session completion
Example:
Cycle 2 - Temperature=80.00C,
Vibration=5.00mm/s,
RPM=3200,
Voltage=245.00V,
Current=12.00A,
Status=WARNING

11. Automatic Simulation Mode
The default mode automatically cycles through predefined equipment conditions.
Normal condition
Temperature : 65 C
Vibration   : 3 mm/s
RPM         : 2200
Voltage     : 230 V
Current     : 7 A

Expected status:
NORMAL

Warning condition
Temperature : 80 C
Vibration   : 5 mm/s
RPM         : 3200
Voltage     : 245 V
Current     : 12 A

Expected status:
WARNING

Critical condition
Temperature : 100 C
Vibration   : 9 mm/s
RPM         : 3800
Voltage     : 260 V
Current     : 18 A

Expected status:
CRITICAL

The simulation continuously cycles through these conditions.
12. Manual Sensor Input
The application also supports manual sensor input.
Run:
sudo ./industrial_monitor --manual

The application then accepts sensor values from the user instead of using the automatic simulation.
This allows different operating conditions to be tested manually.
13. Build Requirements
The project requires:
- Linux system
- GCC
- G++
- Linux kernel headers
- Make
Verify the kernel version:
uname -r

Verify the compiler:
gcc --version
g++ --version

14. Build the Project
From the project root:
cd ~/industrial-monitor

Build the user-space application:
make

Build the kernel driver:
make driver

Build both components:
make
make driver

15. Clean Build
To remove generated build files:
make clean

Then rebuild:
make
make driver

16. Load the Kernel Driver
Insert the kernel module:
sudo insmod driver/industrial_monitor_driver.ko

Verify that it is loaded:
lsmod | grep industrial_monitor

Verify the character device:
ls -l /dev/industrial_monitor

Expected device:
/dev/industrial_monitor

17. Run the Monitoring Application
Start automatic monitoring:
sudo ./industrial_monitor

The application continuously displays:
NORMAL
WARNING
CRITICAL

Press:
Ctrl+C

to stop monitoring.
The application then:
1. Stops the monitoring loop.
2. Retrieves driver statistics.
3. Resets the driver.
4. Closes the character device.
5. Completes the monitoring session.
18. Run Manual Mode
Run:
sudo ./industrial_monitor --manual

Enter sensor values when prompted.
This can be used to test different fault conditions.
19. Check Kernel Logs
Kernel driver activity can be inspected using:
sudo dmesg | tail -40

Important messages include:
device opened
mode changed to 1
sensor data updated
sensor data requested
NEW WARNING fault event
NEW CRITICAL fault event
equipment recovered to NORMAL
statistics requested
driver reset
device closed

20. Unload the Driver
When the monitoring application is stopped:
sudo rmmod industrial_monitor_driver

Verify:
lsmod | grep industrial_monitor

If there is no output, the module has been unloaded.
21. Testing
The project has been tested for:
Functional Testing
- Character device opening
- Character device closing
- Sensor data transmission
- Sensor data retrieval
- IOCTL communication
- Driver reset
- Statistics retrieval
Fault Testing
- NORMAL condition
- WARNING condition
- CRITICAL condition
- WARNING → CRITICAL transition
- CRITICAL → NORMAL recovery
- Repeated fault transitions
Stress Testing
Repeated monitoring cycles were executed successfully.
Example verified results:
Sensor Updates     : 9
Fault Events       : 6
Warning Events     : 3
Critical Events    : 3

Kernel logs confirmed repeated:
NEW WARNING fault event
NEW CRITICAL fault event
equipment recovered to NORMAL

22. Project Directory Structure
industrial-monitor/
│
├── driver/
│   ├── industrial_monitor_driver.c
│   ├── industrial_monitor_driver_backup.c
│   ├── Makefile
│   └── industrial_monitor_driver.ko
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
├── industrial_monitor
├── driver_test
├── README.md
└── .gitignore

23. User Space to Kernel Space Data Flow
The monitoring process follows this sequence:
Sensor Input
     |
     v
Fault Detection
     |
     v
Determine Severity
     |
     v
IOCTL_SET_SENSOR_DATA
     |
     v
Linux Character Driver
     |
     v
Kernel Driver State
     |
     +--------------------+
     |                    |
     v                    v
GET_SENSOR_DATA      REPORT_FAULT
     |                    |
     +---------+----------+
               |
               v
        Driver Statistics
               |
               v
          Kernel Logs

24. Key Linux Concepts Demonstrated
This project demonstrates practical use of:
- Linux kernel modules
- Character devices
- Device file creation
- Kernel/user-space communication
- IOCTL
- Kernel logging
- Module loading and unloading
- Kernel synchronization concepts
- Driver state management
- Error handling
- C/C++ system programming
- Makefiles
- Linux debugging using dmesg
- Git-based project development
25. Example Monitoring Output
========================================
 INDUSTRIAL EQUIPMENT MONITOR
========================================

[OK] Character device opened
[OK] Monitoring mode enabled

Temperature : 65.00 C [NORMAL]
Vibration   : 3.00 mm/s [NORMAL]
Motor RPM   : 2200 RPM [NORMAL]
Voltage     : 230.00 V [NORMAL]
Current     : 7.00 A [NORMAL]

Overall Status: NORMAL

Warning:
Overall Status: WARNING
[WARNING] Equipment requires attention

Critical:
Overall Status: CRITICAL
[CRITICAL] Immediate equipment attention required

26. Project Outcome
The project successfully demonstrates a Linux-based industrial monitoring architecture in which a user-space monitoring application communicates with a custom Linux kernel character device driver.
The system supports sensor monitoring, fault classification, state-transition detection, kernel statistics, fault reporting, logging, automatic simulation, manual input, and repeated fault testing.
27. Future Improvements
Possible future extensions include:
- Real physical sensor integration
- Persistent database storage
- Web-based monitoring dashboard
- Remote equipment monitoring
- Email/SMS alerts
- Additional industrial sensors
- Configurable thresholds through configuration files
- Systemd-based driver/service startup
- Advanced predictive maintenance using machine learning
- Hardware-based emergency shutdown control

