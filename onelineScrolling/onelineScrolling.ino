#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

//Define variables 

#define I2C_ADDR          0x3F        //Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7

//Initialise the LCD
LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

String alwaysDisplay = "From serial:"; //The message that will always be displayed on row 1.
String input; //Where the string sent from the serial monitor is stored.
int inputLength = 0; //Where the length of the input string is stored.
char inputArray[40]; //The input string will be converted to a character array if it is longer than 16 characters,
                     // so that it can be written one character at a time.

void setup() {
  Serial.begin(9600); //Start serial communication.
  lcd.begin(16,2); //Initialize the LCD display's size (16 coloms, 2 rows).
      lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
    lcd.setBacklight(HIGH);
  lcd.clear(); //Clear the LCD screen, just in case!
  while(!Serial) {} //Wait for the user to open the serial monitor.
  Serial.println("Type a message to display on the LCD screen."); //Let the user know that they may begin sending data.
}

void loop() {
  if (Serial.available()) { //Wait for serial data to be sent by the user.
    delay(100); //Wait for the serial data to finish incoming.
    input = Serial.readString(); //Store the incoming data in "input" as a string.
    inputLength = input.length(); //Store the length of the string in "inputLength".
    lcd.clear(); //Clear the LCD screen of data from the last loop.
    lcd.print(alwaysDisplay); //Print the message on row 1.
    Serial.print(input);
    Serial.print(", ");
    Serial.println(inputLength); //Print the string and its length in the serial monitor
                                                                          //  [for debugging purposes].
   
    if (inputLength <= 16) { //If the string is up to 16 characters we simply need to move the cursor to row 2 and print the string.
      lcd.setCursor(0,1);
      lcd.print(input);
    }
    else if (inputLength > 39) Serial.println("This string is too long."); //Due to RAM constraints, strings longer than 39 characters
                                                                           //  are too buggy to be output to the display.
    else { //Strings longer than 16 characters, but still within RAM constraints get complicated...
      lcd.setCursor(0,1); //Move the cursor to row 2.
      input.toCharArray(inputArray,40); //Convert the string stored in "input" into a character array.
      for (int i = 0; i <= 16; i++) { //For the first 16 characters, simply print them to the LCD screen.
        lcd.write(inputArray[i]);
      }
      delay(1500); //Delay for 1.5 seconds so the user has time to read.
      for (int j = 17; j <= inputLength; j++) { //Now we begin printing from character 17 onward...
        lcd.write(inputArray[j]); //Write the j-th character (for now it will be off-screen).
        lcd.scrollDisplayLeft(); //Scroll the text left one character-space.

        //This is where things get tricky, because both rows will be scrolled. But we want row 1 to remain stationary!
        lcd.setCursor(j-16,0); //Set the cursor to the first character space on the first row [visually].
                               // cursor space (0,0) has been scrolled off-screen!
        lcd.print(alwaysDisplay); //Re-print the row 1 message.
        lcd.setCursor(j+1,1); //Set the cursor one character space to the right of the last printed character on row 2.
                              //  Which is visually one character space off-screen, in preparation for the next itteration.
        delay(300); //delay for .3 seconds so the user has time to read.
      }
    }
  }
}
