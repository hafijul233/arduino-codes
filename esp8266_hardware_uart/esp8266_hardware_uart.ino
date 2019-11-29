#include <SoftwareSerial.h>
#include <rdm6300.h>

#define RDM6300_RX_PIN 2
#define READ_LED_PIN 8

String rfid = "";
char rfidChar[8];

Rdm6300 rdm6300;
//SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
	Serial.begin(9600);
  //mySerial.begin(115200);
  
  pinMode(READ_LED_PIN, OUTPUT);
	digitalWrite(READ_LED_PIN, LOW);
	
	rdm6300.begin(RDM6300_RX_PIN);
	
	Serial.println("\nPlace RFID tag near the rdm6300...");
}

void loop() {
	if (rdm6300.update()) {
		Serial.println(rdm6300.get_tag_id(),HEX);
	  digitalWrite(READ_LED_PIN, rdm6300.is_tag_near());
	  rfid.toCharArray(rfidChar, 6);
    Serial.print(rfidChar);
	  delay(10);
	}
}
