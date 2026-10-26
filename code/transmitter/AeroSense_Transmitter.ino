/*
 * AeroSense - Transmitter Node
 * Wireless Aircraft Structural Health Monitoring Prototype
 *
 * Hardware:
 * - ESP32 development board
 * - SW-420 Vibration Sensor (Digital output)
 *
 * Function:
 * - Reads vibration events from SW-420
 * - Sends event packets over ESP-NOW to the receiver
 * - Includes sequence number and timestamp for latency / packet-loss evaluation
 *
 * Team: Subhiksha S, Nithika M, Saranya N
 * College: Sri Sairam Engineering College, Chennai
 * AeroNex Technologies – Wadhwani Foundation Venture
 */

#include <esp_now.h>
#include <WiFi.h>

// ============== CONFIGURATION ==============
// Replace with the MAC address of your RECEIVER ESP32
// Find it by running the receiver sketch once and checking Serial Monitor
uint8_t receiverAddress[] = {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC};  // <-- CHANGE THIS

// SW-420 digital pin
const int VIBRATION_PIN = 4;   // GPIO4 (change if needed)

// Debounce / sensitivity
const unsigned long DEBOUNCE_MS = 50;
unsigned long lastVibrationTime = 0;

// Packet structure
typedef struct struct_message {
  uint32_t sequence;      // Packet sequence number
  uint32_t timestamp;     // millis() when event occurred
  uint8_t  vibration;     // 1 = vibration detected
  uint8_t  battery;       // Placeholder for future battery %
} struct_message;

struct_message outgoingPacket;
uint32_t packetSequence = 0;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);
  pinMode(VIBRATION_PIN, INPUT);

  // Set device as Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.print("Transmitter MAC: ");
  Serial.println(WiFi.macAddress());

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  // Register peer (receiver)
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("AeroSense Transmitter Ready");
  Serial.println("Waiting for vibration events...");
}

void loop() {
  int vibrationState = digitalRead(VIBRATION_PIN);

  // SW-420 typically goes HIGH on vibration (check your module – some are inverted)
  if (vibrationState == HIGH) {
    unsigned long now = millis();
    if (now - lastVibrationTime > DEBOUNCE_MS) {
      lastVibrationTime = now;

      // Prepare packet
      outgoingPacket.sequence  = packetSequence++;
      outgoingPacket.timestamp = now;
      outgoingPacket.vibration = 1;
      outgoingPacket.battery   = 100;  // Placeholder

      // Send via ESP-NOW
      esp_err_t result = esp_now_send(receiverAddress, (uint8_t *)&outgoingPacket, sizeof(outgoingPacket));

      if (result == ESP_OK) {
        Serial.print("Vibration event sent | Seq: ");
        Serial.print(outgoingPacket.sequence);
        Serial.print(" | Time: ");
        Serial.println(outgoingPacket.timestamp);
      } else {
        Serial.println("Error sending the data");
      }
    }
  }

  delay(10);  // Small delay for stability
}
