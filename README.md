# Air Mouse using Arduino and MPU6050

### Submitted By: Group-11
- Aarya Choudha (2023MMB1403)  
- Akshit Choudhary (2023MMB1406)  
- Daksh Garg (2023MMB1410)  
- Urvashi Walade (2023MEB1396)  
- Yogendra Magdum (2023MEB1401)  

---

## Objective

The goal of this project is to build an **Air Mouse** — a wireless, motion-controlled cursor system — using an **Arduino Uno** and an **MPU6050** (accelerometer + gyroscope) sensor.

By interpreting motion data and converting it into cursor movement, the Air Mouse allows control of a computer without the need for a flat surface, ideal for smart environments and gesture-based interaction.

---

## Components Used

| S.No | Component                   | Purpose |
|------|-----------------------------|---------|
| 1    | Arduino Uno                 | Microcontroller for processing sensor data |
| 2    | MPU6050 Accelerometer + Gyro| Detects hand motion and orientation |
| 3    | Breadboard                  | Circuit prototyping without soldering |
| 4    | Jumper Wires (M-M, M-F)     | Electrical connections between components |
| 5    | Push Buttons (2x)           | Left-click and right-click simulation |
| 6    | 10kΩ Resistors              | Pull-down resistors for stable button input |
| 7    | Micro USB Cable             | Power and serial data transfer |
| 8    | Computer/Laptop             | Receives data and controls cursor via Python |

---

## Circuit Diagram

> A standard connection:
- MPU6050 VCC → 3.3V  
- GND → GND  
- SDA → A4  
- SCL → A5  
- Buttons → D6 (Right Click), D7 (Left Click) with pull-down resistors  
- Arduino connected to PC via USB

---

## Working Principle

- The **MPU6050** detects real-time orientation and motion using gyroscope and accelerometer data.
- **Arduino Uno** reads this data via I2C communication.
- The processed data is sent to a **Python script on the PC** over serial USB.
- The **PC script** moves the cursor using libraries like `pyautogui`.
- Physical **buttons** are used for left and right mouse clicks.

---

## Challenges Faced

| Challenge | Description | Solution |
|----------|-------------|----------|
| MPU6050 not responding | Sensor didn’t provide output | Switched power supply to 3.3V, verified connections |
| Jittery cursor movement | Cursor too shaky or erratic | Added filtering and tuned sensitivity |
| Serial lag | Delay in cursor motion | Optimized Arduino code and flush serial buffer |
| Button debounce | Multiple clicks per press | Added debounce logic using `millis()` function |

---

## Future Enhancements

- Switch to **wireless communication** using **Bluetooth** or **ESP32**
- Add **gesture recognition** to replace mechanical buttons
- Make the device **wearable** (e.g., smart glove, ring)
- Integrate **rechargeable battery** and miniaturized PCB
- Improve **UI/UX** with multi-mode support (presentation, drawing, gaming)

---

## Output Demo

The cursor responds to hand tilt and click buttons effectively simulate mouse actions. The device successfully demonstrates:

- Smooth motion-based cursor control  
- Functional left/right clicks  
- Basic human-computer gesture interaction  

---
