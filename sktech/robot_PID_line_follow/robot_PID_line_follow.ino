#define Left_Dir1 5
#define Left_Dir2 7
#define Left_Speed 6
#define Right_Dir1 2
#define Right_Dir2 4
#define Right_Speed 3

int sensor[8] = { 8,9,10,11,12,13,14,15 }; // Pin assignment

int sensorReading[8] = { 0 }; // Sensor reading array

float activeSensor = 0; // Count active sensors
float totalSensor = 0; // Total sensor readings
float avgSensor = 4.5; // Average sensor reading

float Kp = 72;   // Max deviation = 8-4.5 = 3.5 ||  255/3.5 = 72
float Ki = 0.00015;
float Kd = 5;

float error = 0;
float previousError = 0;
float totalError = 0;

float power = 0;

int PWM_Right, PWM_Left;

void setup()
{
  Serial.begin(9600);
  
  pinMode(Left_Dir1, OUTPUT);
  pinMode(Left_Dir2, OUTPUT);
  pinMode(Left_Speed, OUTPUT);
  pinMode(Right_Dir1, OUTPUT);
  pinMode(Right_Dir2, OUTPUT);
  pinMode(Right_Speed, OUTPUT);
  
  for(int i=0; i<8; i++) {
    pinMode(sensor[i], INPUT);
  }
  
  Stop();
  
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

void PID_program()
{ 
    readSensor();
    
    previousError = error; // save previous error for differential 
    error = avgSensor - 4.5; // Count how much robot deviate from center
    totalError += error; // Accumulate error for integral
    
    power = (Kp*error) + (Kd*(error-previousError)) + (Ki*totalError);
    
    if( power>255 ) { power = 255.0; }
    if( power<-255.0 ) { power = -255.0; }
    
    if(power<0) // Turn left
    {
      PWM_Right = 255;
      PWM_Left = 255 - abs(int(power));
    }
    
    else // Turn right
    {
      PWM_Right = 255 - int(power);
      PWM_Left = 255;
    }  
}

void lineFollow(void) {
   PID_program();
   analogWrite(Left_Speed, PWM_Left);
   analogWrite(Right_Speed, PWM_Right); 
}

void readSensor(void) {
  for(int i=0; i<8; i++) 
    {
      sensorReading[i] = !digitalRead(sensor[i]);
      if(sensorReading[i]==1) { activeSensor+=1; }
      totalSensor += sensorReading[i] * (i+1);
    }
      
    avgSensor = totalSensor/activeSensor;
    activeSensor = 0; totalSensor = 0;
}

void testSensor(void) {
   for(int i=0; i<8; i++) {
    Serial.print(!digitalRead(sensor[i]));
  }
  Serial.println("");
  delay(20);
}

boolean checkSensor() {
  boolean state = 0;
  for(int i=0; i<8; i++) {
    if(digitalRead(sensor[1])==0) {state=1;}
  }
  return state;
}
