#include <Arduino.h>
#include <DHT.h>
#include<SensorData.h>
#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  String id = "AR01";
  float humid = dht.readHumidity();
  float temp = dht.readTemperature();
  float light = 120.23;
  SensorData sensorData(id);

  if (isnan(humid) || isnan(temp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  } else {
    sensorData.setTemperature(humid);
    sensorData.setHumidity(temp);
    sensorData.setLuminousIntensity(light);
    String jsonString = sensorData.toJSON();
    Serial.println(jsonString);
  }
  
  delay(5000);
}