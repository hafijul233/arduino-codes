
int motor1Forward = 7; //in1
int motor1Backward = 5; //in2
int motor1pwmPin = 6; //ena

int motor2Forward = 4; //in3
int motor2Backward = 2; //in4
int motor2pwmPin = 3; //enb

int motor1newSpeed;
int motor2newSpeed;

int motor2Speed = 255; //Default 70
int motor1Speed = 25 5; //Default 120

void setup() 
{
  Serial.begin(9600); //debug console
  
  //motor 1 Configuration
  pinMode(motor1pwmPin, OUTPUT);
  pinMode(motor1Forward, OUTPUT);
  pinMode(motor1Backward, OUTPUT);

  //motor 2 configuration
  pinMode(motor2pwmPin, OUTPUT);
  pinMode(motor2Forward, OUTPUT);
  pinMode(motor2Backward, OUTPUT);
  
  analogWrite(motor2pwmPin, motor2Speed);
  analogWrite(motor1pwmPin, motor1Speed);
}

void loop()
{
  if(Serial.available()) {
    char c = Serial.read();
    switch(c) {
    case 'F' : forward();
        break;
    
    case 'B' : backward();
        break;
    
    case 'L' : left();
        break;
    
    case 'R' : right();
        break;

    case 'S' : stop();
        break;
        
    default : forward();
        break;
    }
  }
}

void forward() 
{
  digitalWrite(motor2Forward, HIGH);
  digitalWrite(motor2Backward, LOW);
  
  digitalWrite(motor1Forward, HIGH);
  digitalWrite(motor1Backward, LOW);
}

void backward() 
{
  digitalWrite(motor2Forward, LOW);
  digitalWrite(motor2Backward, HIGH);
  
  digitalWrite(motor1Forward, LOW);
  digitalWrite(motor1Backward, HIGH);
}

void left() 
{
  digitalWrite(motor2Forward, HIGH);
  digitalWrite(motor2Backward, LOW);
  
  digitalWrite(motor1Forward, LOW);
  digitalWrite(motor1Backward, LOW);
}

void right() 
{
  digitalWrite(motor2Forward, LOW);
  digitalWrite(motor2Backward, LOW);
  
  digitalWrite(motor1Forward, HIGH);
  digitalWrite(motor1Backward, LOW);
}

void stop() 
{
  digitalWrite(motor2Forward, LOW);
  digitalWrite(motor2Backward, LOW);
  
  digitalWrite(motor1Forward, LOW);
  digitalWrite(motor1Backward, LOW);
}
