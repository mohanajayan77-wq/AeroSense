# AeroSense System Architecture

## Overview
AeroSense is a wireless structural health monitoring (SHM) prototype for aircraft components. It detects vibration events using a low-cost SW-420 sensor and transmits them wirelessly via ESP-NOW between two ESP32 boards. The receiver streams data to a computer for real-time monitoring, latency measurement, and packet delivery evaluation.

This prototype demonstrates the core wireless sensing layer. Future versions will add AI-based anomaly detection, multi-sensor fusion, energy harvesting, and aircraft-grade certification pathways.

## High-Level Architecture

```
+-------------------+          ESP-NOW          +-------------------+
|   Transmitter     |  -----------------------> |    Receiver       |
|                   |     (2.4 GHz, low latency)|                   |
| ESP32 + SW-420    |                           | ESP32             |
| Vibration Sensor  |                           | USB Serial        |
+-------------------+                           +---------+---------+
                                                          |
                                                          v
                                                 +-----------------+
                                                 | PC / Monitoring |
                                                 | (Serial / Python)|
                                                 +-----------------+
```

## Components (Current Prototype)

| Node          | Hardware                  | Role                                      |
|---------------|---------------------------|-------------------------------------------|
| Transmitter   | ESP32 + SW-420            | Detects vibration events, packs data, sends via ESP-NOW |
| Receiver      | ESP32                     | Receives packets, computes basic stats, streams to PC   |
| Monitoring    | PC (Serial Monitor / script) | Displays events, logs data, evaluates range/latency    |

## Data Packet
```c
typedef struct struct_message {
  uint32_t sequence;    // Monotonic packet ID
  uint32_t timestamp;   // millis() on transmitter
  uint8_t  vibration;   // 1 = event detected
  uint8_t  battery;     // Placeholder for future power monitoring
} struct_message;
```

## Key Metrics Evaluated
- Communication range
- One-way latency (relative)
- Packet delivery / loss rate
- Event detection reliability

## Future Roadmap
- Multi-node sensor mesh
- Acoustic + vibration fusion
- On-device TinyML anomaly detection
- Wireless power / energy harvesting
- Secure encrypted ESP-NOW or alternative long-range radio
- Mobile / web dashboard
- Aircraft integration studies

## Design Principles
- Minimal wiring / battery dependence (prototype still uses wired power)
- Low latency wireless link (ESP-NOW)
- Open-source and low-cost components
- Easy evaluation of communication performance
