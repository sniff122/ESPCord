#include "secrets.h"
#include "config.h"
#include "events.h"
#include "event_funcs.h"

#include <Arduino.h>
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>

using namespace websockets;

//#define DEBUG
#ifdef DEBUG
#define DEBUGLOG Serial.println
#else
#define DEBUGLOG(MSG)
#endif

#define INFO
#ifdef INFO
#define INFOLOG Serial.println
#else
#define INFOLOG(MSG)
#endif

WebsocketsClient client;

const String host = "https://discord.com/api/";

unsigned long heartbeatInterval = 0;
unsigned long lastHeartbeatAck = 0;
unsigned long lastHeartbeatSend = 0;

bool hasWsSession = false;
String websocketSessionId;
bool hasReceivedWSSequence = false;
unsigned long lastWebsocketSequence = 0;

String wssGateway;
bool wss_is_connected = false;

unsigned long now;

DynamicJsonDocument doc(4096);

void startOTA() {
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "firmware";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("OTA: Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nOTA: End");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("OTA: Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("OTA: Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();
}

void setupwifi() {
  WiFi.begin(SSID, passphrase);
  Serial.print("Connecting to ");
  Serial.println(SSID);
  for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");

  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Unable to connect to ");
    Serial.println(SSID);
    sleep(5);
    Serial.println("Rebooting....");
    ESP.restart();
  }

  Serial.print("Succesfully connected to ");
  Serial.println(SSID);

  Serial.println();
  Serial.print("IPv4 Address: ");
  Serial.println(WiFi.localIP());
}


void onMessage(WebsocketsMessage msg){
  DEBUGLOG("Got Message: " + msg.data());

  deserializeJson(doc, msg.data());

  if(doc["op"] == 0) // Message
  {
    if(doc.containsKey("s"))
    {
      lastWebsocketSequence = doc["s"];
      hasReceivedWSSequence = true;
    }

    if (doc["t"] == DISCORD_EVENT_READY) {
      websocketSessionId = doc["d"]["session_id"].as<String>();
      hasWsSession = true;
      on_ready(doc);
      INFOLOG("Setting presence");
      doc.clear();
      doc["op"] = 3;
      doc["d"] = doc.createNestedObject();
      doc["d"]["since"] = 91879201;
      doc["d"]["activities"] = doc.createNestedArray();
      doc["d"]["activities"][0] = doc.createNestedArray();
      doc["d"]["activities"][0]["name"] = "I am running on an ESP32!";
      doc["d"]["activities"][0]["type"] = 0;
      doc["d"]["status"] = "online";
      doc["d"]["afk"] = false;

      String msg;

      serializeJson(doc, msg);

      DEBUGLOG("Send: " + msg);
      client.send(msg);
    }
    else if (doc["t"] ==  DISCORD_EVENT_GUILD_MEMBER_ADD) {
      on_member_join(doc);
    }
    else if (doc["t"] == DISCORD_EVENT_GUILD_MEMBER_REMOVE) {
      on_member_remove(doc);
    }
    else if (doc["t"] == DISCORD_EVENT_MESSAGE_CREATE) {
      on_message(doc);
    }
  }
  else if(doc["op"] == 9) // Connection invalid
  {
    client.close();
    hasWsSession = false;
    heartbeatInterval = 0;
  }
  else if(doc["op"] == 11) // Heartbeat ACK
  {
    INFOLOG("Got heartbeat ACK");
    lastHeartbeatAck = now;
  }
  else if(doc["op"] == 10) // Hello
  {
    heartbeatInterval = doc["d"]["heartbeat_interval"];

    if(hasWsSession)
    {
      doc.clear();
      doc["op"] = 6;
      doc["d"] = doc.createNestedObject();
      doc["d"]["token"] = String(bot_token);
      doc["d"]["session_id"] = websocketSessionId;
      doc["d"]["seq"] = String(lastWebsocketSequence, 10);

      String msg;

      serializeJson(doc, msg);

      DEBUGLOG("Send: " + msg);
      client.send(msg);
    }
    else
    {
      doc.clear();
      doc["op"] = 2;
      doc["d"] = doc.createNestedObject();
      doc["d"]["token"] = String(bot_token);
      doc["d"]["intents"] = gateway_intents;
      doc["d"]["properties"] = doc.createNestedObject();
      doc["d"]["properties"]["$os"] = "Espressif";
      doc["d"]["properties"]["$browser"] = "ESP32";
      doc["d"]["properties"]["$device"] = "Espressif ESP32";
      doc["d"]["compress"] = false;
      doc["d"]["large_threshold"] = 1;

      String msg;

      serializeJson(doc, msg);

      DEBUGLOG("Send: " + msg);
      client.send(msg);
    }

    lastHeartbeatSend = now;
    lastHeartbeatAck = now;
  }
};

