#define Left_Dir1 5
#define Left_Dir2 7
#define Left_Speed 6

#define Right_Dir1 2
#define Right_Dir2 4
#define Right_Speed 3

int sensor[3]={8, 10, 12};

void setup()
{
  Serial.begin(9600);
  
  pinMode(Left_Dir1, OUTPUT);
  pinMode(Left_Dir2, OUTPUT);
  pinMode(Left_Speed, OUTPUT);
  pinMode(Right_Dir1, OUTPUT);
  pinMode(Right_Dir2, OUTPUT);
  pinMode(Right_Speed, OUTPUT);
  
  for(int i=0; i<3; i++) {
    pinMode(sensor[i], INPUT);
  }
  
  Forward();
}

void loop()
{

   lineFollow();
}

void Left_Forward() 
{
  digitalWrite(Left_Dir1, LOW);
  digitalWrite(Left_Dir2, HIGH);
}

void Left_Reverse() 
{
  digitalWrite(Left_Dir1, HIGH);
  digitalWrite(Left_Dir2, LOW);
}

void Right_Forward()
{
  digitalWrite(Right_Dir1, LOW);
  digitalWrite(Right_Dir2, HIGH);
}

void Right_Reverse()
{
  digitalWrite(Right_Dir1, HIGH);
  digitalWrite(Right_Dir2, LOW);
}

void Go(int s)
{
  analogWrite(Right_Speed, s);
  analogWrite(Left_Speed, s);
}

void Forward()
{
  Left_Forward();
  Right_Forward();
}

void Reverse() 
{
  Left_Reverse();
  Right_Reverse();
}

void Turn_Left() 
{
  Right_Forward();
  Left_Reverse();
}

void Turn_Right() 
{
  Right_Reverse();
  Left_Forward();
}

void Stop() 
{
  analogWrite(Left_Speed,0);
  analogWrite(Right_Speed, 0);
}

void lineFollow(void) {
   analogWrite(Left_Speed, HIGH);
   analogWrite(Right_Speed, HIGH);
   if(sensor[0]== HIGH) Turn_Left();
   if(sensor[1]==HIGH) Forward();
   if(sensor[2]==HIGH) Turn_Right();
}

