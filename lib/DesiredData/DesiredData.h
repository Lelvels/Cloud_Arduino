#ifndef DESIREDDATA_H
#define DESIREDDATA_H
#include <ArduinoJson.h>

class DesiredData{
    private:
        String ArduinoId;
        float Humidity;
        float Temperature;
        float SoilMoisture;
        float CO2;
        bool FanInState;
        bool FanOutState;
        bool HumidifierState;
        bool LedState;
    public:
        DesiredData(String _ArduinoId);
        String getArduinoId();

        float getHumidity();
        bool setHumidity(float _Humidity);

        float getTemperature();
        bool setTemperature(float _Temperature);

        float getSoilMoisture();
        bool setSoilMoisture(float _SoilMoisture);

        float getCO2();
        bool setCO2(float _CO2);

        bool getFanInState();
        void setFanInState(bool _FanInState);

        bool getFanOutState();
        void setFanOutState(bool _FanOutState);

        bool getHumidifierState();
        void setHumidifierState(bool _HumidifierState);

        bool getLedState();
        void setLedState(bool _LedState);
};

#endif