#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int Sensor = A0;
int LED = 3;
int pirSensor = 4;

int clap = 0;
long detection_range_start = 0;
long detection_range = 0;
boolean status_lights = false;
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  pinMode(Sensor, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(pirSensor, INPUT);
}

void loop() {
int status_sensor = digitalRead(Sensor);
int pir_sensor_value = digitalRead(pirSensor);

if (status_sensor == 0){
  if (clap == 0){
    detection_range_start = detection_range = millis();
    clap++;
  }else if (clap > 0 && millis()-detection_range >= 50){
    detection_range = millis();
    clap++;
  }
}

if (millis()-detection_range_start >= 400){
  if (clap == 1 && pir_sensor_value == 1){
    if (!status_lights){
      status_lights = true;
      digitalWrite(LED, HIGH);
      lcd.setBacklight(HIGH);
      lcd.println("Welcome!");
    } else if (status_lights) {
        status_lights = false;
        digitalWrite(LED, LOW);
        lcd.clear();
        lcd.setBacklight(LOW);
     }
  }
  clap = 0;
  }

}
