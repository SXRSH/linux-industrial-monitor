# Project Documentation

This directory contains the design and architecture documentation for the Linux-Based Industrial Equipment Monitoring and Fault Detection System.

## Documents

| Document | Description |
|---|---|
| [System Architecture](architecture.md) | Overall system architecture and component interaction |
| [Class Diagram](class_diagram.md) | Major software classes/modules and their relationships |
| [Sequence Diagram](sequence_diagram.md) | Runtime interaction between application, driver, kernel and fault detector |
| [State Machine Diagram](state_machine.md) | Equipment state transitions between NORMAL, WARNING and CRITICAL |

## System Layers

1. Sensor/Input Layer
2. Monitoring Application
3. Fault Detection Layer
4. Linux Character Device Driver
5. Kernel Space
6. Logging and Statistics Layer
