#include <LiquidCrystal.h>

#define trigger A4
#define echo A5

const int ena = 7, in4 = 8, in3 = 9;//Motor Driver
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float percentage = 0.0;
int low_level = 0, high_level = 0;
float duration, max_height = 20, water_level;

void setup() {
  
  lcd.begin(16,2);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(ena,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  
  lcd.setCursor(0, 0);
  lcd.print("WELCOME TO");
  lcd.setCursor(0, 1);   
  lcd.print("Liq. Controllter");
  delay(500);
  lcd.clear();
  
}

void loop() {
  
  lcd.clear();
  DepthPercentage();
  lcd.setCursor(0,0);
  lcd.print("Storage: ");
  lcd.print(percentage);
  lcd.print("%");
  
    low_level = analogRead(A0);
    high_level = analogRead(A1);
  
  if(percentage <= 5.00 && low_level > 200){
    lcd.setCursor(2,1);
    lcd.print("Status: EMPTY");
    //Motor ON
    digitalWrite(ena,HIGH);
    digitalWrite(in4,HIGH);
    digitalWrite(in3,LOW);
  }
  
  else if(percentage > 5.00 && percentage < 80.00){
    lcd.setCursor(2,1);
    lcd.print("Status: OKEY");  
  }
  
  else if(percentage >=80.00 || high_level >= 200){  
    lcd.setCursor(2,1);
    lcd.print("Status: FULL"); 
    //Motor OFF
    digitalWrite(ena,LOW);
    digitalWrite(in4,LOW);
    digitalWrite(in3,LOW);
  }
  
  else {
    lcd.setCursor(2,1);
    lcd.print("Status: ERROR"); 
  }
  delay(500);
}

void DepthPercentage(){

  digitalWrite(trigger, LOW);
    delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  duration = pulseIn(echo,HIGH);
  water_level = max_height - (duration*0.034/2);
  percentage = (water_level)*100/max_height;
}
