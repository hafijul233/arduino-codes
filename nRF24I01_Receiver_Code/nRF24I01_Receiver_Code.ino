

//Robo India Tutorial on nRF24L01
//Simple Code for Receiver


#include <SPI.h>                           //Communication Interface with modem
#include "nRF24L01.h"
#include "RF24.h"                          //library to control radio modem

RF24 radio(9, 10);                         //Creating an object

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
typedef enum { role_ping_out = 1, role_pong_back } role_e;
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

role_e role = role_pong_back;

void setup(void)
{
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  radio.begin();                         //activates modem
  radio.setRetries(15, 15);
  radio.openReadingPipe(1, pipes[1]);
  radio.startListening();
  radio.printDetails();
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);
  radio.startListening();
}

void loop(void)
{
  Serial.println("Waiting");
  if (radio.available()) {               //check receive data
    unsigned long data = 0;
    radio.read( &data, sizeof(unsigned long) );
    Serial.println(data);
    
    if (data == 2){
      digitalWrite(4, HIGH);
    } else {
      digitalWrite(4, LOW);
    }
    delay(20);
  }
}
