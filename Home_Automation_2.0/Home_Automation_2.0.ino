#include <Servo.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define PBulb1 31
#define PBulb2 33
#define PFan1 35

#define SBulb1 46
#define SBulb2 48
#define SFan1 52

#define gasPin A1
#define tempPin A0
#define buzzer A4

#define tx 11
#define rx 10

char command = '\0';
int i = 0;

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;

Servo gateservo;

SoftwareSerial mySerial(rx, tx);

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  Serial.begin(19200);
  mySerial.begin(9600);
  lcd.begin(16,2);

  pinMode(SBulb1, INPUT);
  pinMode(SBulb2, INPUT);
  pinMode(SFan1, INPUT);

  pinMode(PBulb1, OUTPUT);
  pinMode(PBulb2, OUTPUT);
  pinMode(PFan1, OUTPUT);

  pinMode(gasPin, INPUT);
  pinMode(tempPin, INPUT);

  gateservo.attach(3);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   WELCOME TO    ");
  lcd.setCursor(1,0);
  lcd.print("   Smart Home    ");
  delay(500);
  lcd.clear();
}

void loop()
{
  lcd.setCursor(0,0);
  lcd.print("Smart House");
  lcd.setCursor(1,0);
  
  if(mySerial.available() > 0)
  {
    command = mySerial.read();

    Serial.print("Received Value: ");
    Serial.println(command);
      getchar();
    
    switch(command)
    {
      case 'A' :{
        digitalWrite(PBulb1, HIGH);
        lcd.print("Lamp1 is OFF");
        //delay(300);
        //lcd.clear();
        break;
        }

     case 'a' :{
        digitalWrite(PBulb1, LOW);
        lcd.print("Lamp1 is ON");
        //delay(30000);
        //lcd.clear();
        break;
        }

     case 'B' :{
        digitalWrite(PBulb2, HIGH);
        lcd.print("Lamp2 is OFF");
        //delay(300);
        //lcd.clear();
        break;
        }

     case 'b' :{
        digitalWrite(PBulb2, LOW);
        lcd.print("Lamp2 is ON");
        //delay(300);
        //lcd.clear();
        break;
        }

     case 'D' :{
        digitalWrite(PFan1, HIGH);
        lcd.print("Fan1 is OFF");
        delay(300);
        //lcd.clear();
        break;
        }

     case 'd' :{
        digitalWrite(PFan1, LOW);
        lcd.print("Fan1 is ON");
        delay(300);
        //lcd.clear();
        break;
        }

     case 'G' : {
        lcd.print("Opening Gate");
        for(i = 0; i<90; i++){
          gateservo.write(i);
          delay(15);
        }
        break;
        }

      case 'g' : {
        lcd.print("Closing Gate");
        for(i = 90; i>0; i--){
          gateservo.write(i);
          delay(15);
        }
        break;
        }
        
    case 'R'  :{
          digitalWrite(PBulb1, HIGH);
          digitalWrite(PBulb2, HIGH);
          digitalWrite(PFan1, HIGH);
          
        break;
      }
     default: Serial.print("Garbase Received Value: ");
              Serial.println(command);
      break;
    }
  }
}
