# 🏎️ Embedded Vehicle Edge Node (Simulator)

> A production-grade, event-driven automotive edge node simulator built with Modern C++, FreeRTOS (POSIX), and SocketCAN.

## 📌 Project Overview
As physical hardware can often be a bottleneck for continuous software development and CI/CD pipelines, this project abstracts the hardware layer to simulate a critical Electronic Control Unit (ECU) entirely on a Linux host machine. 

This repository demonstrates the architecture of a **safety-critical embedded system** without requiring physical microcontrollers, showcasing hardware abstraction, real-time operating system concepts, and inter-process communication.

## ⚙️ Core Technologies & Concepts
* **Language:** Modern C++ (C++14/17)
* **RTOS:** FreeRTOS (POSIX Port) for thread management and real-time task scheduling.
* **Communication:** SocketCAN (`vcan0`) for virtual automotive bus communication.
* **Architecture:** Event-Driven Architecture (Command Dispatcher, Event Bus).
* **Build System:** CMake
* **Quality Assurance:** Host-based Unit Testing (Unity/GTest) & CI/CD via GitHub Actions.

## 🚀 Features (Work in Progress)
- [ ] **CMake Build System** setup for modular compilation.
- [ ] **FreeRTOS POSIX Integration** to run real-time tasks as Linux processes.
- [ ] **Thread-Safe C++ Wrappers** for FreeRTOS primitives (Queues, Mutexes, Semaphores).
- [ ] **SocketCAN Interface** for reading and decoding virtual vehicle telemetry.
- [ ] **Sensor Data Processing Task** (e.g., filtering raw noisy signals).

---
*Developed by [Wassim ABDALLAH](https://www.linkedin.com/in/abdallah-wassim-b88a95234/) - Embedded Systems Engineer*
