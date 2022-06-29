#include <Arduino.h>

class MqttManager{
    public:
        MqttManager();
        void mqttSetConfigs();
        void mqttRun();
        void updateStateMqttApi(String service, String state);
        void updateStateMqtt(String topic, String msg);
        void consultAllState();
};