/*
  Fadding LED
  Turns an LED Dimming from off maximum light and reverse maximum to off, repeatedly.
  We will use analogWrite(); for this program
  For this we need to use only PWM Pins(~) symbol given in front of digital pins
  Ex Uno has pins:3,5,6,9,10,11 as PWM 
  
  For detail: https://www.arduino.cc/en/Tutorial/Fading
*/

void setup() {
  //pinMode(pin number, pin state);Ex: digital pin number: 3
  pinMode(3, OUTPUT);
}

// the loop function runs over and over again forever//// On Off On Off.................................
void loop() {
  for(int i=0;i<=255;i+=5){ // increment led power with 5
    analogWrite(3, i);   // turn the LED on grow with i equal power
    delay(30);
  }
  for(int i=255;i>=0;i-=5){// decrement led power with 5
    analogWrite(3, i);   // turn the LED on grow with i equal power
    delay(30);
  }
}
