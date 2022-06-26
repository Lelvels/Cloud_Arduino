#include<Arduino.h>
#include<DHT.h>
#include<ArduinoJson.h>
#include<LiquidCrystal_I2C.h>
#include<ReportedData.h>
#include<DesiredData.h>
#include<AltSoftSerial.h>
#include<math.h>

#define DHTTYPE DHT22
#define DHTPIN 4
#define FAN_IN_PIN 5
#define FAN_OUT_PIN 6
#define HUMIDIFIER_PIN 7
//AltSerial 8,9 => CO2
#define LED_PIN 10
#define VAN_PIN 11
#define SOIL_PIN A0

//Đặt tên ID cho Arduino
const char ARDUINO_ID[10] = "AR01";
//Desired Init
DesiredData desired(ARDUINO_ID);
//Reported Init
ReportedData reported(ARDUINO_ID);
//AltSoftSerial
AltSoftSerial altSerial;
//Timing
uint16_t last_sent = 0;
uint16_t last_control = 0;
uint16_t last_read_co2 = 0;
uint16_t last_display = 0;
//CO2_SENSOR
float nco2 = 0;
float last_nco2 = 0;
//JSON ARDUINO
StaticJsonDocument<200> doc;
//Sensor and others
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);
//Message ID, reset mỗi khi chạy
uint16_t mess_id = 0;

/*
  Function name: reported_to_Json()
  Parameters: void
  Description: lấy dữ liệu reported từ Object reported, sử dụng doc để đóng gói
  lại thành chuỗi JSON sau đó gửi đến Raspberry pi thông qua Serial, nếu có lỗi xảy 
  ra liên quan đến dữ liệu trong quá trình đóng gói, hệ thống sẽ gửi 1 đoạn code lỗi 
  liên quan.
  Reference: https://arduinojson.org/v6/doc/serialization/
*/
void reported_to_Json(){
  float humid = reported.getHumidity();
  float temp = reported.getTemperature();
  float soil = reported.getSoilMoisture();
  float co2 = reported.getCO2();
  doc.clear();
  doc["Id"] = mess_id; mess_id++;
  doc["DeviceId"] = ARDUINO_ID;
  
  if(isnan(humid) || isnan(temp)){
    Serial.println("DHT_ERR");
  } else {
    doc["Temperature"] = temp;
    doc["Humidity"] = humid;
  }

  if (isnan(soil)){
    Serial.println("SOIL_ERR");
  } else {
     doc["SoilMoisture"] = soil;
  }

  if (isnan(co2)) {
    Serial.println("CO2_ERR");
  } else {
     doc["CO2"] = co2;
  }

  serializeJson(doc, Serial);
}

/*
  Function name: Json_to_desired()
  Parameters: command, ở đây là chuỗi điều khiển mà Arduino đọc được gửi đi từ Raspberry pi,
  chuỗi điều khiển này có dạng là:
  {'ArduinoId': arduino_id, 'Temperature': temp, 
                   'MinHumidity': min_humid, 'MaxHumidity': max_humid,
                   'MinCO2' : min_co2, 'MaxCO2' : max_co2,
                   'Disable' : disable,
                   'LedState' : LedState}
  Description: Arduino sau khi nhận được chuỗi điều khiển từ Raspberry sẽ deserialize chuỗi 
  điều khiển này, kiểm tra dữ liệu và lưu chúng vào trong Object desired, mỗi khi cần kiểm tra
  với yêu cầu của người dùng, hệ thống chỉ cần lấy object desired ra để kiểm tra.

  Reference: https://arduinojson.org/v6/doc/deserialization/
*/
void Json_to_desired(String command){
  doc.clear();
  DeserializationError error = deserializeJson(doc, command);
  if(error){
    Serial.println("JSON_ERR");
    return;
  } else {
    JsonVariant desiredTemp = doc["Temperature"];
    if(!desiredTemp.isNull()){
      desired.setTemperature(desiredTemp.as<float>());  
    }

    JsonVariant minHumidity = doc["MinHumidity"];
    if(!minHumidity.isNull()){
      desired.setMinHumidity(minHumidity.as<float>());
    }

    JsonVariant maxHumidity = doc["MaxHumidity"];
    if(!maxHumidity.isNull()){
      desired.setMaxHumidity(maxHumidity.as<float>());
    }

    JsonVariant minCO2 = doc["MinCO2"];
    if(!minCO2.isNull()){
      desired.setMinCO2(minCO2.as<float>());
    }

    JsonVariant maxCO2 = doc["MaxCO2"];
    if(!maxCO2.isNull()){
      desired.setMaxCO2(maxCO2.as<float>());
    }

    JsonVariant LedState = doc["LedState"];
    if(!LedState.isNull()){
      desired.setLedState(LedState.as<bool>());
    }

    JsonVariant Disable = doc["Disable"];
    if(!Disable.isNull()){
      desired.setDisable(Disable.as<bool>());
    }
  }
}

