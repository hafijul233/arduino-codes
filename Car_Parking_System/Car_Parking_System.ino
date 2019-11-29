//Libraries
#include "Ultrasonic.h"

//Define pins ultrasonic(trig,echo)
Ultrasonic ultrasonic(A0,A1);

//Define Pin values
#define blue 8
#define red 9
#define green 10
 
//Variables
int distance = 0;
int booked = 0;

//program start
void setup() {
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Car Parking System");
}

void loop()
{
  distance = ultrasonic.Ranging(CM); //Use 'CM' for centimeters or 'INC' for inches
     if(distance >= 100){
        Serial.println("Slot Empty");
        digitalWrite(green, HIGH);
        digitalWrite(red, LOW);
        digitalWrite(blue, LOW);
     }
     else{
       Serial.println("Slot Using");
       digitalWrite(red, HIGH);
       digitalWrite(green, LOW);
       digitalWrite(blue, LOW);
     }

  //every 1sec. 
  delay(1000);
}
