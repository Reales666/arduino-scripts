#include <LCD-I2C.h>
#include <Wire.h>
#include "SHT31.h"
#include "Air_Quality_Sensor.h"

SHT31 sht31 = SHT31(); // Initialize SHT31 sensor (Temp & Humidity)
AirQualitySensor airQualitySensor(A0); // Initialize Air Quality Sensor in A0
LCD_I2C lcd(0x27, 20, 4); // Screen I2C address and screen size

void setup() {
  // If you are using more I2C devices using the Wire library use lcd.begin(false)
  // this stop the library(LCD-I2C) from calling Wire.begin()
  Wire.begin();
  lcd.begin(&Wire);
  lcd.display();
  lcd.backlight();
  sht31.begin();  

  lcd.print("Sensor init...");

  for (int i = 20; i > 0; i--) {
    lcd.setCursor(0, 1);
    lcd.print(i);

    if(i < 10) {
      lcd.setCursor(1, 1);
      lcd.print(" ");
    }

    delay(1000);
  }

  lcd.clear();

  if (airQualitySensor.init()) 
  {
    lcd.setCursor(0, 0);
    lcd.print("Sensor ready.");
  } else 
  {
    lcd.setCursor(0, 0);
    lcd.print("Sensor ERROR!");
  }
}

void loop()
{
  float temp = sht31.getTemperature();
  float hum = sht31.getHumidity();

  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(temp) + " C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: " + String(hum) + " %");

  int quality = airQualitySensor.slope();

  if (quality == AirQualitySensor::FORCE_SIGNAL) {
      lcd.setCursor(0, 2);
      lcd.print("High pollution!");
      lcd.setCursor(0, 3);
      lcd.print("Force signal active");
  } else if (quality == AirQualitySensor::HIGH_POLLUTION) {
      lcd.setCursor(0, 2);
      lcd.print("High pollution!");
  } else if (quality == AirQualitySensor::LOW_POLLUTION) {
      lcd.setCursor(0, 2);
      lcd.print("Low pollution!");
  } else if (quality == AirQualitySensor::FRESH_AIR) {
      lcd.setCursor(0, 2);
      lcd.print("Fresh air");
  }

  delay(5000);
}
