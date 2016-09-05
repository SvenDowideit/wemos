
#include "wemos/wemos.h"
// Each of these is optional for the wemos target
#include "wemos/oled.h"
#include "wemos/rgbled.h"
#include "wemos/webserver.h"
#include "wemos/mdns.h"

#include <Arduino.h>

const char* ssid = "ASUS";
const char* password = "WhatTheHe11";


void setup(void){
  setupRGB();

  setupLED();
  setLED(0);

  Serial.begin(115200);
  Serial.println("");
  Serial.println("Getting started");


  setupWIFI(ssid, password);
  setupMDNS();

  setupWebserver();
  Serial.println("HTTP server started");

  setB();
  Serial.println("blue");
  // Disabling OLED as its breaking RGB - and its not as important to me yet
  //setupOLED();
  //Serial.println("OLED done");
  setWhite();
  Serial.println("ready");

}

void loop(void){
  updateMDNS();
  updateWebserver();
}
