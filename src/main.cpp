#include <Arduino.h>
#include <DHT.h>
#include <ReportedData.h> 
#include <DesiredData.h>

#define DHTPIN 2
#define DHTTYPE DHT22

const char ARDUINO_ID[6] = "AR01";
String send_msg = "";
String receive_msg = "";

DHT dht(DHTPIN, DHTTYPE);
ReportedData reported(ARDUINO_ID);
DesiredData desired(ARDUINO_ID);

void setup() {
  Serial.begin(9600);
  dht.begin();
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
}

void loop() {
  Serial.println("AR01");
  //Reading data from sensor
  float temp_Reported = dht.readTemperature();
  float humid_Reported = dht.readHumidity();
  receive_msg = "";

  //Sending sensor data to the rasberry
  if (isnan(humid_Reported) || isnan(temp_Reported)) {
    Serial.println(F("SENSOR_ERR"));
  } else {
    //SEND REPORTED DATA THEN RECEIVE SEND DATA
    if(Serial.available() > 0){
      receive_msg = Serial.readStringUntil('\n');
      receive_msg.trim();
      Serial.print("Arduino got: ");
      Serial.println(receive_msg);
      int check = receive_msg.equals("ACK");
      Serial.print("Check got: ");
      Serial.println(check);

      if (!check) {
        reported.setTemperature(temp_Reported);
        reported.setHumidity(humid_Reported);
        String jsonString = reported.toJSON();
        Serial.println(jsonString);
        Serial.println("STOP");
      } else {     
        Serial.println("Arduino is processing data");
      }
    }
  }
}