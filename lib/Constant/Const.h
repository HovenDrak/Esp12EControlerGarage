class Variables{
    public:

        // -------------X CONST WIFI X------------- // 
        const char* WIFI_SSID = "devicesdev";
        const char* WIFI_PASS = "kgb8y2kk";

        // -------------X CONST MQTT X------------- // 
        const char* MQTT_SERVER = "bbfb08f6f1b84ffebf8b0c4fbbcd0e90.s1.eu.hivemq.cloud";
        const char* TOPIC_CMND_GARAGE = "cmnd/garage";
        String CMND_CLOSE_GARAGE = "\"fechado\"";
        String CMND_OPEN_GARAGE = "\"aberto\"";
        int MQTT_PORT = 8883;
        

        // -------------X CONST NTP X------------- // 
        const char* NTP_SERVER = "br.pool.ntp.org";
        const long  GMTOFFSET_SEC = 0;
        const long  DAYLIGHTOFFSET_SEC = -10800;

        // -------------X CONST PINS X------------- // 
        int PIN_CMND = 12;

};     