/*
  Function name: lcd_display_init()
  Parameters: void
  Description: Sử dụng để hiện thị các tham số môi trường đo được
  và dữ liệu điều khiển của hệ thống lưu ý là chỉ áp dụng với 
  màn hình LCD 20 cột và 4 hàng.
  Lưu ý là thư viện của LCD đã nằm sẵn trong code, /lib/LiquidCrystal_I2C
  Reference: https://www.youtube.com/watch?v=q9YC_GVHy5A
*/
void lcd_display_init(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(reported.getTemperature());
  lcd.setCursor(8,0);
  lcd.print(reported.getHumidity());
  lcd.setCursor(15, 0);
  lcd.print(desired.isDisable());
  lcd.setCursor(17, 0);
  lcd.print(desired.getLedState());

  lcd.setCursor(0, 1);
  lcd.print(reported.getCO2());
  lcd.setCursor(8, 1);
  lcd.print(reported.getSoilMoisture());

  lcd.setCursor(0,2);
  lcd.print(desired.getTemperature());
  lcd.setCursor(8,2);
  lcd.print(desired.getMinHumidity());
  lcd.setCursor(15,2);
  lcd.print(desired.getMaxHumidity());

  lcd.setCursor(0,3);
  lcd.print(desired.getMinCO2());
  lcd.setCursor(8,3);
  lcd.print(desired.getMaxCO2());
}

/*
  Function name: reset_func()
  Parameters: void
  Description: Sử dụng để reset Arduino bằng phần mềm, do Cảm biến CO2 đôi
  lúc bị trục trặc nên dẫn đến việc đọc sai cảm biến CO2, tạm thời ta giải quyết 
  vấn đề này bằng cách reset lại arduino bằng phần mềm.
*/
void(* resetFunc) (void) = 0; //declare reset function @ address 0

void setup(){
  Serial.begin(9600);
  altSerial.begin(9600);
  //pinMode
  dht.begin(); //DHT -> 4
  lcd.begin();
  lcd.backlight();
  pinMode(FAN_IN_PIN, OUTPUT);
  pinMode(FAN_OUT_PIN, OUTPUT);
  pinMode(HUMIDIFIER_PIN, OUTPUT);
  pinMode(VAN_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  digitalWrite(VAN_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(FAN_IN_PIN, LOW);
  digitalWrite(FAN_OUT_PIN, LOW);
  digitalWrite(HUMIDIFIER_PIN, LOW);
}

void loop(){
  uint16_t current_time = millis();
  /*
    Đọc dữ liệu từ Raspberry pi
  */
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    Json_to_desired(command);
  }

  /*
    Lưu ý: Đây là phần tính toán nồng độ khí CO2, nếu các bạn sử dụng
    cảm biến CO2 khác thì có thể xóa đi phần này, việc đo CO2 sẽ thông qua AltSoftSerial
  */
  if(altSerial.available())
  {
    const float zero = 1.01;
    const float span = 0.995;
    const float b = 0.171;
    const float c = 0.476;
    byte arr[5];
    float ch1 = 0, ch2 = 0, ch2b = 0, fa = 0, phanso = 0;
    altSerial.flush();
    altSerial.readBytesUntil('0', arr, 5);
    if(arr[4] != 0){
      //resetFunc();
    } else {
      ch1 = arr[0]*256 + arr[1];
      ch2 = arr[2]*256 + arr[3];
      ch2b = ch2 + 2100;
      fa = 1 - (ch1/(ch2b*zero));
      phanso = log(1-(fa/span)) / (-b);
      nco2 = pow(phanso, (1/c)) * pow(10, 4) * 1/2;
      reported.setCO2(nco2);
    }
  }
  delay(100);

  //Hiển thị LCD
  current_time = millis();
  if(current_time - last_display > 2000){
    lcd_display_init();
    last_display = current_time;
  }
  
  //Điều khiển và đo cảm biến
  current_time = millis();
  if(current_time - last_control > 2000){
    //Đo từ cảm biến
    float temp = dht.readTemperature();
    float humid = dht.readHumidity();
    int value = analogRead(A0);    
    float percent = map(value, 0, 1023, 0, 100);
    float soil = (100 - percent)*2;

    reported.setTemperature(temp);
    reported.setHumidity(humid);
    reported.setSoilMoisture(soil);

    //Controlling
    if(desired.isDisable()){
      digitalWrite(FAN_IN_PIN, LOW);
      digitalWrite(FAN_OUT_PIN, LOW);
      digitalWrite(HUMIDIFIER_PIN, LOW);
      digitalWrite(VAN_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
    } else {
      if(desired.getLedState()){
        digitalWrite(LED_PIN, HIGH);
      } else {
        digitalWrite(LED_PIN, LOW);
      }

      if(reported.getCO2() > desired.getMaxCO2()){
        digitalWrite(VAN_PIN, LOW);
      } else {
        if(reported.getCO2() < desired.getMinCO2()){
          digitalWrite(VAN_PIN, HIGH);
        }
      }

      if(reported.getHumidity() > desired.getMaxHumidity()){
        digitalWrite(HUMIDIFIER_PIN, LOW);
      } else {
        if(reported.getHumidity() < desired.getMinHumidity()){
          digitalWrite(HUMIDIFIER_PIN, HIGH);
        }
      }

      if(reported.getTemperature() > desired.getTemperature()){
        digitalWrite(FAN_IN_PIN, HIGH);
      } else {
        digitalWrite(FAN_IN_PIN, LOW);
      }

      bool fan_out_state = (reported.getCO2() > desired.getMaxCO2()) || (reported.getHumidity() > desired.getMaxHumidity());
      if(fan_out_state){
        digitalWrite(FAN_OUT_PIN, HIGH);
      } else {
        digitalWrite(FAN_OUT_PIN, LOW);
      }
    }
  }

  //Send reported data
  current_time = millis();
  if(current_time - last_sent > 8000){
    reported_to_Json();
    last_sent = current_time;
  }
}