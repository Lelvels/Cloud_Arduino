#ifndef DESIREDDATA_H
#define DESIREDDATA_H
#include<Arduino.h>

class DesiredData{
    private:
        String ArduinoId;
        float Humidity;
        float Temperature;
        float LuminousIntensity;
        float SoilMoisture;
        float CO2;
        bool FanInState;
        bool FanOutState;
        bool HumidifierState;
    public:
        
};

#endif