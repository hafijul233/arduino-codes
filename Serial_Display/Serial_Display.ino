#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

char c , d;

void setup() {
  mySerial.begin(115200);
  Serial.begin(9600);
}

void loop() {
  if(mySerial.available()>2) {
    c = mySerial.read();
    d = mySerial.read();
    Serial.print("Axis X: ");
    Serial.print(x);
    Serial.print(" - Axis Y: ");
    Serial.println(y);
  }
}
