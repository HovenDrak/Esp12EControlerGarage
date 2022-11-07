#include <MqttManager.h>
#include <ApiManager.h>
#include <IOManager.h>
#include <Arduino.h>
#include <Servo.h>
#include <Const.h>

ApiControler controlApiIO;
MqttManager controlMqttIO;
Variables varIO;
Servo myServo;
int pos;

IOManager::IOManager(){}

void IOManager::pinSetConfig(){
    pinMode(varIO.PIN_LIGHTS[0], OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    myServo.attach(varIO.PIN_CMND);
    myServo.write(180);
}

void IOManager::openGarage(String user){
    for (int move = 180; move >= 0; move -= 2){
        myServo.write(move);              
        delay(15);                      
    }
    controlMqttIO.updateStateMqttApi(varIO.SERVICE_GARAGE, varIO.CMND_OPEN_GARAGE);
    controlApiIO.createEvent("Abrindo Portão", user, "openGarage");
}

void IOManager::closeGarage(String user){
    for (int move = 0; move <= 180; move += 2){
        myServo.write(move);         
        delay(15);                      
    }
    controlMqttIO.updateStateMqttApi(varIO.SERVICE_GARAGE, varIO.CMND_CLOSE_GARAGE);
    controlApiIO.createEvent("Fechando Portão", user, "closeGarage");
}

void IOManager::cmndLight(int light, String cmnd, String user){
    if(cmnd.equals(varIO.CMND_ON_LIGHT)){
        digitalWrite(varIO.PIN_LIGHTS[light], LOW);
        controlApiIO.createEvent("Ligando luz", user, "light" + String(light) + "on");
    } else {
        digitalWrite(varIO.PIN_LIGHTS[light], HIGH);
        controlApiIO.createEvent("Desligando luz", user, "light" + String(light) + "off");
    }
    controlMqttIO.updateStateMqttApi(varIO.SERVICE_LIGHTS[light], cmnd);
}

