# Lora-chat

📡 **LoRa-chat** is a simple Arduino-based two-way chat system that uses LoRa (Long Range) radios for communication. It allows users to send and receive messages wirelessly using LoRa modules without requiring Wi-Fi or cellular network.

## Features

- LoRa-based wireless communication using the RH_RF95 driver.
- Bi-directional chat via the Serial Monitor.
- Remote ON/OFF control of connected devices using simple message commands (`ON`, `OFF`).
- RSSI (Received Signal Strength Indicator) logging.
- Lightweight and easy to set up on Arduino-compatible boards.

##  Hardware Requirements

To run this project, you'll need:

- 2x Arduino (Uno, Nano, Mega, etc.)
- 2x LoRa modules (e.g., HopeRF RFM95W)
- Jumper wires
- Breadboard (optional)
- USB cables

###  Pin Connections

| RFM95 Pin | Arduino Pin |
|----------:|-------------|
| VCC       | 3.3V        |
| GND       | GND         |
| DIO0      | 7           |
| NSS (CS)  | 8           |
| SCK       | 13 (SPI)    |
| MISO      | 12 (SPI)    |
| MOSI      | 11 (SPI)    |
| RESET     | 4           |

> ⚠️ Ensure you're powering the RFM95 module with **3.3V**, not 5V, or you may damage the module.

##  Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software)
- [RadioHead Library](http://www.airspayce.com/mikem/arduino/RadioHead/)

###  Install RadioHead Library

You can install it from Arduino Library Manager:

1. Go to **Sketch** → **Include Library** → **Manage Libraries...**
2. Search for **RadioHead**
3. Click **Install**

##  How to Get Started

### Uploading the Code

1. Open the `Lora-chat.ino` file in Arduino IDE.
2. Select the correct board and port:
   - Tools → Board → Your Arduino board (e.g., Arduino Uno)
   - Tools → Port → Your device port
3. Upload the code to **both Arduino boards**.
4. Open the **Serial Monitor** on both devices with a baud rate of **115200**.

### Communication

- Type a message in the Serial Monitor and hit **Enter**. The message will be sent via LoRa.
- Received messages are printed with RSSI for signal quality feedback.
- You can send special commands:
  - `ON`: Turns ON pin 12 (sets it to `LOW`)
  - `OFF`: Turns OFF pin 12 (sets it to `HIGH`)

> This is useful for controlling devices such as LEDs or relays connected to pin 12.

##  Frequency Setting

This project uses **952.2 MHz** as the LoRa frequency:

```cpp
#define RF95_FREQ 952.2
