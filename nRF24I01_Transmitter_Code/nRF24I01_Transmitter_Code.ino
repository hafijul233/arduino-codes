//Robo India Tutorial on nRF24L01
//Simple Code for transmitter


#include <SPI.h>                            //Communication Interface with modem
#include "nRF24L01.h"
#include "RF24.h"                          //library to control radio modem

RF24 radio(9, 10);                         //Creating an object

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
unsigned long Command ;
void setup()
{
  Serial.begin(57600);
  pinMode(4, INPUT);
  radio.begin();                        //activates modem
  radio.setRetries(15, 15);             //number of times modem retry to send data
  radio.openReadingPipe(1, pipes[1]);
  radio.startListening();
  radio.printDetails();
  radio.openWritingPipe(pipes[0]);     //sets address to recevier
  radio.openReadingPipe(1, pipes[1]);
  radio.stopListening();               //switch the modem to data transmission mode
}

void loop()
{
  Serial.println("Running");
  radio.stopListening();
 Command = 2;
  radio.write( &Command, sizeof(unsigned long) );  //blocks the program until it receives the acknowledgment
  radio.startListening();
  delay(1000);                                     //stops program for one second
}
