/*
 * A simple example to interface with rdm6300 rfid reader using AltSoftSerial.
 * We use AltSoftSerial uart instead of the default software uart driver.
 *
 * Connections:
 *     | Board            | RX Pin | PWM Unusable | Pin Unusable |
 *     |------------------+--------+--------------+--------------|
 *     | Teensy 3.0 & 3.1 |     20 |           22 |           21 |
 *     | Teensy 2.0       |     10 |            - |            9 |
 *     | Teensy++ 2.0     |      4 |       26, 27 |           25 |
 *     | Arduino Uno      |      8 |           10 |            9 |
 *     | Arduino Leonardo |     13 |            - |            5 |
 *     | Arduino Mega     |     48 |       44, 45 |           46 |
 *     | Wiring-S         |      6 |            4 |            5 |
 *     | Sanguino         |     14 |           12 |           13 |
 *
 * Arad Eizen (https://github.com/arduino12) 08/05/19, 09/06/19, 22/06/19.
 */

#include <rdm6300.h>
#include <AltSoftSerial.h>

#define RDM6300_RX_PIN 8
#define READ_LED_PIN 13

Rdm6300 rdm6300;
AltSoftSerial alt_soft_serial;


void setup()
{
	Serial.begin(115200);

	pinMode(READ_LED_PIN, OUTPUT);
	digitalWrite(READ_LED_PIN, LOW);

	alt_soft_serial.begin(RDM6300_BAUDRATE);
	rdm6300.begin(&alt_soft_serial);

	Serial.println("\nPlace RFID tag near the rdm6300...");
}

void loop()
{
	/* if non-zero tag_id, update() returns true- a new tag is near! */
	if (rdm6300.update())
		Serial.println(rdm6300.get_tag_id(), HEX);

	digitalWrite(READ_LED_PIN, rdm6300.is_tag_near());

	delay(10);
}
