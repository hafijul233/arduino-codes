/*
  Blink
  Turns an LED on for one second, then off for one second, repeatedly.
*/

void setup() {
  //pinMode(pin number, pin state);Ex: digital pin number: A5
  pinMode(8, OUTPUT);
}

// the loop function runs over and over again forever//// On Off On Off.................................
void loop() {
  digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level up or 5Volt)
  delay(1000);                       // wait for a second                 /*1s = 1000 mmilisecond*/
  digitalWrite(8, LOW);    // turn the LED off by making the voltage LOW or (digital 0Volt)
  delay(1000);                       // wait for a second
}
