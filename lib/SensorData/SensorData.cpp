#include<SensorData.h>
#include <ArduinoJson.h>

#define INIT_VALUE -99

//--Logic--//
SensorData::SensorData(String _ArduinoId){
    ArduinoId = _ArduinoId;
    Humidity = INIT_VALUE;
    Temperature = INIT_VALUE;
    LuminousIntensity = INIT_VALUE;
    SoilMoisture = INIT_VALUE;
    CO2 = INIT_VALUE;
}

SensorData::SensorData(){
    ArduinoId = "";
    Humidity = INIT_VALUE;
    Temperature = INIT_VALUE;
    LuminousIntensity = INIT_VALUE;
    SoilMoisture = INIT_VALUE;
    CO2 = INIT_VALUE;
}

String SensorData::toJSON(){
    String JsonString = "";
    DynamicJsonDocument doc(1024);

    if(ArduinoId.length() != 0){
        doc["ArduinoId"] = ArduinoId;
    }
    if( !(isnan(Humidity) || Humidity == INIT_VALUE) ){
        doc["Humidity"] = Humidity;
    } 
    if( !(isnan(Temperature) || Temperature == INIT_VALUE) ){
        doc["Temperature"] = Temperature;
    }
    if( !(isnan(LuminousIntensity) || LuminousIntensity == INIT_VALUE) ){
        doc["LuminousIntensity"] = LuminousIntensity;
    }
    if( !(isnan(SoilMoisture) || SoilMoisture == INIT_VALUE) ){
        doc["SoilMoisture"] = SoilMoisture;
    }
    if( !(isnan(CO2) || CO2 == INIT_VALUE) ){
        doc["CO2"] = CO2;
    }
    serializeJson(doc, JsonString);
    return JsonString;
}

//---GETTER - SETTER---//
String SensorData::getArduinoId(){
    return ArduinoId;
}

void SensorData::setArduinoId(String _ArduinoId){
    ArduinoId = _ArduinoId;
}

float SensorData::getHumidity()
{
    return Humidity;
}

void SensorData::setHumidity(float _Humidity)
{
    Humidity = _Humidity;
    return;
}

float SensorData::getTemperature()
{
    return Temperature;
}


void SensorData::setTemperature(float _Temperature)
{
    Temperature = _Temperature;
}


float SensorData::getLuminousIntensity()
{
    return LuminousIntensity;
}


void SensorData::setLuminousIntensity(float _LuminousIntensity)
{
    LuminousIntensity = _LuminousIntensity;
}


float SensorData::getSoilMoisture()
{
    return SoilMoisture;
}

void SensorData::setSoilMoisture(float _SoilMoisture)
{
    SoilMoisture = _SoilMoisture;
}


float SensorData::getCO2()
{
    return CO2;
}

void SensorData::setCO2(float _CO2)
{
    CO2 = _CO2;
}