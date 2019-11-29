/*  This code will only work with:
 *  "Robotic Starter Kit (Arduino)" (Link: https://www.techshopbd.com/product-categories/kits/2498/robotic-starter-kit-arduino-techshop-bangladesh)
 *  
 *  CONNECTION:
 *  L293D     ARDUINO
 *  -----     -------
 *  ENA       6
 *  IN1       7
 *  IN2       5
 *  IN3       4
 *  IN4       2
 *  ENB       3
 *  VCC       Vin
 *  GND       GND
 *  
 *  SENSOR    ARDUINO
 *  ------    -------
 *  VCC       5V
 *  GND       GND
 *  SEN1      12
 *  SEN2      13
 *  
 *  Developer: 
 *       Md. Fahimul Islam
 *       Research Engineer
 *       fahimul@techshopbd.com
 *       http://www.TechShopBD.com 
 */

int last_direction  = 0;    //variable declaration
int robot_speed     = 200;  //Set the Robot Speed (between 0 and 200)

#define DELAYMS 10

#define FORWARD     0   //flag define
#define HARD_LEFT   1   //flag define
#define HARD_RIGHT  2   //flag define
#define SOFT_LEFT   3   //flag define
#define SOFT_RIGHT  4   //flag define

#define leftMotorPWM  6  //connect other end to ENABLE A of L293d
#define rightMotorPWM 3  //connect other end to ENABLE B of L293d

#define leftSensor    12
#define rightSensor   13

#define leftMotor1  2
#define leftMotor2  4
#define rightMotor1 5
#define rightMotor2 7

void setup()
{
  Serial.begin(9600);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  delay(100);
  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);
  delay(100);
  
  analogWrite(leftMotorPWM, robot_speed);
  analogWrite(rightMotorPWM, robot_speed);
  delay(100);
}


void loop()
{
  int left_reading = digitalRead(leftSensor);
  int right_reading = digitalRead(rightSensor);
  if(left_reading==1 && right_reading==1) // When both sensors are on black line
   {
      Serial.println("forward");
      robot_move(FORWARD);                //move FORWARD
      last_direction=FORWARD;             //save FORWARD in the variable named last direction
    }
  else if(left_reading==1 && right_reading==0) // When left sensor is on black line
   {
      Serial.println("soft left");
      robot_move(SOFT_LEFT);              //move left
      last_direction=HARD_LEFT;           //save left in the variable named last direction
   }
  
  else if(left_reading==0 && right_reading==1)// When right sensor is on black line
   {
      Serial.println("soft right");
      robot_move(SOFT_RIGHT);            //move right
      last_direction=HARD_RIGHT;         //save right in the variable named last direction
   }
  
  else if (left_reading==0 && right_reading==0)// When none of the sensors is on black line
   {
      Serial.println("memory");
      robot_move(last_direction);       //move to last direction
   }
  delay(DELAYMS);
}



void robot_move(int direc)              //define a function named robot_move which will return direction
{
  if (direc == FORWARD) {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
  }  //{analogWrite(leftMotor1, robot_speed); digitalWrite(leftMotor2, LOW); analogWrite(rightMotor1, robot_speed); digitalWrite(rightMotor2, LOW); delay(1);}
  
  else if (direc == SOFT_LEFT) {
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);  
    digitalWrite(rightMotor1, HIGH); 
    digitalWrite(rightMotor2, LOW);
  }  //{digitalWrite(leftMotor1, LOW); digitalWrite(leftMotor2, LOW); analogWrite(rightMotor1, robot_speed); digitalWrite(rightMotor2, LOW); delay(1);}
  
  else if (direc == HARD_LEFT) {
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
  }  //{digitalWrite(leftMotor1, LOW); analogWrite(leftMotor2, robot_speed); analogWrite(rightMotor1, robot_speed); digitalWrite(rightMotor2, LOW); delay(1);}
  
  else if (direc == SOFT_RIGHT){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
  }  //{analogWrite(leftMotor1, robot_speed); digitalWrite(leftMotor2, LOW); digitalWrite(rightMotor1, LOW); digitalWrite(rightMotor2, LOW); delay(1);}
  
  else if (direc == HARD_RIGHT){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
  }  //{analogWrite(leftMotor1, robot_speed); digitalWrite(leftMotor2, LOW); digitalWrite(rightMotor1, LOW); analogWrite(rightMotor2, robot_speed); delay(1);}
}

