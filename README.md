# AgriSmart-Greenhouse irrigation system 
## 🌿 About AgriSmart

**AgriSmart** is an integrated IoT solution designed to monitor and manage various environmental and operational aspects of a greenhouse farm. The project comprises three main systems:

- 🌀 **AgriSmart Irrigation System**
- ☀️ **AgriSmart Weather Station**
- 🧪 **AgriSmart Gas Analyzer**

  <h3 align="center">🔧 AgriSmart Schematic Diagram</h3>
<p align="center">
  <img src ="images/Agrismart station Image 2025-07-13 at 09.07.17_ddf1a8b1.jpg" width="600"/>
</p>

Each system is built using **NodeMCU microcontrollers** and a range of sensors and actuators to ensure optimal conditions for plant growth, operational efficiency, and environmental safety.

The goal of AgriSmart is to create a **comprehensive, automated greenhouse management system** using Internet of Things (IoT) technology to improve productivity, optimize resource usage, and enhance security.

### 💧 Irrigation System

- Uses soil moisture sensors to monitor water levels and automate irrigation.
- A DHT11 sensor and **three 5V cooling fans** regulate temperature and humidity inside the greenhouse.
- A **PIR motion sensor** and **buzzer** are integrated for detecting intrusions and alerting the farmer.

    <h3 align="center">🔧 AgriSmart Irrigation system Mobile application</h3>
<p align="center">
  <img src="images/agrismart irrigation app.jpg" width="400"/>
</p>

### ☀️ Weather Station

- Continuously monitors environmental conditions using:
  - Light sensor
  - DHT11 temperature & humidity sensor
  - Rain sensor
- Data is displayed on an **LCD panel** and transmitted to the **Blynk app** for real-time remote monitoring.

### 🧪 Gas Analyzer

- Focuses on **air quality monitoring** inside the greenhouse.
- Uses an **MQ135 gas sensor** to detect harmful gases such as **ammonia (NH₃)** and **carbon dioxide (CO₂)**.
- Sensor data is processed by a NodeMCU and transmitted to the Blynk platform for live monitoring.

Together, these systems help optimize plant development, improve greenhouse management, and ensure safety for both plants and personnel.

<h3 align="center">🔧 AgriSmart Schematic Diagram</h3>
<p align="center">
  <img src="schematics/Agrismart irrigation system scematic diagram  PNG.png" width="600"/>
</p>
