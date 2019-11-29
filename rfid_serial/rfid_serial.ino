#include <rdm6300.h>

#define RDM6300_RX_PIN 4
#define READ_LED_PIN 13

char idArray[10];
String rfid;

Rdm6300 rdm6300;

void setup()
{
  Serial.begin(9600);
  
  pinMode(READ_LED_PIN, OUTPUT);
  digitalWrite(READ_LED_PIN, LOW);
  
  rdm6300.begin(RDM6300_RX_PIN);
  Serial.println("INIT");
}

void loop()
{
  if (rdm6300.update()) {
    rfid = rdm6300.get_tag_id();
    if (rdm6300.is_tag_near() == true) {
      digitalWrite(READ_LED_PIN, HIGH);
    }
    rfid.toCharArray(idArray, rfid.length());
    Serial.println(rfid);
  }
  delay(10);
}
