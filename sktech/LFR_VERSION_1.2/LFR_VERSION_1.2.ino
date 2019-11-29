#define leftDir1 5   //IN2
#define leftDir2 7   //IN1
#define leftSpeed 6  //ENA

#define rightDir1 2  //IN4
#define rightDir2 4  //IN3
#define rightSpeed 3 //ENB

int sensor[6]={8, 9, 10, 11, 12, 13};

int sensorRead[6]={0};

void setup() {
  Serial.begin(9600);
  
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  
  for(int i=0;i<5;i++){
    pinMode(sensor[i],INPUT);
  }

  digitalWrite(leftSpeed,HIGH);
  digitalWrite(rightSpeed,HIGH);
  
}

void loop() {
  sensorReading();
  delay(500);
  if(sensorRead[0] == 1){
  while(sensorRead[0] == 1){
      rightForward();
      leftReverse();
      
      sensorReading();
    }
  }
  
  if(sensorRead[5] == 1){
  while(sensorRead[5] == 1){
      leftForward();
      rightReverse();
      
      sensorReading();
    }
  }
   
  else Forward();
}

void Forward(){

}

void leftForward() 
{
  digitalWrite(leftDir1, LOW);
  digitalWrite(leftDir2, HIGH);
}

void rightForward()
{
  digitalWrite(rightDir1, LOW);
  digitalWrite(rightDir2, HIGH);
}

void leftReverse() 
{
  digitalWrite(leftDir1, HIGH);
  digitalWrite(leftDir2, LOW);
}

void rightReverse()
{
  digitalWrite(rightDir1, HIGH);
  digitalWrite(rightDir2, LOW);
}

void sensorReading(){
  for(int i=0; i<6;i++){
    sensorRead[i] = digitalRead(sensor[i]);  
  }
  for(int i=0; i<6;i++){
    Serial.print(sensorRead[i]);
    Serial.print(" | ");
  }
  Serial.println("");
}

