# AeroSense Test Cases & Sample Data

## Functional Test Cases

### TC-01: Basic Vibration Detection & Transmission
- **Setup**: Both ESP32s powered, correct MAC configured, Serial Monitor open on receiver (115200 baud).
- **Action**: Gently tap or vibrate near the SW-420 sensor.
- **Expected**: Receiver prints a new event with increasing sequence number and "Vibration: DETECTED".
- **Pass Criteria**: Event appears within < 100 ms of the physical vibration (subjective observation).

### TC-02: Packet Sequence Integrity
- **Setup**: Generate 20–30 vibration events.
- **Expected**: Sequence numbers increase monotonically with no large gaps under good conditions.
- **Pass Criteria**: Estimated Packets Lost remains 0 or very low.

### TC-03: Communication Range Evaluation
- **Setup**: Start at 1 m line-of-sight, then increase distance in 2–5 m steps. Optionally add obstacles.
- **Expected**: Reliable delivery up to a certain range; packet loss increases beyond it.
- **Record**: Maximum reliable range and conditions (LOS / NLOS).

### TC-04: Latency Observation
- **Setup**: Observe "Approx Latency (ms)" field on receiver.
- **Note**: Absolute latency is not precise without clock sync, but relative values and consistency can be compared.
- **Pass Criteria**: Latency remains relatively stable under good RF conditions.

### TC-05: Continuous Operation
- **Setup**: Leave system running for 10–15 minutes with occasional vibrations.
- **Expected**: No crashes, continuous reception, counters keep increasing.
- **Pass Criteria**: Stable Serial output, no resets.

### TC-06: No False Positives (Idle)
- **Setup**: Sensor in quiet environment for 2 minutes.
- **Expected**: No (or very few) spontaneous events.
- **Pass Criteria**: Idle false-trigger rate is acceptable for demonstration.

## Sample Receiver Serial Output

```
Receiver MAC Address: 24:6F:28:AA:BB:CC
Copy this MAC into the transmitter sketch!

AeroSense Receiver Ready
Listening for vibration events from transmitter...

----------------------------------------
Event #: 0
Vibration: DETECTED
TX Timestamp: 12450
RX Timestamp: 12478
Approx Latency (ms): 28
Packets Received: 1
Estimated Packets Lost: 0
----------------------------------------
----------------------------------------
Event #: 1
Vibration: DETECTED
TX Timestamp: 13120
RX Timestamp: 13145
Approx Latency (ms): 25
Packets Received: 2
Estimated Packets Lost: 0
----------------------------------------
```

## Sample Log (CSV style for analysis)
```csv
sequence,tx_timestamp,rx_timestamp,latency_ms,packets_received,packets_lost
0,12450,12478,28,1,0
1,13120,13145,25,2,0
2,14500,14530,30,3,0
```

## How to Capture Data
1. Open Arduino Serial Monitor on the Receiver (115200 baud).
2. Or use a terminal program / Python `pyserial` script to log to a file.
3. Save the output as evidence for range, latency, and reliability evaluation.
