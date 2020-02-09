#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int Sensor = A0;
int LED = 3;

int clap = 0;
long detection_range_start = 0;
long detection_range = 0;
boolean status_lights = false;
LiquidCrystal_I2C lcd(0x27,2,1,0);

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("hello");
  pinMode(Sensor, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
int status_sensor = digitalRead(Sensor);
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
  if (clap == 2){
    if (!status_lights){
      status_lights = true;
      digitalWrite(LED, HIGH);
    } else if (status_lights) {
        status_lights = false;
        digitalWrite(LED, LOW);
     }
  }
  clap = 0;
  }

}
