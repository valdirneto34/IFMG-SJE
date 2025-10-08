/*#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("PROJETO");
  lcd.setCursor(0, 1);
  lcd.print("ROBOTICA");
}*/
/*
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void contaDez() {
  for (int i = 0; i <= 10; i++) {
    lcd.clear();
    lcd.home();
    lcd.print(String(i));
    delay(1000);
  }
}
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}
void loop() {
  lcd.home();
  lcd.print("PROJETO");
  lcd.setCursor(0, 1);
  lcd.print("ROBOTICA");
  delay(5000);
  contaDez();
  delay(1000);
}
*/

#include <Wire.h>

void setup() {
  Wire.begin();

  Serial.begin(9600);
  Serial.println("\nI2C Scanner");
}

void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning I2C devices...");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.print("Found ");
    Serial.print(nDevices);
    Serial.println(" devices\n");
  }
  delay(5000);  // Wait 5 seconds for next scan
}
