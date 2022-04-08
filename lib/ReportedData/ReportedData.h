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
    String toJSON();
    String getArduinoId();
    void setArduinoId(String _ArduinoId);
    float getHumidity();
    void setHumidity(float _Humidity);
    float getTemperature();
    void setTemperature(float _Temperature);
    float getLuminousIntensity();
    void setLuminousIntensity(float _LuminousIntensity);
    float getSoilMoisture();
    void setSoilMoisture(float _SoilMoisture);
    float getCO2();
    void setCO2(float _CO2);
};

#endif