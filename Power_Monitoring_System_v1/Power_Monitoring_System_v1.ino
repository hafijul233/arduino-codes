#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

/*
 * Define I2C Address where the PCF8574A is Every Device address is Different 
 * use i2c scanner.ino to check on Serial Monitor
 */
 
#define I2C_ADDR          0x3F //it is this onecs value
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

//Single Line Scrolling 
int screenWidth = 16;
int screenHeight = 2;

// just some reference flags
int stringStart, stringStop = 0;
int scrollCursor = screenWidth;


//Global Variable
int totalPower = 200;
int device1Power = 120, device2Power = 800, device3Power = 600, device4Power = 100;

//Second Line msg 
  String line2 =  "Device 1: ";/* + String(device1Power) + " kWh # "
                       + "Device 2: " + String(device2Power) + " kWh # "
                       + "Device 3: " + String(device3Power) + " kWh # "
                       + "Device 4: " + String(device4Power) + "kWh";*/

void setup() {
      
    Serial.begin(9600);
    
    //LCD Configuration
    lcd.begin (16,2);
    lcd.clear();
    lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
    lcd.setBacklight(HIGH);

    //Welcome Note
    lcd.clear();
    lcd.setCursor(0,0);
      lcd.print("   WELCOME TO   ");
    lcd.setCursor(0,1);
      //lcd.autoscroll();
        lcd.print("Power Consumption Monitoring System");
        delay(400);
      //lcd.noAutoscroll();
      delay(1000);
   lcd.clear();
}

void loop() {
  //First Row Text
  lcd.setCursor(0,0);
    lcd.print("T.Power: ");
      lcd.print(totalPower);
    lcd.print("kWh");

  //Second Row Text
  lcd.setCursor(scrollCursor, 1);
  lcd.print(line2.substring(stringStart,stringStop));
  
  delay(400);
  
  lcd.clear();
  if(stringStart == 0 && scrollCursor > 0){
    scrollCursor--;
    stringStop++;
  } 
  else if (stringStart == stringStop){
    stringStart = stringStop = 0;
    scrollCursor = screenWidth;
  }
  else if (stringStop == line2.length() && scrollCursor == 0) {
    stringStart++;
  }
  else {
    stringStart++;
    stringStop++;
  }
}