void onEvent(WebsocketsEvent event, String data) {
  if(event == WebsocketsEvent::ConnectionOpened) {
    Serial.println("Connnection Opened");
  } else if(event == WebsocketsEvent::ConnectionClosed) {
    Serial.println("Connnection Closed");
    Serial.println(data);
    sleep(5);
    Serial.println("Reconnecting to Discord WS Gateway");
    bool wss_is_connected = client.connect("wss://gateway.discord.gg:443/?v=8&encoding=json");
  } else if(event == WebsocketsEvent::GotPing) {
    Serial.println("Got a Ping!");
  } else if(event == WebsocketsEvent::GotPong) {
    Serial.println("Got a Pong!");
  }\
}

void setup() {
  Serial.begin(115500);
  setupwifi();

  startOTA();

  client.onMessage(onMessage);
  client.onEvent(onEvent);

  const char ssl_ca_cert[] PROGMEM = \
    "-----BEGIN CERTIFICATE-----\n" \
    "MIIDdzCCAl+gAwIBAgIEAgAAuTANBgkqhkiG9w0BAQUFADBaMQswCQYDVQQGEwJJ\n" \
    "RTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJlclRydXN0MSIwIAYD\n" \
    "VQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTAwMDUxMjE4NDYwMFoX\n" \
    "DTI1MDUxMjIzNTkwMFowWjELMAkGA1UEBhMCSUUxEjAQBgNVBAoTCUJhbHRpbW9y\n" \
    "ZTETMBEGA1UECxMKQ3liZXJUcnVzdDEiMCAGA1UEAxMZQmFsdGltb3JlIEN5YmVy\n" \
    "VHJ1c3QgUm9vdDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKMEuyKr\n" \
    "mD1X6CZymrV51Cni4eiVgLGw41uOKymaZN+hXe2wCQVt2yguzmKiYv60iNoS6zjr\n" \
    "IZ3AQSsBUnuId9Mcj8e6uYi1agnnc+gRQKfRzMpijS3ljwumUNKoUMMo6vWrJYeK\n" \
    "mpYcqWe4PwzV9/lSEy/CG9VwcPCPwBLKBsua4dnKM3p31vjsufFoREJIE9LAwqSu\n" \
    "XmD+tqYF/LTdB1kC1FkYmGP1pWPgkAx9XbIGevOF6uvUA65ehD5f/xXtabz5OTZy\n" \
    "dc93Uk3zyZAsuT3lySNTPx8kmCFcB5kpvcY67Oduhjprl3RjM71oGDHweI12v/ye\n" \
    "jl0qhqdNkNwnGjkCAwEAAaNFMEMwHQYDVR0OBBYEFOWdWTCCR1jMrPoIVDaGezq1\n" \
    "BE3wMBIGA1UdEwEB/wQIMAYBAf8CAQMwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3\n" \
    "DQEBBQUAA4IBAQCFDF2O5G9RaEIFoN27TyclhAO992T9Ldcw46QQF+vaKSm2eT92\n" \
    "9hkTI7gQCvlYpNRhcL0EYWoSihfVCr3FvDB81ukMJY2GQE/szKN+OMY3EU/t3Wgx\n" \
    "jkzSswF07r51XgdIGn9w/xZchMB5hbgF/X++ZRGjD8ACtPhSNzkE1akxehi/oCr0\n" \
    "Epn3o0WC4zxe9Z2etciefC7IpJ5OCBRLbf1wbWsaY71k5h+3zvDyny67G7fyUIhz\n" \
    "ksLi4xaNmjICq44Y3ekQEe5+NauQrz4wlHrQMz2nZQ/1/I6eYs9HRCwBXbsdtTLS\n" \
    "R9I4LtD+gdwyah617jzV/OeBHRnDJELqYzmp\n" \
    "-----END CERTIFICATE-----\n";

  client.setCACert(ssl_ca_cert);

  bool wss_is_connected = client.connect("wss://gateway.discord.gg:443/?v=8&encoding=json");
}


void loop() {
  client.poll();
  now = millis();
  if (heartbeatInterval > 0) {
    if (now > lastHeartbeatSend + heartbeatInterval) {
      INFOLOG("Sending heartbeat");
      if (hasReceivedWSSequence) {
        doc.clear();
        doc["op"] = 1;
        doc["d"] = String(lastWebsocketSequence, 10);

        String smsg;

        serializeJson(doc, smsg);

        DEBUGLOG("Send: " + smsg);
        client.send(smsg);
      } else {
        doc.clear();
        doc["op"] = 1;
        doc["d"] = NULL;

        String smsg;

        serializeJson(doc, smsg);

        DEBUGLOG("Send: " + smsg);
        client.send(smsg);
      }
      lastHeartbeatSend = now;
    }
    if (lastHeartbeatAck > lastHeartbeatSend + (heartbeatInterval / 2)) {
      INFOLOG("Heartbeat ack timeout");
      client.close();
      heartbeatInterval = 0;
      INFOLOG("Rebooting in 5 seconds...");
      sleep(5);
      INFOLOG("Rebooting now!");
      ESP.restart();
    }
  }
  ArduinoOTA.handle();
}
