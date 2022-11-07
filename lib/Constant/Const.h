#include <Arduino.h>

class Variables{
    public:

        // -------------X CONST WIFI X------------- // 
        const char* WIFI_SSID = "Root Main";
        const char* WIFI_PASS = "1115062002ja";

        // -------------X CONST MQTT X------------- // 
        const char* MQTT_SERVER = "bbfb08f6f1b84ffebf8b0c4fbbcd0e90.s1.eu.hivemq.cloud";
        const char* USER_MQTT = "userESP8266";
        const char* PASS_MQTT = "67ESP826667";

        const char* TOPIC_CMND_LIGHT = "cmnd/light";
        String SERVICE_LIGHTS[1] = {"light1"};
        String CMND_OFF_LIGHT = "\"desligado\"";
        String CMND_ON_LIGHT = "\"ligado\"";

        
        const char* TOPIC_CMND_GARAGE = "cmnd/garage";
        String CMND_CLOSE_GARAGE = "\"fechado\"";
        String CMND_OPEN_GARAGE = "\"aberto\"";
        String SERVICE_GARAGE = "garage";
        int MQTT_PORT = 8883;

        // -------------X CONST NTP X------------- // 
        const char* NTP_SERVER = "br.pool.ntp.org";
        const long  GMTOFFSET_SEC = 0;
        const long  DAYLIGHTOFFSET_SEC = -10800;

        // -------------X CONST PINS X------------- // 
        int PIN_LIGHTS[1] = {16};
        int PIN_CMND = 5;

        // -------------X CONST API X------------- // 
        String hostApi = "http://api-tcc-oficial.herokuapp.com";
        String pathUpdate = "/automation/update/status";
        String pathStatus = "/automation/status";
        String pathCreateLog = "/create/log";

};     