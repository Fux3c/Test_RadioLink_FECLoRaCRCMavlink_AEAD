# Teensy Flight Computer Prototype (FCP)

This repository contains the source code for an embedded **Flight Computer Prototype**. Built using the Teensy microcontroller platform, this project simulates the core logic and telemetry operations of a sounding rocket’s avionics system.

---

##  Project Overview

The objective of this project is to model real world rocket flight behavior within a controlled, hardware in the loop environment. The system manages everything from pre flight arming to post flight recovery signaling.

### Core Objectives

- **Altitude Measurement** – High-frequency vertical distance tracking  
- **State Detection** – Autonomous transition between flight phases  
- **Apogee Detection** – Identifying peak altitude for recovery deployment  
- **Deployment Simulation** – Physical triggering of recovery hardware  
- **Real-time Telemetry** – Data streaming to a Ground Station  

---

##  System Architecture

The system follows a linear data-processing pipeline:

Sensors → Flight Logic → Actuators & Telemetry


---

##  Hardware Components

- **Teensy** – High-performance microcontroller acting as the primary flight computer  
- **HC-SR04** – Ultrasonic sensor used to simulate altitude data  
- **DHT11/22** – Temperature sensor for environmental monitoring  
- **Servo Motor** – Simulates mechanical parachute deployment  
- **Buzzer** – Audible signaling for state changes
- **LEDs** – Visual indicators for real-time system status  

---

##  Flight States

The computer operates using a deterministic **Finite State Machine (FSM)**.  

A FSM is a mathematical model where the system can be in exactly one of a finite number of states at any given time.

| State   | Description |
|----------|-------------|
| IDLE     | System initialization and sensor check |
| ARMED    | Ready for launch; waiting for vertical movement |
| BOOST    | Active motor burn and rapid ascent |
| COAST    | Upward travel after motor burnout |
| APOGEE   | Peak altitude detected; parachute deployment triggered |
| DESCENT  | Controlled fall under parachute |
| LANDED   | Motion has ceased; recovery beacon (buzzer) active |

> **Apogee Detection Logic:**  
> Apogee is detected when filtered altitude data transitions from an increasing trend to a decreasing trend.

---

##  Telemetry & Ground Control

Data is transmitted via USB Serial in a comma separated format for processing by a Qt-based Ground Control Station.

### Data Packet Format



This structured stream enables:

- Real time graphing  
- Data logging  
- Flight state monitoring  
- System health visualization  

---

##  Purpose

This project serves as:

- An embedded systems architecture study  
- A flight software prototyping platform  






