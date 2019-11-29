#include <Servo.h>
 
//Motor pinOut
#define enb 3
#define in4 2
#define in3 4

#define ena 6
#define in2 5
#define in1 7

//Ultrasonic Sensor pinOut
#define trigger A4
#define echo A5

//Servo pinOut
#define servoPin 9


Servo sensor;

void setup()
{
  Serial.begin(9600);
  sensor.attach(servoPin);
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);

  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  
  analogWrite(ena, 125);
  analogWrite(enb, 125);
  
}

void loop()
{
  double distance = distanceRange();

  if(distance <= 15.00)
  {
    left();
  }
  else
  {
      forward();
  }
  delay(300);
}

void forward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
}


void backward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
}

void left()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
}

void right()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
}


double distanceRange()
{
  double time, distance;

  digitalWrite(trigger,LOW);
    delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
    delayMicroseconds(10);
  digitalWrite(trigger,LOW);
    delayMicroseconds(2);
 
  time=pulseIn(echo,HIGH);
    distance = time*340/20000;//CM
  Serial.println(distance);
  
  return distance;
}
