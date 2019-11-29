#include <LiquidCrystal.h>
#include <Servo.h>
#include <Wire.h>

#define basketButton 2
#define basketLed 11

#define front_trigger 7
#define front_echo 8

#define waste_trigger 5
#define waste_echo 6

#define empty A3
#define half A4
#define full A5

Servo Left, Right, Compress;

float percentage, duration, max_height =31.60, distance;

int fullflag, gateflag;

String WasteValue = "";

void setup() 
{
  Serial.begin(9600);
    
  pinMode(basketButton, INPUT);
  pinMode(basketLed, OUTPUT);
  
  pinMode(front_trigger, OUTPUT);
  pinMode(front_echo, INPUT);
  
  pinMode(waste_trigger, OUTPUT);
  pinMode(waste_echo, INPUT);
  
  pinMode(empty, OUTPUT);
  pinMode(half, OUTPUT);
  pinMode(full,OUTPUT);
   
  digitalWrite(basketButton,LOW);
  
  digitalWrite(empty, LOW);
  digitalWrite(half, LOW);
  digitalWrite(full,LOW);
  
  Left.attach(3);
  Right.attach(4);
  Compress.attach(9);  
}

void loop() 
{
  if(digitalRead(basketButton) == HIGH){
    
    Serial.println("BASKET FOUND");
    digitalWrite(basketLed,HIGH);

    GetWasteLevel();
      
      Serial.print("Dust Level: ");
      Serial.println(percentage);
      
    if(percentage >= 0 && percentage <=10)
    {
        Serial.println("Empty");
        
        digitalWrite(empty, HIGH);
        digitalWrite(half, LOW);
        digitalWrite(full, LOW);
        
        fullflag = 0;
    }

    else if(percentage > 10 && percentage <= 70)
    {
        Serial.println("Medium");
        
        digitalWrite(empty, LOW);
        digitalWrite(half, HIGH);
        digitalWrite(full, LOW);
      
      if(percentage >=50 && percentage <=70){
        for(int pos=0; pos < 90; pos++){
          Compress.write(pos);
          delay(15);
        }
     }
        fullflag = 0;
    }
    else if(percentage > 70 && percentage <= 90){
        Serial.println("Full");
        
        digitalWrite(empty, LOW);
        digitalWrite(half, LOW);
        digitalWrite(full, HIGH);
        
        for(int pos=0; pos < 90; pos++){
          Compress.write(pos);
          delay(15);
        }
        fullflag = 1;
    }
    else
    { 
        Serial.println("OverLoad");
    }

    if(GetPersonWarninig() == 1)
    {
      if(fullflag == 0)
      {
          for(int pos=0; pos <90; pos++){
            Left.write(pos);
            Right.write(pos);
            delay(15);
          }
       }
    }
  }
  
  else
  {
    Serial.println("BASKET MISSING");
    Allclear();
  }
  
  Allclear();
  delay(1000);
}

void Allclear()
{
    digitalWrite(basketLed,LOW);
    digitalWrite(basketButton,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    
    
}

void GetWasteLevel()
{

  digitalWrite(waste_trigger, LOW);
    delayMicroseconds(2);
  
  digitalWrite(waste_trigger, HIGH);
    delayMicroseconds(10);
  
  digitalWrite(waste_trigger, LOW);

    duration = pulseIn(waste_echo,HIGH);
  
    distance = duration*0.034/2;
    //Serial.print("Distance: ");
    
    if(distance >= 0 && distance <= max_height)
    {
        percentage = ((max_height - distance)*100)/max_height;
        //Serial.println(percentage);
    }

    else
    {
      percentage = 0.0;
    }
}

int GetPersonWarninig()
{
  digitalWrite(front_trigger, LOW);
    delayMicroseconds(2);

  digitalWrite(front_trigger, HIGH);
    delayMicroseconds(10);

  digitalWrite(front_trigger, LOW);

    duration = pulseIn(front_echo,HIGH);
  
  distance = duration*0.034/2;
    Serial.print("GetPerson: ");
      Serial.println(distance);
    if(distance < 30)
    {
      return 1;
    }
    else
    {
      return 0;
    }
}




