#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("circuitdigest.com");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Use Ser. Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Type to display");
}

void loop()
{
  {

    // when characters arrive over the serial port...
    if (Serial.available()) {

      delay(100);               // wait a bit for the entire message to arrive

      lcd.clear();                // clear the screen

      while (Serial.available() > 0) {                // read all the available characters

        lcd.write(Serial.read());             // display each character to the LCD
      }
    }
  }
}
