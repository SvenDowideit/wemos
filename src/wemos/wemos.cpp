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

#define REPLY_LENGTH 256
char reply[REPLY_LENGTH+1];


const char *wifiInfo() {
  byte mac[6];                     // the MAC address of your Wifi shield
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);

  snprintf(reply, REPLY_LENGTH, "\n \
\nConnected to: %s \
\nIp Adress: %s \
\nsignal strength (RSSI): %d dBm \
\nMAC: %x:%x:%x:%x:%x:%x \
\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str(), WiFi.RSSI(),
mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
  return reply;
}

void setupWIFI(const char *ssid, const char *password) {
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(wifiInfo());
}
