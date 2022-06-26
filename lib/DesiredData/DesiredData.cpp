#include<DesiredData.h>
#define INIT_VALUE 0

DesiredData::DesiredData(String _DeviceId){
    DeviceId = _DeviceId;
    Temperature = 30;
    MinHumidity = 90;
    MaxHumidity = 98;
    MinCO2 = 1000; //ppm 
    MaxCO2 = 3000;
    LedState = true;
    Disable = false;
}
//GETTER - SETTER
String DesiredData::getDeviceId()
{
    return DeviceId;
}

float DesiredData::getMaxHumidity()
{
    return MaxHumidity;
}

bool DesiredData::setMaxHumidity(float maxHumidity)
{
    if(maxHumidity >= MinHumidity && maxHumidity <= 98){
        MaxHumidity = maxHumidity;
        return true;
    }
    return false;
}

float DesiredData::getMinHumidity()
{
    return MinHumidity;
}

bool DesiredData::setMinHumidity(float minHumidity)
{
    if(minHumidity >= 0 && minHumidity <= MaxHumidity){
        MinHumidity = minHumidity;
        return true;
    }
    return false;
}

float DesiredData::getTemperature()
{
    return Temperature;
}

bool DesiredData::setTemperature(float _Temperature)
{
    if(_Temperature >= 0 && _Temperature <= 40){
        Temperature = _Temperature;
        return true;
    }
    return false;
}

float DesiredData::getMinCO2()
{
    return MinCO2;
}

bool DesiredData::setMinCO2(float minCO2)
{
    if(minCO2 >= 300 && minCO2 <= MaxCO2){
        MinCO2 = minCO2;
        return true;
    }
    return false;
}

float DesiredData::getMaxCO2()
{
    return MaxCO2;
}

bool DesiredData::setMaxCO2(float maxCO2)
{
    if(maxCO2 >= MinCO2 && maxCO2 <= 10000){
        MaxCO2 = maxCO2;
        return true;
    }
    return false;
}

bool DesiredData::getLedState()
{
    return LedState;
}

void DesiredData::setLedState(bool _LedState)
{
    LedState = _LedState;
}

bool DesiredData::isDisable()
{
    return Disable;
}

void DesiredData::setDisable(bool _Disable)
{
    Disable = _Disable;
}