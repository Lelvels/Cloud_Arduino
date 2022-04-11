#include<Arduino.h>
#include<DHT.h>
#include<ArduinoJson.h>
#include<LiquidCrystal_I2C.h>

#define DHTPIN 7
#define DHTTYPE DHT22

const char ARDUINO_ID[10] = "AR01";
String command;
float desiredTemp;
float desiredHumid;
bool send_data;
uint16_t last_sent = 0;

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup(){
  Serial.begin(9600);
  dht.begin();
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB
  }
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  desiredHumid = 0;
  desiredTemp = 0;
  lcd.begin();
  lcd.backlight();
}

void loop(){
  StaticJsonDocument<200> doc;
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();

    DeserializationError error = deserializeJson(doc, command);
    if(error){
      desiredHumid = -1;
      desiredTemp = -1;
      return;
    } else {
      desiredTemp = doc["Temperature"];
      desiredHumid = doc["Humidity"];
    }

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Id:");
    lcd.setCursor(10,0);
    lcd.print(ARDUINO_ID);

    lcd.setCursor(0,1);
    lcd.print("Temp:");
    lcd.setCursor(10,1);
    lcd.print(desiredTemp);

    lcd.setCursor(0,2);
    lcd.print("Humid:");
    lcd.setCursor(10,2);
    lcd.print(desiredHumid);
  }

  uint16_t current_sent = millis();
  if(current_sent - last_sent > 10000){
    float temp = dht.readTemperature();
    float humid = dht.readHumidity();

    if(isnan(temp) || isnan(humid)){
      Serial.println("DHT_ERR");
    } else {
      doc["ArduinoId"] = ARDUINO_ID;
      doc["Temperature"] = temp;
      doc["Humidity"] = humid;
      serializeJson(doc, Serial);
    }
    last_sent = current_sent;
  }
}
