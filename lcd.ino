#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  delay(1000);
  
  lcd.setCursor(3, 0);
  lcd.print("Wassup");
  delay(1000);
  
  lcd.clear();
  delay(1000);

  lcd.setCursor(3, 1);
  lcd.print("Wassup");
  delay(1000);
}
