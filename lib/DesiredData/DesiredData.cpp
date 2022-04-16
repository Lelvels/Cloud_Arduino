#include<DesiredData.h>
#define INIT_VALUE 0

DesiredData::DesiredData(String _ArduinoId){
    ArduinoId = _ArduinoId;
    Humidity = 80;
    Temperature = 20;
    SoilMoisture = 0; //Tính theo phần trăm
    CO2 = 3000; //ppm //lớn hơn 3000 thì khởi động quạt
    FanInState = false;
    FanOutState = false;
    HumidifierState = false;
    LedState = false;
}
//GETTER - SETTER
String DesiredData::getArduinoId()
{
    return ArduinoId;
}

float DesiredData::getHumidity()
{
    return Humidity;
}

bool DesiredData::setHumidity(float _Humidity)
{
    if(_Humidity >= 20 && _Humidity <= 80){
        Humidity = _Humidity;
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
    if(_Temperature >= 10 && _Temperature <= 40){
        Temperature = _Temperature;
        return true;
    }
    return false;
}


float DesiredData::getSoilMoisture()
{
    return SoilMoisture;
}


bool DesiredData::setSoilMoisture(float _SoilMoisture)
{
    if(_SoilMoisture > 30 && _SoilMoisture < 100){
        SoilMoisture = _SoilMoisture;
        return true;
    }
    return false;
}


float DesiredData::getCO2()
{
    return CO2;
}


bool DesiredData::setCO2(float _CO2)
{
    if(_CO2 >= 1000 && _CO2 <= 10000){
        CO2 = _CO2;
        return true;
    }
    return false;
}


bool DesiredData::getFanInState()
{
    return FanInState;
}


void DesiredData::setFanInState(bool _FanInState)
{
    FanInState = _FanInState;
}


bool DesiredData::getFanOutState()
{
    return FanOutState;
}


void DesiredData::setFanOutState(bool _FanOutState)
{
    FanOutState = _FanOutState;
}


bool DesiredData::getHumidifierState()
{
    return HumidifierState;
}


void DesiredData::setHumidifierState(bool _HumidifierState)
{
    HumidifierState = _HumidifierState;
}


bool DesiredData::getLedState()
{
    return LedState;
}


void DesiredData::setLedState(bool _LedState)
{
    LedState = _LedState;
}