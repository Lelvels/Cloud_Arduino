#ifndef DESIREDDATA_H
#define DESIREDDATA_H
#include <ArduinoJson.h>

class DesiredData{
    private:
        String DeviceId;
        float Temperature;
        float MinHumidity;
        float MaxHumidity;
        float MinCO2;
        float MaxCO2;
        bool LedState;
        bool Disable;
    public:
        DesiredData(String _DeviceId);
        String getDeviceId();

        float getMinHumidity();
        bool setMinHumidity(float minHumidity);

        float getMaxHumidity();
        bool setMaxHumidity(float maxHumidity);

        float getTemperature();
        bool setTemperature(float _Temperature);

        float getMinCO2();
        bool setMinCO2(float minCO2);

        float getMaxCO2();
        bool setMaxCO2(float maxCO2);

        bool getLedState();
        void setLedState(bool _LedState);

        bool isDisable();
        void setDisable(bool _Disable);
};

#endif