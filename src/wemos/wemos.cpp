#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;
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

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
    // look at http://bbs.espressif.com/viewtopic.php?t=485
    MDNS.addService("http", "tcp", 80);
  }
}

void updateWIFI() {
  mdns.update();
}
