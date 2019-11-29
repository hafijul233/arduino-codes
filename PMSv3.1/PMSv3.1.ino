#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

//Define LCD variables
#define I2C_ADDR          0x3F        //Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7

#define maxRange           50
//System Pin Definition
const int voltageSensor = 14; //analog pin layout 14 - 19 == A0 - A5
const int currentSensor[5] = {15, 16, 17, 18, 19};
const int devices[5] = {2, 3, 4, 5, 6};
const int controllerPins[5] = {7, 8, 9, 12, 13};

//System Constants
const int mVperAmp = 100; // 185 for 5A , 100 for 20A and 66 for 30A Sensor Module
double currents[5], voltage;
double consumePower[5];
String StatusReport;
int controllers[5] = {0};
String dataStream;
char dataStreamArray[maxRange];

//Lcd Constants
int inputLength = 0;
char inputArray[maxRange];

//Initialise the LCD
LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

//Initialise the Software Serial
SoftwareSerial dataSerial(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  dataSerial.begin(115200);

  //Define the LCD as 16 column by 2 rows
  lcd.begin (16, 2);
  //Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.clear();
  lcdMessage("   WELCOME TO   ", "Power Monitoring System");

  //Input Pin Allocation
  pinMode(voltageSensor, INPUT);
  for (int i = 0; i < 5; i++) {
    pinMode(currentSensor[i], INPUT);
    //Output Pin Allocation
    pinMode(devices[i], OUTPUT);
    //Controllers Pin Allocation
    pinMode(controllerPins[i], INPUT);
  }
  delay(500);
  lcd.clear();
}

void loop() {

  for (int i = 0; i < 5; i++) {
    digitalWrite(devices[i], LOW);
  }
  voltage = getVoltage();
  for (int i = 0; i < 2; i++) {
    currents[i] = getCurrent(currentSensor[i]);
    consumePower[i] = (voltage * currents[i]);
    StatusReport += "P" + String(i + 1) + " : ";
    StatusReport += String(consumePower[i] / 1000, 3) + "kW , ";
  }
  
  lcdMessage("  Power Status  ", StatusReport);

  dataStream = String(voltage) + "A" + String(currents[0], 3) + "A" + String(currents[1], 3)
               + "A" + String(currents[2], 3) + "A" + String(currents[3], 3)
               + "A" + String(currents[4], 3);

  dataStream.toCharArray(dataStreamArray, maxRange);
  dataSerial.write(dataStreamArray);
  dataStream = "";
  StatusReport = "";
  delay(500);
}

double getVoltage() {
  double inputVoltage = 220.00;
  return inputVoltage;
}

double getCurrent(int pin) {
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  double voltage, vrms, arms;
  uint32_t start_time = millis();

  while ((millis() - start_time) < 1000) { //sample for 1 Sec
    readValue = analogRead(pin);
    // see if you have a new maxValue
    if (readValue > maxValue) {
      /*record the maximum sensor value*/
      maxValue = readValue;
    }
    if (readValue < minValue) {
      //record the maximum sensor value
      minValue = readValue;
    }
  }
  
  // Subtract min from max
  voltage = ((maxValue - minValue) * 5.0) / 1024.0;
  vrms = (voltage / 2.0) * 0.707;
  arms = (vrms * 1000) / mVperAmp;
  
  return arms;
}

void lcdMessage(String FirstRow, String SecondRow) {
  inputLength = SecondRow.length();
  lcd.clear();
  lcd.print(FirstRow);
  if (inputLength <= 16) {
    lcd.setCursor(0, 1);
    lcd.print(SecondRow);
  }
  else if (inputLength > maxRange) {
    Serial.println("This string is too long.");
  }
  else {
    lcd.setCursor(0, 1);
    SecondRow.toCharArray(inputArray, maxRange);
    for (int i = 0; i <= 16; i++) {
      lcd.write(inputArray[i]);
    }

    delay(1500); //completion wait

    for (int j = 17; j <= inputLength; j++) {
      lcd.write(inputArray[j]);
      lcd.scrollDisplayLeft();

      lcd.setCursor(j - 16, 0);
      lcd.print(FirstRow);
      lcd.setCursor(j + 1, 1);
      delay(300);
    }
  }
}
