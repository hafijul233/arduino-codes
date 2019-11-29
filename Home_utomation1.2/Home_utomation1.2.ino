#include <Servo.h>
#include <LiquidCrystal.h>

#define PowerBulb1 5
#define PowerBulb2 4
#define PowerBulb3 3
#define PowerFan1 2

#define gaspin A0
#define buzzer 9

char command = '\0';
int i = 0;

Servo gateservo;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  Serial.begin(9600);
  pinMode(PowerBulb1, OUTPUT);
  pinMode(PowerBulb2, OUTPUT);
  pinMode(PowerBulb3, OUTPUT);
  pinMode(PowerFan1, OUTPUT);
  gateservo.attach(9);
}

void loop()
{
  if(Serial.available() > 0)
  {
    command = Serial.read();

    Serial.print("Received Value: ");
    Serial.println(command);
      getchar();
    
    switch(command)
    {
      case 'A' :
        digitalWrite(PowerBulb1, HIGH);
        break;

     case 'a' :
        digitalWrite(PowerBulb1, LOW);
        break;

     case 'B' :
        digitalWrite(PowerBulb2, HIGH);
        break;

     case 'b' :
        digitalWrite(PowerBulb2, LOW);
        break;

     case 'C' :
        digitalWrite(PowerBulb3, HIGH);
        break;

     case 'c' :
        digitalWrite(PowerBulb3, LOW);
        break;

     case 'D' :
        digitalWrite(PowerFan1, HIGH);
        break;

     case 'd' :
        digitalWrite(PowerFan1, LOW);
        break;

     case 'G' : {
        for(i = 0; i<160; i++){
          gateservo.write(i);
          delay(15);
        }

        delay(1000);

        for(i = 160; i>0; i--){
          gateservo.write(i);
          delay(15);
        }

        break;
     }
    case 'R'  :{
          digitalWrite(PowerBulb1, HIGH);
          digitalWrite(PowerBulb2, HIGH);
          digitalWrite(PowerBulb3, HIGH);
          digitalWrite(PowerFan1, HIGH);
          
        break;
      }
     default: Serial.print("Garbase Received Value: ");
              Serial.println(command);
      break;
    }
  }
}

void gasController(int state)
{  
  int gasvalue = analogRead(gaspin);
  if(gasvalue >=8){
          digitalWrite(PowerBulb1, HIGH);
          digitalWrite(PowerBulb2, HIGH);
          digitalWrite(PowerBulb3, HIGH);
          digitalWrite(PowerFan1, HIGH);

          //Buzzer On

          digitalWrite(buzzer, HIGH);
  }
}
