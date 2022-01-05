#ifndef UTILS_H_
#define UTILS_H_

#include <ArduinoJson.h>
#include <Arduino.h>
#include <HTTPClient.h>
//#include "config.h"
//#include "secrets.h"

HTTPClient httpclient;
DynamicJsonDocument jdoc(1024);

const String dhost = "https://discord.com/api";


DynamicJsonDocument send_message(String channel_id, String message) {
  httpclient.begin(dhost + "/channels/" + channel_id + "/messages");
  httpclient.addHeader("Authorization", "Bot " + String(bot_token));
  httpclient.addHeader("User-Agent", "ESPCord (https://sniff122.tech, v1.0)");
  httpclient.addHeader("Content-Type", "application/json");

  int responseCode = httpclient.POST("{\"content\": \"" + message + "\"}");

  String response;

  if (responseCode == 200) {
    String response = httpclient.getString();
  } else {
    Serial.print("Failed to send message! : ");
    Serial.println(responseCode);
    String response = httpclient.getString();
    Serial.println(response);
  }
  httpclient.end();

  deserializeJson(jdoc, response);
  return jdoc;
}

#endif