#include <Arduino.h>

class IOManager{
    public:
        IOManager();
        void pinSetConfig();
        void openGarage(String user);
        void closeGarage(String user);
        void cmndLight(int light, String cmnd, String user);
};