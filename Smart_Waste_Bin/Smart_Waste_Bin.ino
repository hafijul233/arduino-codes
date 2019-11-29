#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define ledPin A0

#define front_trigger 6
#define front_echo 7

#define waste_trigger 5
#define waste_echo 4

#define basket 2

#define empty 8
#define half 9
#define full 10


//const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;

//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const float max_height = 26.45;
float percentage=0.0, distance, duration;
int person = 0, full_flag = 0;
int gate_state = 0;

Servo gate;

void setup() {
  
  Serial.begin(9600);
  //Serial.begin(16, 2);
  
  pinMode(waste_trigger, OUTPUT);
  pinMode(waste_echo, INPUT); 

  pinMode(front_trigger, OUTPUT);
  pinMode(front_echo, INPUT);

  pinMode(basket, INPUT);
  pinMode(A1,OUTPUT);
  pinMode(empty,OUTPUT);
  pinMode(half,OUTPUT);
  pinMode(full,OUTPUT);
  
  digitalWrite(empty,LOW);
  digitalWrite(half,LOW);
  digitalWrite(full,LOW);
  
  gate.attach(3);
}


void loop() {
  
  //Serial.clear();
  //Serial.setCursor(0, 0);
  Serial.println("Smart Waste Bin");
  //Serial.setCursor(1,0);
  
  if(digitalRead(basket) == HIGH){//basket Presence
      //basket indeicator
      digitalWrite(ledPin,HIGH); 
      Serial.println("Basket Found");

    // Waste Level Calculation 
      GetWasteLevel();
      
      //Show Every Waste Value
      Serial.print("Waste Level: ");
      Serial.println(percentage);

      if(percentage >= 0 && percentage <=10)
      {
        digitalWrite(empty,HIGH);
        digitalWrite(half,LOW);
        digitalWrite(full,LOW);
      }

      else if(percentage > 10 && percentage <=70)
      {
        digitalWrite(empty,LOW);
        digitalWrite(half,HIGH);
        digitalWrite(full,LOW);
      }

      else
      { 
        digitalWrite(empty,LOW);
        digitalWrite(half,LOW);
        digitalWrite(full,HIGH);

      }

    //Finding Nearest Person
      person = GetPersonWarninig();

      if(person == 1){
        digitalWrite(A1,HIGH);
      }
      else
      {
        digitalWrite(A1,LOW);
      }

      /*if(full_flag == 0)//when there is less space 
      {
        if(person == 1 && gate_state == 0){
          for (int pos = 0; pos <= 150; pos++) {
            gate.write(pos);              
            delay(15);
            gate_state = pos;                        
          }
        }

      if(person == 1 && gate_state == 150){
         gate.write(170);
      }

      if(person == 0 && gate_state == 150){
        for (int pos = 150; pos >= 0; pos--) {
          gate.write(pos);              
          delay(15);
          gate_state = pos;                        
        }
      }
    }

    if (full_flag == 1)//there is no space
    { 
     //Serial.setCursor(1,0);
      Serial.println(" Waste Bin FULL.");
      gate.write(0);
    }*/
  }// basket presense
  
  else
  {  
    Serial.println("Basket NOT Found");
    //Serial.print("There No Basket.");
        digitalWrite(empty,LOW);
        digitalWrite(half,LOW);
        digitalWrite(full,LOW);
  }
  delay(1000);
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

    if(distance >= 0 && distance <= max_height)
    {
        percentage = ((max_height - distance)*100)/max_height;
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
