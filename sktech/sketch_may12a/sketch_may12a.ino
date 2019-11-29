#define Left_Dir1 5
#define Left_Dir2 7
#define Left_Speed 6
#define Right_Dir1 2
#define Right_Dir2 4
#define Right_Speed 3

int flagr,flagl,flagc;

void setup() {
 pinMode(Left_Dir1, OUTPUT);
  pinMode(Left_Dir2, OUTPUT);
  pinMode(Left_Speed, OUTPUT);
  pinMode(Right_Dir1, OUTPUT);
  pinMode(Right_Dir2, OUTPUT);
  pinMode(Right_Speed, OUTPUT);

  pinMode(9, INPUT);//r
  pinMode(10, INPUT);//c
  pinMode(11, INPUT);//l

  
}

void loop() {
  
  flagr = digitalRead(9);
  flagc = digitalRead(10);
  flagl = digitalRead(11);
  
  if(flagr == 1 && flagc == 0 && flagl == 0){
    Left_Forward();
    Forward();
  }
  if(flagr == 0 && flagc == 1 && flagl == 0){
    Forward();
  }
  if(flagr == 0 && flagc == 0 && flagl == 1){
    Right_Forward();
    Forward();
  }
  
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

void Go(int s = 127)
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
