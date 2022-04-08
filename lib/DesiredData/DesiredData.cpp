#include<DesiredData.h>
#define INIT_VALUE -99

DesiredData::DesiredData(){
    ArduinoId = "";
    Humidity = INIT_VALUE;
    Temperature = INIT_VALUE;
    SoilMoisture = INIT_VALUE;
    CO2 = INIT_VALUE;
    FanInState = false;
    FanOutState = false;
    HumidifierState = false;
    LedState = false;
}

DesiredData::DesiredData(String _ArduinoId){
    ArduinoId = _ArduinoId;
    Humidity = INIT_VALUE;
    Temperature = INIT_VALUE;
    SoilMoisture = INIT_VALUE;
    CO2 = INIT_VALUE;
    FanInState = false;
    FanOutState = false;
    HumidifierState = false;
    LedState = false;
}

void DesiredData::DeserializeJsonDesiredData(String Json){
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, Json);
    char id[10];
    ArduinoId.toCharArray(id, 10);
    setTemperature(doc[id]["Temperature"]);
    setHumidity(doc[id]["Humidity"]);
}
//GETTER - SETTER
String DesiredData::getArduinoId()
{
    return ArduinoId;
}

void DesiredData::setArduinoId(String _ArduinoId)
{
    ArduinoId = _ArduinoId;
}

float DesiredData::getHumidity()
{
    return Humidity;
}

void DesiredData::setHumidity(float _Humidity)
{
    Humidity = _Humidity;
}

    
float DesiredData::getTemperature()
{
    return Temperature;
}

void DesiredData::setTemperature(float _Temperature)
{
    Temperature = _Temperature;
}


float DesiredData::getSoilMoisture()
{
    return SoilMoisture;
}


void DesiredData::setSoilMoisture(float _SoilMoisture)
{
    SoilMoisture = _SoilMoisture;
}


float DesiredData::getCO2()
{
    return CO2;
}


void DesiredData::setCO2(float _CO2)
{
    CO2 = CO2;
}


bool DesiredData::isFanInState()
{
    return FanInState;
}


void DesiredData::setFanInState(bool _FanInState)
{
    FanInState = _FanInState;
}


bool DesiredData::isFanOutState()
{
    return FanOutState;
}


void DesiredData::setFanOutState(bool _FanOutState)
{
    FanOutState = _FanOutState;
}


bool DesiredData::isHumidifierState()
{
    return HumidifierState;
}


void DesiredData::setHumidifierState(bool _HumidifierState)
{
    HumidifierState = _HumidifierState;
}


bool DesiredData::isLedState()
{
    return LedState;
}


void DesiredData::setLedState(bool _LedState)
{
    LedState = _LedState;
}