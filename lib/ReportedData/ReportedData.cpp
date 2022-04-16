#include<ReportedData.h>

#define INIT_VALUE 0

//--Logic--//
ReportedData::ReportedData(String _ArduinoId){
    ArduinoId = _ArduinoId;
    Humidity = INIT_VALUE;
    Temperature = INIT_VALUE;
    LuminousIntensity = INIT_VALUE;
    SoilMoisture = INIT_VALUE;
    CO2 = INIT_VALUE;
}

//---GETTER - SETTER---//
String ReportedData::getArduinoId(){
    return ArduinoId;
}

float ReportedData::getHumidity()
{
    return Humidity;
}

bool ReportedData::setHumidity(float _Humidity)
{
    Humidity = _Humidity;
    return true;
}

float ReportedData::getTemperature()
{
    return Temperature;
}


bool ReportedData::setTemperature(float _Temperature)
{
    Temperature = _Temperature;
    return true;
}


float ReportedData::getLuminousIntensity()
{
    return LuminousIntensity;
}


bool ReportedData::setLuminousIntensity(float _LuminousIntensity)
{
    LuminousIntensity = _LuminousIntensity;
    return true;
}


float ReportedData::getSoilMoisture()
{
    return SoilMoisture;
}

bool ReportedData::setSoilMoisture(float _SoilMoisture)
{
    SoilMoisture = _SoilMoisture;
    return true;
}


float ReportedData::getCO2()
{
    return CO2;
}

bool ReportedData::setCO2(float _CO2)
{
    CO2 = _CO2;
    return true;
}