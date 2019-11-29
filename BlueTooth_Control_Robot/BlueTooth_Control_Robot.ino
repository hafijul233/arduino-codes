#include <Wire.h>
#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

char command = 'S';

void setup()
{
  Serial.begin(9600);
 
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  
  Stop();
}

void loop() {
  if(Serial.avaliable()>0)
  {

    command = Serial.read();

    switch(command){

      case 'F': Forward();
                break;

      case 'B': Backward();
                break;

      case 'L': Left();
                break;

      case 'R': Right();
                break;

      case 'S': Stop();
                break;

      default: Stop();
                break;
    }
  }
  delay(1000);
}

void Forward()
{
  motor1.run(Forward);
  motor2.run(Forward);
  motor3.run(Forward);
  motor4.run(Forward);
}

void Backward()
{
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
void Left()
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
void Right()
{
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void Stop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void ServoControl()
{

}
