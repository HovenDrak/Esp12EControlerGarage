#include <Arduino.h>

class MqttManager{
    public:
        MqttManager();
        void updateStateMqttApi(String service, String state);
        void updateStateMqtt(String topic, String msg);
        void cmndGarage(String cmnd, String user);
        void consultAllState();
        void mqttSetConfigs();
        void mqttRun();
};