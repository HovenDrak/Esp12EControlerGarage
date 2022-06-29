#include <CertStoreBearSSL.h>
#include <PubSubClient.h>
#include <MqttManager.h>
#include <ESP8266WiFi.h>
#include <IOManager.h>
#include <LittleFS.h>
#include <Arduino.h>
#include <Const.h>

BearSSL::CertStore certStore;
WiFiClientSecure espClient;
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

  if(top.equals(varMqtt.TOPIC_CMND_GARAGE)){
    if(msg.equals(varMqtt.CMND_OPEN_GARAGE)){
      Serial.println("[ESP8266] COMANDO FECHAR PORTAO");
      ioControl.openGarage();

    } else if(msg.equals(varMqtt.CMND_CLOSE_GARAGE)){
      Serial.println("[ESP8266] COMANDO ABRIR PORTAO");
      ioControl.closeGarage();
                 
    }
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
    
    if (client -> connect(clientId.c_str(), "userESP8266", "67Esp826667")) {
      Serial.println("CONECTADO!!!");
      client -> subscribe(varMqtt.TOPIC_CMND_GARAGE);
      
    } else if(client -> state() == -2){
      Serial.println("[MQTT] FALHOU, STATE = -2");
      Serial.println("[ESP8266] REINICIANDO ESP...");
      ESP.restart();
      
    }else {
      Serial.print("[MQTT] FALHOU, STATE = ");
      Serial.print(client -> state());
      Serial.println(" PROXIMA TENTATIVA EM 5s...");
      delay(5000);
    }
  }
}

void MqttManager::mqttRun(){
    if(!client -> connected()){ 
        reconnect();
    } 
    client -> loop();
}

