#include <SoftwareSerial.h>

#define enA 3
#define in1 2
#define in2 4

#define in3 5
#define in4 7
#define enB 6

// RX is digital pin 10 (connect to TX of other device)
// TX is digital pin 11 (connect to RX of other device)
SoftwareSerial comSerial(10, 11); // RX, TX

char c;

void setup()
{
  comSerial.begin(19200);
  Serial.begin(9600);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);

}

void loop() 
{
  if (comSerial.available()) 
  {
    c = comSerial.read();
    Serial.println((int)c);
    switch (c)
    {
      case 'f' : forward();
        Serial.println("FORWARD");
        break;

      case 'b' : backward();
        Serial.println("BACKWARD");
        break;

      case 'l' : left();
        Serial.println("LEFT");
        break;

      case 'r' : right();
        Serial.println("RIGHT");
        break;

      case 's' : stop();
        Serial.println("STOP");
        break;

      default : stop();
        Serial.println("Stop");
        break;
    }
    delay(1000);
  }
  else {
    Serial.println("Waiting...");
  }
}

void forward() 
{
  analogWrite(enA, 200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enB, 200);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

}

void backward() 
{
  analogWrite(enA, 200);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enB, 200);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

}

void left() 
{
  analogWrite(enA, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  analogWrite(enB, 200);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

}

void right() 
{
  analogWrite(enA, 200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enB, 0);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

}

void stop() 
{
  analogWrite(enA, 200);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  analogWrite(enB, 200);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

}
