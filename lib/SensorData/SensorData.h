#ifndef SENSORDATA_H
#define SENSORDATA_H
#include<Arduino.h>
#include <ArduinoJson.h>

class SensorData
{
private:
    String ArduinoId;
    float Humidity;
    float Temperature;
    float LuminousIntensity;
    float SoilMoisture;
    float CO2;

public:
    SensorData();
    SensorData(String arduino_id);
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