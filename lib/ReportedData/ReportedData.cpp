#include<ReportedData.h>

#define INIT_VALUE 0

//--Logic--//
ReportedData::ReportedData(String _DeviceId){
    DeviceId = _DeviceId;
    Humidity = INIT_VALUE;
    Temperature = INIT_VALUE;
    SoilMoisture = INIT_VALUE;
    CO2 = INIT_VALUE;
}

//---GETTER - SETTER---//
String ReportedData::getDeviceId(){
    return DeviceId;
}

float ReportedData::getHumidity()
{
    return Humidity;
}

bool ReportedData::setHumidity(float _Humidity)
{
    if(!isnan(_Humidity) && _Humidity >= 0){
        Humidity = _Humidity;
        return true;
    }
    return false;
}

float ReportedData::getTemperature()
{
    return Temperature;
}


bool ReportedData::setTemperature(float _Temperature)
{
    if(!isnan(_Temperature) && _Temperature >= 0){
        Temperature = _Temperature;
        return true;
    }
    return false;
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
    if(!isnan(_CO2) && _CO2 >= 0 && _CO2 <= 10000){
        CO2 = _CO2;
        return true;
    }
    return false;
}