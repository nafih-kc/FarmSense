# 🌱 FarmSense — IoT-Based Smart Agriculture Monitoring System

A real-time crop monitoring system built with ESP32, Python/Flask, MySQL, and Flutter. Automatically monitors soil moisture, temperature, humidity, and light — and controls a water pump based on live sensor data.

---

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [System Architecture](#system-architecture)
- [Hardware Components](#hardware-components)
- [Software & Tools](#software--tools)
- [Project Structure](#project-structure)
- [Setup & Installation](#setup--installation)
- [How It Works](#how-it-works)
- [Team](#team)

---

## Overview

CROPIQ is a smart agriculture monitoring system designed to help farmers track crop conditions in real time. The ESP32 microcontroller collects environmental data from multiple sensors and sends it to a Flask backend server, which stores the data in a MySQL database. A Flutter mobile app displays live readings and threshold alerts.

---

## Features

- 🌡️ Real-time temperature and humidity monitoring (DHT11)
- 💧 Soil moisture sensing with automatic water pump control
- ☀️ Light detection via LDR sensor
- 📲 Live data display on Flutter mobile app
- 🔔 LED alerts for temperature, humidity, and light thresholds
- 🗄️ Data stored in MySQL database via Python/Flask backend
- 📡 Wireless data transmission over WiFi (HTTP)

---

## System Architecture

```
[ESP32 + Sensors]
       |
       | HTTP POST (WiFi)
       ▼
[Python Flask Server]
       |
       | SQL Queries
       ▼
  [MySQL Database]
       |
       | HTTP GET (JSON)
       ▼
 [Flutter Mobile App]
```

---

## Hardware Components

| Component | Purpose |
|---|---|
| ESP32 | Main microcontroller + WiFi |
| DHT11 | Temperature & humidity sensing |
| Soil Moisture Sensor | Detects soil water level |
| LDR (Light Dependent Resistor) | Detects light/darkness |
| Water Pump | Auto-irrigation based on moisture |
| Blue LED | Temperature threshold alert |
| Green LED | Light status indicator |

---

## Software & Tools

- **Arduino IDE** — ESP32 programming (Embedded C)
- **Python 3 + Flask** — Backend REST API server
- **MySQL** — Sensor data storage
- **Flutter** — Cross-platform mobile application
- **Proteus** — Circuit simulation (design phase)

---

## Project Structure

```
cropiq/
│
├── esp32/
│   └── cropiq_esp32.ino       # ESP32 Arduino code
│
├── backend/
│   └── app.py                 # Python Flask server
│
├── flutter_app/               # Flutter mobile app source
│
└── README.md
```

---

## Setup & Installation

### 1. ESP32 Setup
1. Open `esp32/cropiq_esp32.ino` in Arduino IDE
2. Replace the placeholders with your details:
```cpp
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverName = "http://YOUR_SERVER_IP:5000/test";
```
3. Connect sensors according to pin definitions in the code
4. Upload to ESP32

### 2. Backend Setup
```bash
# Install dependencies
pip install flask pymysql

# Set up MySQL database
CREATE DATABASE sensor_data;
USE sensor_data;
CREATE TABLE readings (
    id INT AUTO_INCREMENT PRIMARY KEY,
    humidity FLOAT,
    temperature FLOAT,
    ldr VARCHAR(10),
    moisture INT,
    date DATE,
    time TIME
);

# Update database credentials in app.py
# Run the server
python app.py
```

### 3. Flutter App Setup
```bash
cd flutter_app
flutter pub get
flutter run
```
> Update the server IP in the Flutter app to match your Flask server address.

---

## How It Works

1. **ESP32** reads sensor values every 5 seconds
2. If soil moisture exceeds threshold (>3000), the **water pump activates automatically**
3. If temperature exceeds 31°C, the **blue LED turns on** as an alert
4. The **green LED** reflects current light status from the LDR
5. All readings are sent via **HTTP POST** to the Flask server
6. Flask stores the data in **MySQL** and serves the latest reading via **HTTP GET**
7. The **Flutter app** fetches and displays live sensor data with alerts

---

## Team

Built by a 5-member team as a diploma final year project at **AWH Polytechnic College, Kuttikattoor** (2025).

| Role | Contributor |
|---|---|
| ESP32 Programming & Team Lead | Nafih KC |
| Flutter Mobile App | Team |
| Flask Backend | Team |
| Hardware Assembly | Team |

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).
