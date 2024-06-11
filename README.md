# WiFi Controlled and Line Following NodeMCU Bot

## Overview

This project features a versatile bot that can be controlled via WiFi using a NodeMCU microcontroller and an Android application, as well as autonomously follow a line using infrared sensors. The bot can switch between manual control and autonomous line-following mode.

## Features

- **WiFi Control**: Control the bot using an Android device connected to the same network.
- **Line Following**: Autonomous navigation using infrared sensors.
- **Real-time Movement**: Command the bot to move forward, backward, left, and right.
- **User-friendly Interface**: Intuitive Android app for seamless control.
- **Extendable**: Easily extend the bot's functionality with additional sensors or modules.

## Hardware Requirements

- NodeMCU (ESP8266)
- Motor Driver Module (L298N or similar)
- DC Motors and Wheels
- Power Supply (e.g., Battery Pack)
- Chassis for the bot
- Jumper Wires
- Infrared (IR) Sensor Module for line following

## Software Requirements

- Arduino IDE
- NodeMCU board package for Arduino IDE
- Provided Android APK for control

## Setup Instructions

### 1. Hardware Assembly

1. **Motor Connection**:
   - Connect the DC motors to the motor driver module.
   - Connect the motor driver module to the NodeMCU.
   - Ensure the power supply is properly connected to the motor driver module and NodeMCU.

2. **Pin Configuration** (example with L298N):
   - Motor A: IN1 and IN2
   - Motor B: IN3 and IN4
   - NodeMCU Pin Connections:
     - IN1 -> D3
     - IN2 -> D4
     - IN3 -> D6
     - IN4 -> D7
   - Enable Pins (if required) connected to NodeMCU.

3. **IR Sensor Connection**:
   - Connect the IR sensors to the NodeMCU.
   - Example Pin Configuration:
     - Left IR Sensor -> D5
     - Right IR Sensor -> D1

### 2. Software Setup

1. **Arduino IDE Configuration**:
   - Install the latest version of the Arduino IDE from [here](https://www.arduino.cc/en/software).
   - Add the NodeMCU (ESP8266) board to Arduino IDE via the Board Manager.
     - Go to `File` -> `Preferences`
     - Add the following URL to "Additional Boards Manager URLs": `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
     - Go to `Tools` -> `Board` -> `Boards Manager` and install "esp8266".

2. **Library Installation**:
   - Ensure the necessary libraries are installed (e.g., `ESP8266WiFi`, `ESP8266WebServer`,`WifiClient`).

3. **Upload Code to NodeMCU**:
   - Open the provided `Source_code.ino` file in Arduino IDE.
   - Modify the WiFi credentials in the code:
     ```cpp
     const char* ssid = "YOUR_SSID";
     const char* password = "YOUR_PASSWORD";
     ```
   - Connect the NodeMCU to your computer and select the correct port and board from the `Tools` menu.
   - Upload the code to the NodeMCU.

### 3. Android App Setup

1. **Install APK**:
   - Transfer the provided APK file to your Android device.
   - Open the APK file on your Android device and follow the prompts to install it.

## Usage

1. **Power on the bot**.
2. **Connect your Android device** to the same WiFi network as the NodeMCU.
3. **Open the app** on your Android device.
4. **Use the app interface** to switch between manual control and line-following mode.

### Manual Control Mode

- Use the app to control the bot's movements in real time.

### Line Following Mode

- Place the bot on a line (typically a black line on a white surface).
- The bot will use its IR sensors to follow the line autonomously.

## Customization

- **IR Sensor Calibration**: Adjust the IR sensor thresholds in the code to ensure accurate line following.
- **Additional Features**: Integrate more sensors (e.g., ultrasonic sensors for obstacle detection) by expanding the NodeMCU code.

## Troubleshooting

- **No Connection**: Ensure the NodeMCU is correctly connected to the WiFi network and the correct IP address is used in the app.
- **Motor Issues**: Check all connections and ensure the motor driver module is properly powered.
- **Code Upload Failures**: Verify the correct board and port are selected in the Arduino IDE.
- **Line Following Issues**: Ensure the IR sensors are correctly positioned and calibrated.

## Contact

For any issues or inquiries, please open an issue in this repository.

---

Enjoy building and controlling your WiFi-controlled and line-following NodeMCU bot with the provided Android app!
