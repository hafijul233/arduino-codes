#include <SoftwareSerial.h>
// RX is digital pin 10 (connect to TX of other device)
// TX is digital pin 11 (connect to RX of other device)
SoftwareSerial comSerial(10, 11); // RX, TX
void setup() {
  comSerial.begin(9600);
  Serial.begin(19200);
}

void loop() {
  if(comSerial.available()) {
    char c = (char)comSerial.read();
    Serial.println(c);
    delay(1000);
  }
  else {
    Serial.println("Waiting ... ");
  }
}
