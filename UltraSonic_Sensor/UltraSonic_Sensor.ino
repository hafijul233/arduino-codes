#include <SoftwareSerial.h>

// defines pins numbers
const int trigPin = A0;
const int echoPin = A1;
// defines variables

long duration;
float distance;
String SendData;

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
    Serial.begin(4800);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  // set the data rate for the SoftwareSerial port
  mySerial.begin(19200);
  mySerial.write("Hello, world?"); 
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= (duration*0.034)/2.0;
  Serial.println(distance);
  //SendData = "Distance: " + String(distance) + "CM";
  mySerial.write(distance);
  delay(1000);
}
