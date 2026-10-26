# AeroSense

**Wireless Aircraft Structural Health Monitoring System**  
by **AeroNex Technologies**  
Sri Sairam Engineering College, Chennai | Wadhwani Foundation Venture

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![ESP32](https://img.shields.io/badge/ESP32-ESP--NOW-blue.svg)](https://www.espressif.com/)
[![Platform](https://img.shields.io/badge/Platform-Arduino-green.svg)](https://www.arduino.cc/)

**Team**: Subhiksha S, Nithika M, Saranya N (ECE)

---

## Problem
Aerospace structures are difficult to monitor continuously because of heavy wiring, battery dependence, and limited access to components. This increases maintenance complexity and can delay detection of abnormal vibration or structural conditions.

## Solution
**AeroSense** is a wireless sensor system that detects vibration events on aircraft components and transmits them in real time using ESP-NOW. The prototype uses an SW-420 vibration sensor and two ESP32 boards (transmitter + receiver). Data is streamed to a computer for monitoring, range testing, latency measurement, and packet-delivery evaluation.

### Key Features (Prototype)
- SW-420 vibration event detection
- Wireless transmission via ESP-NOW (low-latency, connectionless)
- Sequence numbering and basic packet-loss statistics
- Real-time Serial monitoring on PC
- Evaluation of communication range, latency, and reliability
- Fully open-source and low-cost

---

## Repository Structure
```
AeroSense/
├── code/
│   ├── transmitter/
│   │   └── AeroSense_Transmitter.ino
│   └── receiver/
│       └── AeroSense_Receiver.ino
├── docs/
│   ├── ARCHITECTURE.md
│   └── CIRCUIT.md
├── tests/
│   └── TEST_CASES.md
├── LICENSE
└── README.md
```

---

## Hardware Required
- 2 × ESP32 development boards
- 1 × SW-420 Vibration Sensor module
- USB cables + jumper wires

See [docs/CIRCUIT.md](docs/CIRCUIT.md) for detailed wiring.

---

## Quick Start

### 1. Clone the repository
```bash
git clone https://github.com/mohanajayan77-wq/AeroSense.git
cd AeroSense
```

### 2. Upload Receiver first
1. Open `code/receiver/AeroSense_Receiver.ino` in Arduino IDE.
2. Select board: **ESP32 Dev Module** (or your specific board).
3. Upload.
4. Open **Serial Monitor at 115200 baud**.
5. Copy the printed **Receiver MAC Address**.

### 3. Configure & Upload Transmitter
1. Open `code/transmitter/AeroSense_Transmitter.ino`.
2. Paste the receiver MAC into this line:
   ```cpp
   uint8_t receiverAddress[] = {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX};
   ```
3. Upload to the second ESP32.

### 4. Test
- Open Serial Monitor on the **Receiver**.
- Tap or vibrate near the SW-420 sensor.
- You should see event packets with sequence number, timestamps, latency estimate, and statistics.

---

## Documentation
- [System Architecture](docs/ARCHITECTURE.md)
- [Circuit & Wiring Guide](docs/CIRCUIT.md)
- [Test Cases & Sample Data](tests/TEST_CASES.md)

---

## Future Scope
- Multi-sensor nodes (acoustic + vibration)
- On-device AI / TinyML anomaly detection
- Energy harvesting / wireless power
- Secure long-range communication
- Mobile or web dashboard
- Aircraft-grade validation studies

---

## License
This project is released under the **MIT License**. See [LICENSE](LICENSE).

---

## Acknowledgments
- Wadhwani Foundation
- Sri Sairam Engineering College, Chennai
- Mentors and peers who supported the project

**Safer skies through smarter monitoring.**
