# RTOS-Based Hiking Safety System

## 📌 Overview
This project implements a **Real-Time Hiking Safety System** using ESP32 and FreeRTOS.  
It detects deviation from a predefined path and triggers alerts using LED, buzzer, and OLED display.

---

## 🚀 Features
- Real-time path deviation detection
- RTOS-based multitasking (FreeRTOS)
- Event-driven communication (Event Groups)
- OLED display (coordinates + deviation + status)
- LED & buzzer alerts
- MATLAB-generated path simulation

---

## 🧠 System Flow
GPS Data → Deviation Calculation → Event Flag → Alert + Display

---

## 🛠️ Hardware Used
- ESP32
- OLED Display (SSD1306, I2C)
- LED
- Buzzer

---

## 💻 Simulation
Simulated using **Wokwi (ESP32 + FreeRTOS)**

---

## 📊 MATLAB Integration
Path and deviation are generated using MATLAB.

---

## 📁 Files
- `sketch.ino` → Main RTOS code  
- `diagram.json` → Wokwi circuit  
- `matlab/path_generation.m` → Path generation script  

---

Run:

`path_generation.m`

---

## 🎯 Future Scope
- Real GPS integration (NEO-6M)
- GSM alerts (SMS)
- Mobile app tracking
- Map visualization

---

## 👨‍💻 Author
Mohammad Abdul Muqeet
