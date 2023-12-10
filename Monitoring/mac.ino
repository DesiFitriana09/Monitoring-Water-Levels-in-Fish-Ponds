#include <WiFi.h>
const char* ssid = "yaudah pake";
const char* password = "masukaja";
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { // Perbaikan pada bagian ini
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
}
void loop() {
}
