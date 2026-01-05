<div align="center">
  
  <h1>Portable Land Parameter Measuring Device (IoT + ML)</h1>

  <p>
    <strong>Smart Soil Analysis for Precision Agriculture</strong> - A portable IoT device that analyzes soil health in real-time using Machine Learning.
  </p>

  <img src="https://img.shields.io/badge/Python-3.9+-3776AB?logo=python&logoColor=white" />
  <img src="https://img.shields.io/badge/Hardware-ESP32-E7352C?logo=espressif&logoColor=white" />
  <img src="https://img.shields.io/badge/ML-Scikit--Learn-F7931E?logo=scikitlearn&logoColor=white" />
  <img src="https://img.shields.io/badge/Framework-Flask-000000?logo=flask&logoColor=white" />
</div>

<br />

## Overview

The **Land Parameter Device (LPD)** addresses the delay and cost associated with traditional soil testing labs. By integrating **IoT sensors** with a **Machine Learning backend**, this device provides farmers and researchers with instant analysis of soil properties.

It captures live environmental data, transmits it to a cloud server, and returns predictions for **pH, Electrical Conductivity (EC), Soil Type, and Suitable Crops** within seconds.

## Features

- **Real-Time Sensing** - Instant reading of Soil Moisture, Soil Temperature, Ambient Temperature, and Humidity.
- **ML-Powered Predictions** - Uses Random Forest & Linear Regression to predict pH, EC, and Crop Suitability.
- **Dual Display Interface** - Data is shown locally on an **LCD screen** and remotely on a **Web Dashboard**.
- **Portable Design** - Battery-powered and compact for easy field usage.
- **Historical Logging** - Automatically saves data points to CSV for long-term soil health tracking.
- **High Accuracy** - Calibrated to deliver ~92% accuracy on crop prediction.

## Tech Stack

- **Microcontroller:** ESP32 (Wi-Fi enabled)
- **Sensors:** Capacitive Soil Moisture Sensor v1.2, Soil Temperature Sensor, LCD Display, DS18B20, Ambient Temperature & Humidity Sensor(DHT11), 
- **Firmware:** C++ (Arduino IDE)
- **Backend API:** Python (Flask)
- **Machine Learning:** Scikit-Learn (Random Forest, Linear Regression)
- **Frontend:** HTML5, CSS3, JavaScript (Fetch API)

## ML Performance

The core of this project is a hybrid Machine Learning pipeline trained on agricultural datasets.

| Parameter | Model Used | Performance Metric |
| :--- | :--- | :--- |
| **Suitable Crop** | Random Forest Classifier | **~92% Accuracy** |
| **Soil Type** | Random Forest Classifier | **~88% Accuracy** |
| **Soil pH** | Linear Regression | **±0.2 Error Margin (MAE)** |
| **Electrical Conductivity** | Linear Regression | **±5% Precision** |

## Prerequisites

Before you begin, ensure you have:

- **Hardware:** ESP32 Dev Kit V1, Sensors (DHT11, Capacitive Moisture, DS18B20), 16x2 I2C LCD.
- **Software:** Arduino IDE, Python 3.x.
- **Libraries:** `WiFi.h`, `HTTPClient.h`, `DHT.h`, `OneWire.h`, `LiquidCrystal_I2C`.
