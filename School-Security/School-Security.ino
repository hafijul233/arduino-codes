#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define D2 22
#define D1 21

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  Serial.begin(9600);
  Wire.begin(D2, D1);
  
  lcd.begin();
  lcd.home();
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME TO");
  lcd.setCursor(0, 1);
  lcd.print("School Security");
}

void loop()
{
  
}
