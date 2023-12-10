#include <WiFi.h>

const char* ssid = "yaudah pake";
const char* password = "masukaja";

WiFiServer server(80);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  server.begin();
  Serial.println("WiFi connected.");
  Serial.println("Waiting for slave connection...");
}

void loop() {
  if (!client.connected()) {
    client = server.available();
  }

  if (client.connected()) {
    while (client.available()) {
      String message = client.readStringUntil('\n');
      Serial.println("Received message from slave: " + message);
    }
    delay(5000);
  }
}
