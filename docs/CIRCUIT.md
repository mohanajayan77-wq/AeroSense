# AeroSense Wiring Guide

## Hardware Required
- 2 × ESP32 development boards (e.g., ESP32-DevKitC or NodeMCU-32S)
- 1 × SW-420 Vibration Sensor module
- USB cables for programming and power
- Jumper wires

## Transmitter Wiring (ESP32 + SW-420)

| SW-420 Pin | ESP32 Pin     | Notes                          |
|------------|---------------|--------------------------------|
| VCC        | 3.3V or 5V    | Most modules accept both       |
| GND        | GND           | Common ground                  |
| DO (Digital Out) | GPIO4    | Changeable in code (`VIBRATION_PIN`) |

**Note:** Some SW-420 modules output HIGH on vibration, others are active-LOW. Adjust the logic in the transmitter code if needed.

## Receiver Wiring
- No external sensors required.
- Connect receiver ESP32 to PC via USB (for Serial monitoring and power).

## Power
- Both boards are powered via USB in the current prototype (wired power).
- Future versions will explore battery or wireless power transfer.

## ESP-NOW Setup Steps
1. Upload the **Receiver** sketch first.
2. Open Serial Monitor (115200 baud) → note the printed **Receiver MAC Address**.
3. Copy that MAC into the transmitter sketch:
   ```cpp
   uint8_t receiverAddress[] = {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX};
   ```
4. Upload the **Transmitter** sketch.
5. Open Serial Monitor on the receiver to see live events.

## Tips for Range & Reliability Testing
- Keep both boards powered and in line-of-sight for baseline tests.
- Gradually increase distance and introduce obstacles.
- Record packet loss and latency from the receiver serial output.
