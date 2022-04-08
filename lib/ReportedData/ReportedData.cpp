#include<ReportedData.h>

#define INIT_VALUE -99

//--Logic--//
ReportedData::ReportedData(String _ArduinoId){
    ArduinoId = _ArduinoId;
    Humidity = INIT_VALUE;
    Temperature = INIT_VALUE;
    LuminousIntensity = INIT_VALUE;
    SoilMoisture = INIT_VALUE;
    CO2 = INIT_VALUE;
}

ReportedData::ReportedData(){
    ArduinoId = "";
    Humidity = INIT_VALUE;
    Temperature = INIT_VALUE;
    LuminousIntensity = INIT_VALUE;
    SoilMoisture = INIT_VALUE;
    CO2 = INIT_VALUE;
}

String ReportedData::toJSON(){
    String JsonString = "";
    DynamicJsonDocument doc(1024);

    if(ArduinoId.length() != 0){
        doc["ArduinoId"] = ArduinoId;
    }
    if( !(isnan(Temperature) || Temperature == INIT_VALUE) ){
        doc["Temperature"] = Temperature;
    }
    if( !(isnan(Humidity) || Humidity == INIT_VALUE) ){
        doc["Humidity"] = Humidity;
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
String ReportedData::getArduinoId(){
    return ArduinoId;
}

void ReportedData::setArduinoId(String _ArduinoId){
    ArduinoId = _ArduinoId;
}

float ReportedData::getHumidity()
{
    return Humidity;
}

void ReportedData::setHumidity(float _Humidity)
{
    Humidity = _Humidity;
    return;
}

float ReportedData::getTemperature()
{
    return Temperature;
}


void ReportedData::setTemperature(float _Temperature)
{
    Temperature = _Temperature;
}


float ReportedData::getLuminousIntensity()
{
    return LuminousIntensity;
}


void ReportedData::setLuminousIntensity(float _LuminousIntensity)
{
    LuminousIntensity = _LuminousIntensity;
}


float ReportedData::getSoilMoisture()
{
    return SoilMoisture;
}

void ReportedData::setSoilMoisture(float _SoilMoisture)
{
    SoilMoisture = _SoilMoisture;
}


float ReportedData::getCO2()
{
    return CO2;
}

void ReportedData::setCO2(float _CO2)
{
    CO2 = _CO2;
}