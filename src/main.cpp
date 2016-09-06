#include <WString.h>

#include "wemos/wemos.h"
// Each of these is optional for the wemos target
#include "wemos/oled.h"
#include "wemos/rgbled.h"
#include "wemos/webserver.h"
#include "wemos/mdns.h"
#include <Arduino.h>

const char* ssid = "ASUS";
const char* password = "WhatTheHe11";

String *handleRoot() {
  setG();
  Serial.printf("GET /\nOK\n");
  String start = R"(<!DOCTYPE html>
<html>
<head>
<title>ESP</title>
</head>
<body>
<h1>Hello from a WEMOS D1 mini</h1>
<div>
<ul>)";

  long  fh = ESP.getFreeHeap();
  char  fhc[20];

  ltoa(fh, fhc, 10);
  String heap = "<li>Heap " + String(fhc) + "</li>";

  ltoa( ESP.getFlashChipRealSize(), fhc, 10);
  String flashSize = "<li>Flash size " + String(fhc) + "</li>";

  ltoa( ESP.getSketchSize(), fhc, 10);
  String sketchSize = "<li>Sketch size " + String(fhc) + "</li>";

  ltoa( ESP.getFreeSketchSpace(), fhc, 10);
  String freeSketchSize = "<li>Free Sketch size " + String(fhc) + "</li>";

  String end = R"(</ul>
</div>
</body>
</html>
  )";
  return new String(start +
    heap +
    sketchSize +
    freeSketchSize +
    flashSize +
    end);
}

void setup(void){
  setupRGB();

  setupLED();
  setLED(0);

  Serial.begin(115200);
  Serial.println("");
  Serial.println("Getting started");

  setupWIFI(ssid, password);
  setupMDNS();

  setupWebserver([=](){
    setR();
    return NotFoundMessage();
  });
  addHandler("/", "text/html", handleRoot);
  addHandler("/info", "text/plain", [=](){
    setB();
    return wifiInfo();
  });

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
