#include<DesiredData.h>


String getArduinoId()
{
    return ArduinoId;
}

void setArduinoId(String ArduinoId)
{
    ArduinoId = ArduinoId;
}

float getHumidity()
{
    return Humidity;
}

    public
        void setHumidity(float Humidity)
        {
            this.Humidity = Humidity;
        }

    public
        float getTemperature()
        {
            return this.Temperature;
        }

    public
        void setTemperature(float Temperature)
        {
            this.Temperature = Temperature;
        }

    public
        float getLuminousIntensity()
        {
            return this.LuminousIntensity;
        }

    public
        void setLuminousIntensity(float LuminousIntensity)
        {
            this.LuminousIntensity = LuminousIntensity;
        }

    public
        float getSoilMoisture()
        {
            return this.SoilMoisture;
        }

    public
        void setSoilMoisture(float SoilMoisture)
        {
            this.SoilMoisture = SoilMoisture;
        }

    public
        float getCO2()
        {
            return this.CO2;
        }

    public
        void setCO2(float CO2)
        {
            this.CO2 = CO2;
        }

    public
        bool isFanInState()
        {
            return this.FanInState;
        }

    public
        void setFanInState(bool FanInState)
        {
            this.FanInState = FanInState;
        }

    public
        bool isFanOutState()
        {
            return this.FanOutState;
        }

    public
        void setFanOutState(bool FanOutState)
        {
            this.FanOutState = FanOutState;
        }

    public
        bool isHumidifierState()
        {
            return this.HumidifierState;
        }

    public
        void setHumidifierState(bool HumidifierState)
        {
            this.HumidifierState = HumidifierState;
        }