

// TODO: remove these, and replace with Arduino library versions.

// Seems like an odd choice to not abstract this into an implementation of the Arduino Webserver
// from https://github.com/platformio/platformio-examples/tree/develop/espressif/esp8266-webserver

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "webserver.h"

ESP8266WebServer server(80);

void addHandler(const char *url, const char *content_type, handler fn) {
  Serial.printf("\nhandler: (%s) -> %s\n", url, fn()->c_str());

  server.on(url, [=](){
    String *m = fn();
    const char *msg = m->c_str();
    Serial.printf(msg);
    server.send(200, content_type, msg);
    delete m;
  });
}

String *NotFoundMessage() {
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
  return new String(message);
}

void setupWebserver(handler handleNotFound) {
  server.onNotFound([=](){
    const char *msg = handleNotFound()->c_str();
    Serial.printf("404\n");
    server.send(404, "text/plain", msg);
  });

  server.begin();
}

void updateWebserver() {
  server.handleClient();
}
