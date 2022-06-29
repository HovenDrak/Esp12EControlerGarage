#include <DataTimeManager.h>
#include <MqttManager.h>
#include <WifiManager.h>
#include <IOManager.h>
#include <LittleFS.h>
#include <Arduino.h>

DataTimeManager dataTimeManager;
MqttManager mqttManager;
WifiManager wifiManager;
IOManager ioManager;

int verifyWifi;

void setup() {
  Serial.begin(115200);
  delay(500);
  LittleFS.begin();

  wifiManager.wifiCheckConnection();
  dataTimeManager.setDateTime();
  ioManager.pinSetConfig();
  mqttManager.mqttSetConfigs();
}

void loop() {
  mqttManager.mqttRun();

  if((millis() - verifyWifi) >= 20000){
    verifyWifi = millis();
    wifiManager.wifiCheckConnection();
  }
}