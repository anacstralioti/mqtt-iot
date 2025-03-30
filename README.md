# LED Control with AskSensors and Arduino Uno + Ethernet Shield using MQTT

This project demonstrates how to control an LED using **AskSensors** and an **Arduino Uno** with an **Ethernet Shield**, communicating via **MQTT** protocol. The LED will be controlled by publishing commands through the MQTT broker, and the Arduino will subscribe to the topic and turn the LED on or off accordingly.

## Components Required

- Arduino Uno;
- Ethernet Shield;
- LED.

## Setup Instructions

### 1. **Hardware Setup**

- Connect the **Ethernet Shield** to your **Arduino Uno**;
- Connect the **LED** to **pin 8** and **GND** on the Arduino;
- Connect the Ethernet Shield to your router using an Ethernet cable.

### 2. **Software Setup**

#### 2.1 **Install Libraries**

Make sure you have the following library installed in your Arduino IDE:

- **PubSubClient**: It is the MQTT client library for Arduino to handle MQTT communication, you have to install it via Library Manager in Arduino IDE. 

To install **PubSubClient**:
1. Open the **Arduino IDE**.
2. Go to **Sketch** > **Include Library** > **Manage Libraries**.
3. In the Library Manager, search for **PubSubClient** and install it.

#### 2.2 **Code Configuration**

In the code, make the following changes:
- **`username`**: Replace with your AskSensors account username.
- **`subTopic`**: Replace `username` with your actual username and `apiKeyOut` with the API key from your AskSensors account.
- **Static IP**: If you want to use a static IP address (instead of DHCP), replace the `IPAddress ip(10, 197, 12, 226);` line with your preferred IP address.

#### 3. MQTT Setup
- Register at AskSensors (https://www.asksensors.com/) and generate an API key in the AskSensors Dashboard.
- Use the provided topic (actuator/your_username/apiKeyOut) to control the actuator (LED) through the MQTT service.

#### 4. Testing
After uploading the code and ensuring the Ethernet Shield is connected to your network:

- Open the Serial Monitor in the Arduino IDE to check the connection status and see the IP address of the Arduino.

- Subscribe to the actuator/your_username/apiKeyOut topic in the AskSensors platform and publish messages like:

- "module1=1" to turn the LED on and "module1=0" to turn the LED off.

The LED should turn on or off based on the message received via MQTT.
