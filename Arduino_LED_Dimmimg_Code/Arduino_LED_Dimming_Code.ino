/*
  LED_Dimming
  This example shows how to fade an LED using the analogWrite() function.

  For detail: http://www.arduino.cc/en/Tutorial/Fading
*/

void setup() {
  pinMode(9,OUTPUT);
}

void loop() {
  // From min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(9, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // From max to min in decrements of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(9, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}
