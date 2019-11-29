#define SenseBULB1 46
#define SenseBULB2 48
#define SenseBULB3 50
#define SenseFAN1  52

#define BULB1 47
#define BULB2 49
#define BULB3 51
#define FAN1  53 

char command;

void setup() {
  
  Serial.begin(9600);
  
  pinMode(BULB1,OUTPUT);
  pinMode(BULB2,OUTPUT);
  pinMode(BULB3,OUTPUT);
  pinMode(FAN1,OUTPUT);
  
}

void loop() 
{
  if (Serial.available() > 0) {
    command = Serial.read();
    
    //For Light 1
    if (digitalRead(SenseBULB1) == LOW){
      Serial.print("AC light 1 is On");
      digitalWrite(BULB1,LOW);
    }
  if (digitalRead(SenseBULB1) == HIGH){
      Serial.print("AC light 1 is Off");
      digitalWrite(BULB1,HIGH);
  }

  //For Light 2
  if (digitalRead(SenseBULB2) == LOW){
      Serial.print("AC light 2 is On");
      digitalWrite(BULB2,LOW);
  }
  if (digitalRead(SenseBULB2) == HIGH){
      Serial.print("AC light 2 is Off");
      digitalWrite(BULB2,HIGH);
    }

  //For Light 3
  if (digitalRead(SenseBULB3) == LOW){
      Serial.print("AC light 3 is On");
      digitalWrite(BULB3,LOW);
  }
  if (digitalRead(SenseBULB3) == HIGH){
      Serial.print("AC light 3 is Off");
      digitalWrite(BULB3,HIGH);
    }
  
  //For FAN 1
  if (digitalRead(SenseFAN1) == HIGH){
      Serial.print("AC FAN 1 is On");
      digitalWrite(FAN1,LOW);
    }
  if (digitalRead(SenseFAN1) == HIGH){
      Serial.print("AC FAN 1 is Off");
      digitalWrite(FAN1,HIGH);              
    }
  }
  delay(500);
}
