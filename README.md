Smart Building Automation System (BMS Prototype) using Arduino & Node-RED

A complete IoT-based Smart Building Management System (BMS) prototype designed using Arduino, environmental sensors, and a real-time visualization dashboard built in Node-RED.
This system demonstrates lighting automation, HVAC control, sensor fusion, and live monitoring, similar to technologies used in UAE smart buildings, hotels, commercial facilities, and modern homes.

Project Overview

This project automates and monitors environmental conditions in a smart building setup.
It uses:
Temperature sensor (TMP36)
Ambient light sensor (phototransistor)
PIR motion sensor
Manual override push button

The Arduino reads sensor values, processes automation logic (light + fan control), and sends real-time JSON data to Node-RED.
Node-RED displays this data using gauges, charts, and text indicators.
This demonstrates a complete IoT pipeline:

Sensing → Processing → Automation → Visualization

Features
Automated Light Control
Light turns ON when:
  Ambient light is low
OR motion is detected (PIR sensor)
  Turns OFF automatically when room is bright & no motion.
Automated Fan/HVAC Control
  Fan turns ON when temperature exceeds a threshold (ex. 30°C).
Manual Override
  Physical push button allows switching light ON/OFF even during auto mode.
Real-Time Dashboard (Node-RED)
Includes:
  Temperature Gauge
  Temperature Trend Chart
  Light Intensity display
  Light ON/OFF indicator
  Fan ON/OFF indicator
Hardware Components
  Arduino UNO
  TMP36 Temperature Sensor
  Ambient Light Sensor (Phototransistor)
  PIR Motion Sensor
  Push Button
  220Ω and 10kΩ Resistors
  LEDs for Light & Fan Indicators
Software Stack
  Arduino IDE / TinkerCAD
  Node-RED (Dashboard Nodes)
  JSON Data Handling
  Real-time visualization
  
How to Run the Project
  
  1️⃣ Clone this repository:
  git clone https://github.com/yourusername/smart-building-bms-node-red.git

  2️⃣ Upload Arduino code:
  Open smart_bms.ino in Arduino IDE → Upload to Arduino.

  3️⃣ Import Node-RED Flow:
  Node-RED → Menu → Import → Paste JSON from flow.json.

  4️⃣ Start Node-RED:
  node-red
View dashboard at:
👉 http://localhost:1880/ui

Applications
  Smart Homes
  Hotels & Commercial Buildings
  Industrial Automation
  Energy-efficient BMS Systems
  IoT Prototyping & Research

Skills Demonstrated
    IoT System Design
    Sensor Integration
    Automation Logic
    Node-RED Dashboard
    JSON Data Streams
    Embedded Programming
    Real-Time Monitoring

Perfect for roles in:
    Instrumentation & Control
    IoT Engineering
    BMS Technician/Engineer
    Automation Engineering
    Facilities Management (UAE)
