#include <DataTimeManager.h>
#include <Arduino.h>
#include <Const.h>
#include <time.h>
#include <TZ.h>

Variables varTime;

DataTimeManager::DataTimeManager(){}

void DataTimeManager::setDateTime(){
    configTime(varTime.GMTOFFSET_SEC, varTime.DAYLIGHTOFFSET_SEC, varTime.NTP_SERVER);

    Serial.print("[ESP8266] AGUARDANDO SINCRONIZACAO DE TEMPO NTP: ");
    time_t now = time(nullptr);
    while (now < 8 * 3600 * 2) {
        delay(100);
        Serial.print(".");
        now = time(nullptr);
    }
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);
    Serial.printf("\n[ESP8266] %s", asctime(&timeinfo));
}