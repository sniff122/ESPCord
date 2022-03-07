#ifndef EVENT_FUNCS_H_
#define EVENT_FUNCS_H_

#include <ArduinoJson.h>
#include <Arduino.h>



#include "utils.h"


DynamicJsonDocument jsondoc(1024);


void on_ready(DynamicJsonDocument payload)
{
  Serial.println("SUCCESSFULLY connected to gateway as: " + payload["d"]["user"]["username"].as<String>() + "#" + payload["d"]["user"]["discriminator"].as<String>() + "!");
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 16);
  display.println("Logged in as: ");
  display.println(payload["d"]["user"]["username"].as<String>());

  display.setCursor(0, 0);
  display.println("Logged In");
  display.display();
}

void on_member_join(DynamicJsonDocument payload)
{
  String username = payload["d"]["user"]["username"].as<String>() + "#" + payload["d"]["user"]["discriminator"].as<String>();
  String user_avatar = "https://cdn.discordapp.com/avatars/" + payload["d"]["user"]["id"].as<String>() + "/" + payload["d"]["user"]["avatar"].as<String>() + ".png";
  Serial.println("A NEW MEMBER JOINED! " + username);
}

void on_member_remove(DynamicJsonDocument payload)
{
  Serial.println("Member left :( " + payload["d"]["user"]["username"].as<String>() + "#" + payload["d"]["user"]["discriminator"].as<String>());
}

void on_message(DynamicJsonDocument payload)
{
  	if (payload["d"]["author"]["bot"])
	  {
		return;
  	}
  	Serial.println("New Message from '"+ payload["d"]["author"]["username"].as<String>() + "#" + payload["d"]["author"]["discriminator"].as<String>() + "': " + payload["d"]["content"].as<String>());
  	String MessageContent = payload["d"]["content"];
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0, 0);
  	display.println("New Message!");
	display.setCursor(0, 16);
	display.println("New message from: ");
	display.print(payload["d"]["author"]["username"].as<String>());
	display.print("#");
	display.println(payload["d"]["author"]["discriminator"].as<String>());
	display.println(MessageContent);
	display.display();
}

#endif
