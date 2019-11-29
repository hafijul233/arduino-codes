#include <LiquidCrystal.h>

#define trigger A4
#define echo A5

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const float max_deepth = 21;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float duration=0, water_level=0, percentage;

void setup() {
  Serial.begin(9600);
  lcd.begin(20,4);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  lcd.setCursor(2,0);
  lcd.print("Welcome TO");
      lcd.setCursor(1,0);
    lcd.print("Lq Lev. Indic.");
      delay(2000);
    lcd.clear();
    lcd.setCursor(1, 0);
}

void loop() {
   distance = ultrasonic.Ranging(CM); //Use 'CM' for 
  lcd.setCursor(1,0);
  lcd.print("Object Deteted");
  lcd.setCursor(0,1);
  lcd.print(distance);
  Serial.println(distance);
  //lcd.setCursor(1,10);
  lcd.print(" Centmeter");
   delay(500);
  lcd.clear();
}
