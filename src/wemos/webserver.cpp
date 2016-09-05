

// TODO: remove these, and replace with Arduino library versions.

// Seems like an odd choice to not abstract this into an implementation of the Arduino Webserver
// from https://github.com/platformio/platformio-examples/tree/develop/espressif/esp8266-webserver
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "webserver.h"

#include "rgbled.h"

ESP8266WebServer server(80);

void handleRoot() {
  setG();
  server.send(200, "text/plain", "hello from esp8266!");
  Serial.printf("OK\n");
}

void addHandler(const char *url, handler fn) {

  Serial.printf("\nhandler: (%s) -> %s\n", url, fn());

  server.on(url, [=](){
    const char *msg = fn();
    Serial.printf(msg);
    server.send(200, "text/plain", msg);
  });
}

void handleNotFound(){
  setR();
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.printf("404\n");
}

void setupWebserver() {
  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
    setG();
  });

  server.onNotFound(handleNotFound);

  server.begin();
}

void updateWebserver() {
  server.handleClient();
}
