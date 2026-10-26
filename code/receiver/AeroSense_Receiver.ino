/*
 * AeroSense - Receiver Node
 * Wireless Aircraft Structural Health Monitoring Prototype
 *
 * Hardware:
 * - ESP32 development board
 * - Connected to PC via USB for serial monitoring
 *
 * Function:
 * - Receives vibration event packets via ESP-NOW
 * - Prints structured data to Serial (for PC monitoring / logging)
 * - Calculates simple latency and keeps packet statistics
 *
 * Team: Subhiksha S, Nithika M, Saranya N
 * College: Sri Sairam Engineering College, Chennai
 * AeroNex Technologies – Wadhwani Foundation Venture
 */

#include <esp_now.h>
#include <WiFi.h>

// Packet structure (must match transmitter)
typedef struct struct_message {
  uint32_t sequence;
  uint32_t timestamp;   // millis() on transmitter when event occurred
  uint8_t  vibration;
  uint8_t  battery;
} struct_message;

struct_message incomingPacket;

// Statistics
uint32_t packetsReceived = 0;
uint32_t lastSequence = 0;
uint32_t packetsLost = 0;

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingPacket, incomingData, sizeof(incomingPacket));

  packetsReceived++;

  // Simple packet loss detection
  if (packetsReceived > 1 && incomingPacket.sequence > lastSequence + 1) {
    packetsLost += (incomingPacket.sequence - lastSequence - 1);
  }
  lastSequence = incomingPacket.sequence;

  // Approximate one-way latency (only meaningful if clocks were synced; useful for relative comparison)
  unsigned long receiveTime = millis();
  long latency = (long)receiveTime - (long)incomingPacket.timestamp;

  // Print structured output for monitoring / logging
  Serial.println("----------------------------------------");
  Serial.print("Event #: ");
  Serial.println(incomingPacket.sequence);
  Serial.print("Vibration: ");
  Serial.println(incomingPacket.vibration ? "DETECTED" : "None");
  Serial.print("TX Timestamp: ");
  Serial.println(incomingPacket.timestamp);
  Serial.print("RX Timestamp: ");
  Serial.println(receiveTime);
  Serial.print("Approx Latency (ms): ");
  Serial.println(latency);
  Serial.print("Packets Received: ");
  Serial.println(packetsReceived);
  Serial.print("Estimated Packets Lost: ");
  Serial.println(packetsLost);
  Serial.println("----------------------------------------");
}

void setup() {
  Serial.begin(115200);
  delay(500);

  // Set device as Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.print("Receiver MAC Address: ");
  Serial.println(WiFi.macAddress());
  Serial.println("Copy this MAC into the transmitter sketch!");
  Serial.println();

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register receive callback
  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("AeroSense Receiver Ready");
  Serial.println("Listening for vibration events from transmitter...");
  Serial.println();
}

void loop() {
  // Everything is handled in the receive callback
  delay(10);
}
