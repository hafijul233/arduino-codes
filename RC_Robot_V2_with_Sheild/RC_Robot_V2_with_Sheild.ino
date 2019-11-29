/* JoyStick module receiver code
  - CONNECTIONS: nRF24L01 Modules See:
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 6
   4 - CSN to Arduino pin 8
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED

  Symbol Used
  Bt = Bluetooth
  Rd = Radio
  Celb = Celebration

*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Radio Configuration
#define CE_PIN   9
#define CSN_PIN 10

//Celebration LED Configuration
#define Celb_LED    8

//MotoR Driver Configuration
#define ENA_m1 3         // ENA_m1 enable/speed motor Front Right 
#define ENB_m1 6         // ENA_m1 enable/speed motor Back Right

#define IN_1  2          // L298N #1 in 1 motor Right
#define IN_2  4          // L298N #1 in 2 motor Right

#define IN_3  5          // L298N #2 in 3 motor Left
#define IN_4  7          // L298N #2 in 4 motor Left

//System Constant Vaiables
const uint64_t pipe = 0xE8E8F0F0E1LL;
const int std_high = 600;
const int std_low = 300;

// System Variables & Objects
RF24 radio(CE_PIN, CSN_PIN);

int data[9];
int xAxis, yAxis;
char command;

// the Six btn variables from joystick
int btnUp;
int btnRight;
int btnDown;
int btnLeft;
int btnPush;
int btnE;
int btnF;

// Conntrol Functions
void forward()
{
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  Serial.println("FORWARD");

}

void backward()
{
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

  Serial.println("BACKWARD");
}

void left()
{
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  Serial.println("LEFT");
}

void right()
{
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);

  Serial.println("RIGHT");
}

void stop()
{
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);

  Serial.println("STOP");
}

void celebration()
{
  digitalWrite(Celb_LED, HIGH);
  delay(3000);
  digitalWrite(Celb_LED, LOW);

  Serial.println("CELEBRATION");
}

void RdControl ()
{
  if ( radio.available())
  {
    radio.read( data, sizeof(data) );
    xAxis = data[0];
    yAxis = data[1];
    // Key btn Controls
    btnPush  = data[2]; //PUSH
    btnUp    = data[3]; //A
    btnRight = data[4]; //B
    btnDown  = data[5]; //C
    btnLeft  = data[6]; //D
    btnE  = data[7];  //E
    btnF  = data[8];  //F

    for (int i = 0; i < 9; i++ ) {
      Serial.print("Value (");
      Serial.print(i);
      Serial.print(") : ");
      Serial.println(data[i]);
    }
    Serial.println("----------------------------");


    // Buttons Responses
    if ( btnUp == LOW || btnRight == LOW ||
         btnDown == LOW || btnLeft == LOW )
    {
      if (btnUp == LOW)
        forward();

      else if (btnRight == LOW)
        right();

      else if (btnDown == LOW)
        backward();

      else if (btnLeft == LOW)
        left();

      else
        stop();
    }

    else if (btnPush == LOW)
    {
      celebration();
    }

    else
    {
      if (xAxis > std_high)
        right();

      else if (xAxis < std_low)
        left();

      else if (yAxis > std_high)
        forward();

      else if (yAxis < std_low)
        backward();

      else if ((yAxis > std_low && yAxis < std_high) && (xAxis > std_low && xAxis < std_high) )
        stop();

      else
        stop();
    }
  }
}

/*void BtControl()
  {
  command = Serial.read();
  switch (command)
  {
    case 'F' : forward();
      break;

    case 'B' : backward();
      //Serial.println("BACKWARD");
      break;

    case 'L' : left();
      //Serial.println("LEFT");
      break;

    case 'R' : right();
      //Serial.println("RIGHT");
      break;

    case 'S' : stop();
      //Serial.println("STOP");
      break;

    default : stop();
      //Serial.println("Stop");
      break;
  }
  }
*/
void setup()
{
  pinMode(Celb_LED, OUTPUT);

  pinMode(ENA_m1, OUTPUT);
  pinMode(ENB_m1, OUTPUT);

  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void loop() {
  if (radio.available()) // When Receiving Data from Radio
  {
    radio.read( data, sizeof(data) );
    xAxis = data[0];
    yAxis = data[1];
    // Key btn Controls
    btnPush  = data[2]; //PUSH
    btnUp    = data[3]; //A
    btnRight = data[4]; //B
    btnDown  = data[5]; //C
    btnLeft  = data[6]; //D
    btnE  = data[7];  //E
    btnF  = data[8];  //F

    /*for(int i =0; i<9; i++ ){
      Serial.print("Value (");
      Serial.print(i);
      Serial.print(") : ");
      Serial.println(data[i]);
      }
      Serial.println("----------------------------");
    */

    // Buttons Responses
    if ( btnUp == LOW || btnRight == LOW ||
         btnDown == LOW || btnLeft == LOW )
    {
      if (btnUp == LOW)
        forward();

      else if (btnRight == LOW)
        right();

      else if (btnDown == LOW)
        backward();

      else if (btnLeft == LOW)
        left();

      else
        stop();
    }

    else if (btnPush == LOW)
    {
      celebration();
    }

    else
    {
      if (xAxis > std_high)
        right();

      else if (xAxis < std_low)
        left();

      else if (yAxis > std_high)
        forward();

      else if (yAxis < std_low)
        backward();

      else if ((yAxis > std_low && yAxis < std_high) && (xAxis > std_low && xAxis < std_high) )
        stop();

      else
        stop();
    }
  }

//if (Serial.available()) // When Receiving Data from Bluetooth
//BtControl();
}
