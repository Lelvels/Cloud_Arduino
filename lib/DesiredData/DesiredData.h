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
        DesiredData();
        DesiredData(String _ArduinoId);
        void DeserializeJsonDesiredData(String json);

        String getArduinoId();
        void setArduinoId(String _ArduinoId);

        float getHumidity();
        void setHumidity(float _Humidity);

        float getTemperature();
        void setTemperature(float _Temperature);

        float getSoilMoisture();
        void setSoilMoisture(float _SoilMoisture);
        float getCO2();
        void setCO2(float _CO2);
        bool isFanInState();
        void setFanInState(bool _FanInState);
        bool isFanOutState();
        void setFanOutState(bool _FanOutState);
        bool isHumidifierState();
        void setHumidifierState(bool _HumidifierState);
        bool isLedState();
        void setLedState(bool _LedState);
};

#endif