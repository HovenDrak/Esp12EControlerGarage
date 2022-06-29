#include <IOManager.h>
#include <Arduino.h>
#include <Servo.h>
#include <Const.h>

Variables varIO;
Servo myServo;
int pos;

IOManager::IOManager(){}

void IOManager::pinSetConfig(){
    pinMode(LED_BUILTIN, OUTPUT);
    myServo.attach(varIO.PIN_CMND);
    myServo.write(180);
}

void IOManager::openGarage(){
    for(int move = pos; move >= 0; move -= 2){
        myServo.write(move);              
        delay(15);                      
    }
}

void IOManager::closeGarage(){
    for(int move = pos; move <= 180; move += 2){
        myServo.write(move);         
        delay(15);                      
    }
}

