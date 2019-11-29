#define ena 10//leftMotor
#define in1 12//Lpositive
#define in2 13//LNegative

#define enb 11//RightMotor
#define in3 9//Rpositive
#define in4 8//RNegative

char command;

void setup() {  
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  Serial.begin(9600);
  
}

void loop() {
    if(Serial.available() > 0){ 
      command = Serial.read(); 
      switch(command){
        case 'F':  
          Forward();
            break;
            
        case 'B':  
          Backward();
            break;
            
        case 'L':  
          Left();
            break;
            
        case 'R':
          Right();
            break;
            
        case 'S':
          Stop();
            break;
            
        default: 
          Stop();
            break;
    }
  } 
}

void Forward()
{
  Speed(1);
  
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  
}
void Backward()
{
  Speed(1);
 digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

void Left()
{
  Speed(1);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
void Right()
{
  Speed(1);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
void Stop()
{
  Speed(0); 
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);

}

void Speed(int state){
  if(state == 1){
    digitalWrite(ena,HIGH);
    digitalWrite(enb,HIGH);
  }
  else{
    digitalWrite(ena,LOW);
    digitalWrite(enb,LOW);
  }
}

