///Note: Relay are Active Low
#include <SoftwareSerial.h>

#define in4 7 //Light 1 working (Green)
#define in3 6 //Light 2 working (Blue)
#define in2 5 //Fan 1 
#define in1 4 //Fan 2
#define tx 3 //Bluetoth Transmitter
#define rx 2 //Bluetoth Receiver

//Software Serial for Bluetooth
SoftwareSerial bluetooth(rx, tx); // RX,TX

void setup()
{
  Serial.begin(115200);
  bluetooth.begin(9600);

  pinMode(in4, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in1, OUTPUT);

  digitalWrite(in4, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in1, HIGH);

}

void loop()
{
  if (bluetooth.available() > 0) {
    char c = bluetooth.read();
    switch (c) {
      case 'A' : {
          digitalWrite(in4, LOW);
          Serial.println("Light 1 is ON");
          break;
      } 
      case 'a' : {
          digitalWrite(in4, HIGH);
          Serial.println("Light 1 is OFF");
          break;
      }
      case 'B' : {
          digitalWrite(in3, LOW);
          Serial.println("Light 2 is ON");
          break;
      }
      case 'b' : {
          digitalWrite(in3, HIGH);
          Serial.println("Light 2 is OFF");
          break;
      }
      case 'C' : {
          digitalWrite(in2, LOW);
          Serial.println("Fan 1 is ON");
          break;
      }
      case 'c' : {
          digitalWrite(in2, HIGH);
          Serial.println("Fan 1 is OFF");
          break;
      }
      case 'S': {
          digitalWrite(in4, HIGH);
          digitalWrite(in3, HIGH);
          digitalWrite(in2, HIGH);
          digitalWrite(in1, HIGH);
          Serial.println("System is Power Off");
          break;
      }
    }
  }
}
