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

String *wifiInfo() {
  byte mac[6];                     // the MAC address of your Wifi shield
  WiFi.macAddress(mac);

  snprintf(reply, REPLY_LENGTH, R"(
Connected to: %s
Ip Adress: %s
signal strength (RSSI): %d dBm
MAC: %x:%x:%x:%x:%x:%x
)", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str(), WiFi.RSSI(),
mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
  return new String(reply);
}

void setupWIFI(const char *ssid, const char *password) {
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(*(wifiInfo()));
}
