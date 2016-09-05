#include <Arduino.h>
#include <ESP8266WiFi.h>

// The single colour LED on the CPU board
const int led = LED_BUILTIN;
void setupLED() {
  pinMode(led, OUTPUT);
}
void setLED(unsigned short state) {
  digitalWrite(led, state);
}


void setupWIFI(const char *ssid, const char *password) {
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
