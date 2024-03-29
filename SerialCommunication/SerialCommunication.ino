#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

String RetriveData;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(19200);
}

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.println(mySerial.read());
  }
}
