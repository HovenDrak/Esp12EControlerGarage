#include <CertStoreBearSSL.h>
#include <PubSubClient.h>
#include <MqttManager.h>
#include <ESP8266WiFi.h>
#include <ApiManager.h>
#include <IOManager.h>
#include <LittleFS.h>
#include <Arduino.h>
#include <Const.h>
#include <JSON.h>

BearSSL::CertStore certStore;
WiFiClientSecure espClient;
ApiControler apiControl;
MqttManager mqttControl;
PubSubClient * client;
IOManager ioControl;
Variables varMqtt;

MqttManager::MqttManager(){}

void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  String top = String(topic);
  
  for (int i = 0; i < int(length); i++) {
    msg += (char)payload[i];
  }
  Serial.println("[MQTT] Topico: " + top + " Mensagem: " + msg);

  JSONVar msgMqttJson = JSON.parse(msg);

  if (top.equals(varMqtt.TOPIC_CMND_GARAGE)){
    String cmnd = JSON.stringify(msgMqttJson[0]["newState"]);
    String user = JSON.stringify(msgMqttJson[1]["user"]);
    mqttControl.cmndGarage(cmnd, user);
  }
}

void MqttManager::mqttSetConfigs(){
  int numCerts = certStore.initCertStore(LittleFS, PSTR("/certs.idx"), PSTR("/certs.ar"));

  Serial.printf("[ESP8266] NUMERO DE CERTIFICADOS CA: %d\n", numCerts);
  if (numCerts == 0) {
    Serial.printf("[ESP8266] Nenhum certificado encontrado. Você executou certs-from-mozilla.py e carregou o diretório LittleFS antes de executar?\n");
    return;
  }

  BearSSL::WiFiClientSecure *bear = new BearSSL::WiFiClientSecure();
  bear -> setCertStore(&certStore);

  client = new PubSubClient(*bear);
  client -> setServer(varMqtt.MQTT_SERVER, varMqtt.MQTT_PORT);
  client -> setCallback(callback);
}


void reconnect() {
  while (!client -> connected()) {
    Serial.print("[MQTT] TENTANDO SE CONECTAR AO BROKER MQTT, ");
    String clientId = "ESP8266Client - MyClient";
    
    if (client -> connect(clientId.c_str(), varMqtt.USER_MQTT, varMqtt.PASS_MQTT)) {
      Serial.println("CONECTADO!!!");
      client -> subscribe(varMqtt.TOPIC_CMND_GARAGE);
      
    } else if (client -> state() == -2){
      Serial.println("[MQTT] FALHOU, STATE = -2");
      Serial.println("[ESP8266] REINICIANDO ESP...");
      ESP.restart();
      
    } else {
      Serial.print("[MQTT] FALHOU, STATE = ");
      Serial.print(client -> state());
      Serial.println(" PROXIMA TENTATIVA EM 5s...");
      delay(5000);
    }
  }
}

void MqttManager::updateStateMqttApi(String service, String state){
  String topic = "status/" + service;
  Serial.println("[MQTT] ATUALIZANDO STATUS MQTT >>> Service: " + service + " Status: " + state);

  client -> publish(topic.c_str(), state.c_str());
  delay(500);

  apiControl.updateStatus(service, state);
  delay(500);
}

void MqttManager::updateStateMqtt(String topic, String msg){
  client -> publish(topic.c_str(), msg.c_str());
}

void MqttManager::mqttRun(){
  if (!client -> connected()){ 
      reconnect();
  } 
  client -> loop();
}

void MqttManager::cmndGarage(String cmnd, String user){
  if (cmnd.equals(varMqtt.CMND_OPEN_GARAGE)){
    Serial.println("[ESP8266] COMANDO FECHAR PORTAO");
    ioControl.openGarage(user);

  } else if (cmnd.equals(varMqtt.CMND_CLOSE_GARAGE)){
    Serial.println("[ESP8266] COMANDO ABRIR PORTAO");
    ioControl.closeGarage(user);  
  }
}

