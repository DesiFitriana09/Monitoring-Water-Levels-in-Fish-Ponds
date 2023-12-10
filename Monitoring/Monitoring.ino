#define BLYNK_TEMPLATE_ID "TMPL6sea6MyLQ"
#define BLYNK_TEMPLATE_NAME "uas"
#define BLYNK_AUTH_TOKEN "SdjK5Kt_nZ4MUttY2gmizZDN_dmH5v5Y"


#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "SdjK5Kt_nZ4MUttY2gmizZDN_dmH5v5Y"; // Masukkan token autentikasi Blynk Anda
char ssid[] = "yaudah pake"; // Masukkan nama jaringan WiFi Anda
char pass[] = "masukaja"; // Masukkan sandi WiFi Anda

const int trigPin = 4;    // Pin Trigger dari sensor HCSR04
const int echoPin = 5;    // Pin Echo dari sensor HCSR04
const int buzzerPin = 19;  // Pin Buzzer

const char* host = "192.168.85.213";
const uint16_t port = 80;
WiFiClient client;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);  // Set pin buzzer sebagai output
}

void loop() {
  Blynk.run();
  
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the pulse duration of the echo pin
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  float distance = duration * 0.034 / 2;

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");

  // Sending distance data to master via WiFi
  String message = "Distance: " + String(distance) + "cm";
  if (client.connected()) {
    client.println(message);
    Serial.println("Sent: " + message);
  } else {
    Serial.println("Connection to master lost. Reconnecting...");
    if (client.connect(host, port)) {
      Serial.println("Reconnected to master.");
    } else {
      Serial.println("Reconnection failed.");
    }
  }

  // Sending distance data to Blynk
  Blynk.virtualWrite(V0, distance);

  // Control the buzzer based on distance
  if (distance < 6) {
    digitalWrite(buzzerPin, HIGH); // Buzzer aktif jika jarak < 6 cm
  } else {
    digitalWrite(buzzerPin, LOW); // Buzzer mati jika jarak >= 6 cm
  }

  delay(1000); // Delay sebelum membaca kembali
}