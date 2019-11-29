/*
  Blink
  Turns an LED on for one second, then off for one second, repeatedly.
*/

void setup() {
  //pinMode(pin number, pin state);Ex: digital pin number: A5
  pinMode(A5, OUTPUT);
}

// the loop function runs over and over again forever//// On Off On Off.................................
void loop() {
  digitalWrite(A5, HIGH);   // turn the LED on (HIGH is the voltage level up or 5Volt)
  delay(1000);                       // wait for a second                 /*1s = 1000 mmilisecond*/
  digitalWrite(A5, LOW);    // turn the LED off by making the voltage LOW or (digital 0Volt)
  delay(1000);                       // wait for a second
}
