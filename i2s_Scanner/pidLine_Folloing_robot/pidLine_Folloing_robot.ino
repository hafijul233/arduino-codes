float pTerm, iTerm, dTerm;

float kp = 11, ki = 0, kd = 11; //kp && kd = 11 keep it
int integral, derivative;
int error, previousError, output;

int irSensors[] = {14, 15, 16, 17, 18}; //IR sensor pins
int irReadings[5];

int motor1Forward = 7; //in1
int motor1Backward = 5; //in2
int motor1pwmPin = 6; //ena

int motor2Forward = 4; //in3
int motor2Backward = 2; //in4
int motor2pwmPin = 3; //enb

int motor1newSpeed;
int motor2newSpeed;

int motor2Speed = 70; //Default 70
int motor1Speed = 120; //Default 120

void setup() 
{
  Serial.begin(9600); //debug console

  //Declare all IR sensors as inputs
  for (int pin = 0; pin < 5; pin++) {
    pinMode(irSensors[pin], INPUT);
  }

  //motor 1 Configuration
  pinMode(motor1pwmPin, OUTPUT);
  pinMode(motor1Forward, OUTPUT);
  pinMode(motor1Backward, OUTPUT);

  //motor 2 configuration
  pinMode(motor2pwmPin, OUTPUT);
  pinMode(motor2Forward, OUTPUT);
  pinMode(motor2Backward, OUTPUT);

}

void loop() 
{
  //Put all of our functions here
  readIRSensors();
  calculateError();
  pidCalculations();
  changeMotorSpeed();
}

void readIRSensors() {
  //Read the IR sensors and put the readings in irReadings array
  for (int pin = 0; pin < 5; pin++) {
    irReadings[pin] = digitalRead(irSensors[pin]);
  }
}

void calculateError() {
  //Determine an error based on the readings
  if ((irReadings[0] == 0) && (irReadings[1] == 0) && (irReadings[2] == 0) && (irReadings[3] == 0) && (irReadings[4] == 1)) {
    error = 4;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 0) && (irReadings[2] == 0) && (irReadings[3] == 1) && (irReadings[4] == 1)) {
    error = 3;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 0) && (irReadings[2] == 0) && (irReadings[3] == 1) && (irReadings[4] == 0)) {
    error = 2;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 0) && (irReadings[2] == 1) && (irReadings[3] == 1) && (irReadings[4] == 0)) {
    error = 1;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 0) && (irReadings[2] == 1) && (irReadings[3] == 0) && (irReadings[4] == 0)) {
    error = 0;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 1) && (irReadings[2] == 1) && (irReadings[3] == 0) && (irReadings[4] == 0)) {
    error = -1;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 1) && (irReadings[2] == 0) && (irReadings[3] == 0) && (irReadings[4] == 0)) {
    error = -2;
  } else if ((irReadings[0] == 1) && (irReadings[1] == 1) && (irReadings[2] == 0) && (irReadings[3] == 0) && (irReadings[4] == 0)) {
    error = -3;
  } else if ((irReadings[0] == 1) && (irReadings[1] == 0) && (irReadings[2] == 0) && (irReadings[3] == 0) && (irReadings[4] == 0)) {
    error = -4;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 0) && (irReadings[2] == 0) && (irReadings[3] == 0) && (irReadings[4] == 0)) {
    if (previousError == -4) {
      error = -5;
    } else {
      error = 5;
    }
  } else if ((irReadings[0] == 1) && (irReadings[1] == 1) && (irReadings[2] == 1) && (irReadings[3] == 1) && (irReadings[4] == 1)) {
    error = 0;
  }
}

void pidCalculations() {
  pTerm = kp * error;
  integral += error;
  iTerm = ki * integral;
  derivative = error - previousError;
  dTerm = kd * derivative;
  output = pTerm + iTerm + dTerm;
  previousError = error;
}

void changeMotorSpeed() {
  //Change motor speed of both motors accordingly
  motor2newSpeed = motor2Speed + output;
  motor1newSpeed = motor1Speed - output;
  //Constrain the new speed of motors to be between the range 0-255
  constrain(motor2newSpeed, 0, 255);
  constrain(motor1newSpeed, 0, 255);
  
  //Set new speed, and run motors in forward direction
  analogWrite(motor2pwmPin, motor2newSpeed);
  analogWrite(motor1pwmPin, motor1newSpeed);
  
  digitalWrite(motor2Forward, HIGH);
  digitalWrite(motor2Backward, LOW);
  
  digitalWrite(motor1Forward, HIGH);
  digitalWrite(motor1Backward, LOW);
}
