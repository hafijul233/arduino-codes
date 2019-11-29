#include <Servo.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define light1 13
#define light2 12
#define fan1 11

#define gas A4
#define temp A5
#define buzzer A0


char command = '\0';
int i = 0;
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo gate;

void setup() {
  
  Serial.begin(9600);
  lcd.begin(16, 2);
  gate.attach(9);
    
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(fan1, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(gas, INPUT);
  pinMode(temp, INPUT);
  
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("- WELCOME TO -"); 
  lcd.setCursor(1,0);
  lcd.print("-AUTOMATED HOME-");
  delay(500);
  lcd.clear();
}

void loop() { 
  lcd.setCursor(0,0);
  lcd.print("-AUTOMATED HOME-");
  lcd.setCursor(0,1);
  
    fireAlarm();
  
  if(Serial.available() > 0)
  {
    command = Serial.read();
    
    if(command == 'A'){
        lcd.print("LIGHT-1 is OFF");
        digitalWrite(light1, HIGH);
        }

    else if(command == 'a'){
        lcd.print("LIGHT-1 is ON");
        digitalWrite(light1, LOW);
        delay(4000);
        }

    else if(command == 'B'){
        lcd.print("LIGHT-2 is OFF");
        digitalWrite(light2, HIGH);
        }

    else if(command == 'b'){
        lcd.print("LIGHT-2 is ON");
        digitalWrite(light2, LOW);
        delay(4000);
        }
        
     else if(command == 'D'){
        lcd.print("FAN-1 is OFF");
        digitalWrite(fan1, HIGH);
        }

     else if(command == 'd'){
        lcd.print("FAN-1 is ON");
        digitalWrite(fan1, LOW);
        delay(4000);
        }

     else if(command == 'G'){
        lcd.print("Opening Gate");
          for(i = 0; i<90; i++){
            gate.write(i);
            delay(15);
          }
        }

      else if(command == 'g'){
        lcd.print("Closing Gate");
          for(i = 90; i>0; i--){
            gate.write(i);
            delay(15);
          }
        }
        
    else if(command == 'R'){
          lcd.print("  Power OFF  ");
          digitalWrite(light1, HIGH);
          digitalWrite(light2, HIGH);
          digitalWrite(fan1, HIGH);
      }
      else if(command == 'r'){
          lcd.print("  Power ON  ");
          digitalWrite(light1, LOW);
          digitalWrite(light2, LOW);
          digitalWrite(fan1, LOW);
          delay(5000);
      }
    
    lcd.clear();
  }
}

void fireAlarm(){
  int v = analogRead(gas);
  if( v > 60){
          lcd.print("Fire Alarm");
          digitalWrite(light1, HIGH);
          digitalWrite(light2, HIGH);
          digitalWrite(fan1, HIGH);
          digitalWrite(buzzer,HIGH);
  }
  digitalWrite(buzzer,LOW);
  
}
