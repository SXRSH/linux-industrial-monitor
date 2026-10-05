# System Architecture

## Overview

The system is a Linux-based industrial equipment monitoring and fault detection system implemented using C and C++ with a custom Linux character device driver.

The system consists of a sensor simulation layer, monitoring application, fault detection module, Linux character device driver, kernel communication, and logging.

## Architecture Diagram

```mermaid
flowchart TD
    A[Sensor Simulator] --> B[Monitoring Application]
    B --> C[Fault Detection]
    B --> D[IOCTL Interface]
    D --> E[Character Device Driver]
    E --> F[Linux Kernel]
    F --> E
    E --> D
    D --> B
    B --> G[Logging]
