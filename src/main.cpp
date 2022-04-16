#include<Arduino.h>
#include<DHT.h>
#include<ArduinoJson.h>
#include<LiquidCrystal_I2C.h>
#include<ReportedData.h>
#include<DesiredData.h>

#define DHTTYPE DHT22
#define DHTPIN 4
#define FAN_IN_PIN 5
#define FAN_OUT_PIN 6
#define HUMID_PIN 10
#define SOIL_PIN_ANALOG A0
#define SOIL_PIN_DIGITAL 8

const char ARDUINO_ID[10] = "AR01";
//Receive string
String command;
//Desired
DesiredData desired(ARDUINO_ID);
//Reported
ReportedData reported(ARDUINO_ID);
//Timing
uint16_t last_sent = 0;
uint16_t last_control = 0;
//JSON ARDUINO
StaticJsonDocument<200> doc;
//Sensor and others
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);


void lcd_display_init(){
  lcd.setCursor(0,0);
  lcd.print("Id:");
  lcd.setCursor(0,1);
  lcd.print("Temp:");
  lcd.setCursor(0,2);
  lcd.print("Humid:");
}

void setup(){
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB
  }
  //pinMode
  dht.begin(); //DHT -> 4
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd_display_init();
}

void loop(){
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();
    DeserializationError error = deserializeJson(doc, command);
    if(error){
      Serial.println("JSON_ERR");
      return;
    } else {
      float desiredTemp = doc["Temperature"];
      desired.setTemperature(desiredTemp);
      float desiredHumid = doc["Humidity"];
      desired.setHumidity(desiredHumid);
    }
  }

  uint16_t current_time = millis();
  
  if(current_time - last_control > 3000){
    //Đo từ cảm biến
    float temp = dht.readTemperature();
    if(isnan(temp)){
      temp = -1;
    }
    reported.setTemperature(temp);

    float humid = dht.readHumidity();
    if(isnan(humid)){
      humid = -1;
    }
    reported.setHumidity(humid);

    //Controlling
    if(humid < desired.getHumidity()){
      digitalWrite(FAN_OUT_PIN, LOW);
      digitalWrite(FAN_IN_PIN, HIGH);
      digitalWrite(HUMID_PIN, HIGH);
    } else {
      digitalWrite(FAN_OUT_PIN, HIGH);
      digitalWrite(HUMID_PIN, LOW);
      digitalWrite(FAN_IN_PIN, LOW);
    }

    //Hiển thị LCD    
    lcd.setCursor(10,0);
    lcd.print(ARDUINO_ID);

    lcd.setCursor(10,1);
    lcd.print(desired.getTemperature());

    lcd.setCursor(10,2);
    lcd.print(desired.getHumidity());

    last_control = current_time;
  }

  //Send reported data
  if(current_time - last_sent > 7000){
    if(reported.getTemperature() < 0 || reported.getHumidity() < 0){
      Serial.println("DHT_ERR");
    } else {
      doc["ArduinoId"] = ARDUINO_ID;
      doc["Temperature"] = reported.getTemperature();
      doc["Humidity"] = reported.getHumidity();
      serializeJson(doc, Serial);
    }
    last_sent = current_time;
  }
}
