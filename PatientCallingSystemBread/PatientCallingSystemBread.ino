#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

//Define LCD variables
#define I2C_ADDR          0x27        //Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7

#define button0 2
#define button1 3
#define button2 4
#define button3 5
#define button4 6
#define button5 7
#define button6 8
#define button7 9
#define button8 10
#define button9 12
#define resetbutton 14
#define buzzer 11

#define maxRange 50

//Lcd Constants

int inputLength = 0;
char inputArray[maxRange];

//Initialise the LCD
LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

void setup()
{
    Serial.begin(9600);

    //Define the LCD as 16 column by 2 rows
      lcd.begin (16, 2);
  //Switch on the backlight
      lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
      lcd.setBacklight(HIGH);
      lcd.clear();
      lcdMessage("   WELCOME TO   ", "Nurse Calling System");
  
    pinMode(button0, INPUT);
    pinMode(button1, INPUT);
    pinMode(button2, INPUT);
    pinMode(button3, INPUT);
    pinMode(button4, INPUT);
    pinMode(button5, INPUT);
    pinMode(button6, INPUT);
    pinMode(button7, INPUT);
    pinMode(button8, INPUT);
    pinMode(button9, INPUT);
    
    Serial.println("Nurse Calling System Powered ON");
    delay(500);
    lcd.clear();
    lcdMessage(" Patient Alert!", "-------------------");
}

void loop()
{
  if(digitalRead(button0) == HIGH)
  {
    lcdMessage(" Patient Alert! ","Room No:01 Calling");
    Serial.println("Room Number 1 Calling");
    Serial.println("Buzzer ON");
    tone(buzzer, 1000);
  }
  
  else if(digitalRead(button1) == HIGH)
  {
    lcdMessage(" Patient Alert! ","Room No:02 Calling");
    Serial.println("Room Number 2 Calling");
    Serial.println("Buzzer ON");
    tone(buzzer, 1000);
  }
  
  else if(digitalRead(button2) == HIGH)
  {
    lcdMessage(" Patient Alert! ","Room No:03 Calling");
    Serial.println("Room Number 3 Calling");
    Serial.println("Buzzer ON");
    tone(buzzer, 1000);
  }
  
   else if(digitalRead(button3) == HIGH)
  {
    lcdMessage(" Patient Alert! ","Room No:04 Calling");
    Serial.println("Room Number 4 Calling");
    Serial.println("Buzzer ON");
    tone(buzzer, 1000);
  }
  
  else if(digitalRead(button4) == HIGH)
  {
    lcdMessage(" Patient Alert! ","Room No:05 Calling");
    Serial.println("Room Number 5 Calling");
    Serial.println("Buzzer ON");
    tone(buzzer, 1000);
  }
  
  else if(digitalRead(button5) == HIGH)
  {
    lcdMessage(" Patient Alert! ","Room No:06 Calling");
    Serial.println("Room Number 6 Calling");
    Serial.println("Buzzer ON");
    tone(buzzer, 1000);
  }
  
  else if(digitalRead(button6) == HIGH)
  {
    lcdMessage(" Patient Alert! ","Room No:07 Calling");
    Serial.println("Room Number 7 Calling");
    Serial.println("Buzzer ON");
    tone(buzzer, 1000);
  }

  else if(digitalRead(button7) == HIGH)
  {
    lcdMessage(" Patient Alert! ","Room No:08 Calling");
    Serial.println("Room Number 8 Calling");
    Serial.println("Buzzer ON");
    tone(buzzer, 1000);
  }
  
  else if(digitalRead(button8) == HIGH)
  {
    lcdMessage(" Patient Alert! ","Room No:09 Calling");
    Serial.println("Room Number 7 Calling");
    Serial.println("Buzzer ON");
    tone(buzzer, 1000);
  }
  
  else if(digitalRead(button9) == HIGH)
  {
    lcdMessage(" Patient Alert! ","Room No:10 Calling");
    Serial.println("Room Number 10 Calling");
    Serial.println("Buzzer ON");
    tone(buzzer, 1000);
  }
  
  else if(digitalRead(resetbutton) == HIGH)
  {
    lcdMessage(" Patient Alert! ","-------------------");
    Serial.println("-------------------");
    Serial.println("Buzzer OFF");
    noTone(buzzer);
  }
}

void lcdMessage(String FirstRow, String SecondRow)
{
  inputLength = SecondRow.length();
  lcd.clear();
  lcd.print(FirstRow);
  if (inputLength <= 16) {
    lcd.setCursor(0, 1);
    lcd.print(SecondRow);
  }
  else if (inputLength > maxRange) {
    Serial.println("This string is too long.");
  }
  else {
    lcd.setCursor(0, 1);
    SecondRow.toCharArray(inputArray, maxRange);
    for (int i = 0; i <= 16; i++) {
      lcd.write(inputArray[i]);
    }

    delay(1500); //completion wait

    for (int j = 17; j <= inputLength; j++) {
      lcd.write(inputArray[j]);
      lcd.scrollDisplayLeft();

      lcd.setCursor(j - 16, 0);
      lcd.print(FirstRow);
      lcd.setCursor(j + 1, 1);
      delay(300);
    }
  }
}
