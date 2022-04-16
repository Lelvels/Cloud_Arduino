#ifndef REPORTEDDATA_H
#define REPORTEDDATA_H
#include <ArduinoJson.h>

class ReportedData
{
private:
    String ArduinoId;
    float Humidity;
    float Temperature;
    float LuminousIntensity;
    float SoilMoisture;
    float CO2;

public:
    ReportedData();
    ReportedData(String arduino_id);
    String getArduinoId();
    float getHumidity();
    bool setHumidity(float _Humidity);
    float getTemperature();
    bool setTemperature(float _Temperature);
    float getLuminousIntensity();
    bool setLuminousIntensity(float _LuminousIntensity);
    float getSoilMoisture();
    bool setSoilMoisture(float _SoilMoisture);
    float getCO2();
    bool setCO2(float _CO2);
};

#endif