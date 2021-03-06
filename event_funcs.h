#ifndef EVENT_FUNCS_H_
#define EVENT_FUNCS_H_

#include <ArduinoJson.h>
#include <Arduino.h>
#include "utils.h"


void on_ready(DynamicJsonDocument payload) {
  Serial.println("SUCCESSFULLY connected to gateway as: " + payload["d"]["user"]["username"].as<String>() + "#" + payload["d"]["user"]["discriminator"].as<String>() + "!");
}

void on_member_join(DynamicJsonDocument payload) {
  String username = payload["d"]["user"]["username"].as<String>() + "#" + payload["d"]["user"]["discriminator"].as<String>();
  String user_avatar = "https://cdn.discordapp.com/avatars/" + payload["d"]["user"]["id"].as<String>() + "/" + payload["d"]["user"]["avatar"].as<String>() + ".png";
  Serial.println("A NEW MEMBER JOINED! " + username);
}

void on_member_remove(DynamicJsonDocument payload) {
  Serial.println("Member left :( " + payload["d"]["user"]["username"].as<String>() + "#" + payload["d"]["user"]["discriminator"].as<String>());
}

void on_message(DynamicJsonDocument payload) {
  if (payload["d"]["author"]["bot"]) {
    return;
  }
  Serial.println("New Message from '"+ payload["d"]["author"]["username"].as<String>() + "#" + payload["d"]["author"]["discriminator"].as<String>() + "': " + payload["d"]["content"].as<String>());
  String MessageContent = payload["d"]["content"];
  if (MessageContent == "esp.ping") {
    send_message(payload["d"]["channel_id"], "Hello from the ESP32!");
  }
}

#endif
