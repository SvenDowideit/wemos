#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;

void setupMDNS() {
if (mdns.begin("esp8266", WiFi.localIP())) {
  Serial.println("MDNS responder started");
  // look at http://bbs.espressif.com/viewtopic.php?t=485
  MDNS.addService("http", "tcp", 80);
}
}

void updateMDNS() {
mdns.update();
}
