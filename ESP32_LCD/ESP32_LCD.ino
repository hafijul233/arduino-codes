#include <LiquidCrystal.h>

const int rs = 16, en = 17, d4 = 5, d5 = 18, d6 = 19, d7 = 21;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
    lcd.begin(16, 2);
    lcd.clear();
    lcd.print("How to Interface");

    // go to row 1 column 0, note that this is indexed at 0
    lcd.setCursor(0,1); 
    lcd.print ("LCD with ESP32");
}

void loop(){}
