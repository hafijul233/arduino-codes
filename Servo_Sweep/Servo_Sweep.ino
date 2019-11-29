/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo first;
Servo second;// create servo object to control a servo
// twelve servo objects can be created on most boards

int posX = 0;    // variable to store the servo position
int posY = 0;

void setup() {
  first.attach(9);  // attaches the servo on pin 9 to the servo object
  second.attach(10);
}

void loop() {
  for (posX = 0,posY = 0; posX <= 180,posY<=180; posX += 1,posY+=1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    first.write(posX);              // tell servo to go to position in variable 'pos'
    second.write(posY);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (posX = 180,posY = 180; posX >= 0,posY >= 0; posX -= 1,posY-=1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    first.write(posX);              // tell servo to go to position in variable 'pos'
    second.write(posY);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

