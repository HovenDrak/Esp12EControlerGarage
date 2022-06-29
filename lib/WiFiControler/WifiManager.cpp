#include <ESP8266WiFi.h>
#include <WifiManager.h>
#include <Arduino.h>
#include <Const.h>

Variables varWifi;

WifiManager::WifiManager(){}

void WifiManager::wifiCheckConnection(){
  Serial.print("[ESP8266] VERIFICANDO CONEXAO WIFI... ");
  if (WiFi.status() == WL_CONNECTED){
    Serial.println("CONECTADO!!!");
    return;
  } else{
    Serial.println("DESCONECTADO!!!");
  }
  Serial.print("[ESP8266] CONECTANDO AO WIFI: ");
  Serial.println(varWifi.WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(varWifi.WIFI_SSID, varWifi.WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());

  Serial.println("[ESP8266] WIFI CONECTADO!!!");
  Serial.print("[ESP8266] IP ADDRESS: ");
  Serial.println(WiFi.localIP());
}