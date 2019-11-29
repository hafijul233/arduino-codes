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

//Initialise the LCD
LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

//System Pin Definition
const int voltageSensor = A0;
const int currentSensor[5] = {A1, A2, A3, A4, A5};
const int devices[5] = {2, 3, 4, 5, 6};
const int controllerPins[5] = {7, 8, 9, 12, 13};

//System Constants
const int mVperAmp = 100; // 185 for 5A , 100 for 20A and 66 for 30A Sensor Module
double current, voltage;
double consumePower[5];
String StatusReport;
int controllers[5] ={0};

//Lcd Constants
const int maxRange = 50;
int inputLength = 0;
char inputArray[maxRange]; 

void setup()
{
  Serial.begin(9600);
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

void loop()
{
  for(int i=0; i < 5; i++){
    controllers[i] = digitalRead(controllerPins[i]);
  }
  for (int i = 0; i < 5; i++) {
    if(controllers[i] == LOW){//LOW == Power ON
      digitalWrite(devices[i], LOW);
    }
    else if (controllers[i] == HIGH){//HIGH == Power OFF
      digitalWrite(devices[i], HIGH);
    }
    else{
      digitalWrite(devices[i], HIGH);//Default == Power OFF
    }
  }
  voltage = getVoltage();
  for (int i = 0; i < 2; i++) {
    current = getCurrent(currentSensor[i]);
    consumePower[i] = (voltage * current);
    
    StatusReport += "P" + String(i+1) + " : ";
    
    if(controllers[i] == HIGH){
    
      StatusReport += String("OFF , ");
    }
    else{
      
      StatusReport += String(consumePower[i]/1000,3) + "kW , ";
    }
  }
  delay(500);
  lcdMessage("  Power Status  ", StatusReport);
  StatusReport = "";
}

double getVoltage()
{
  double inputVoltage = 220.00;

  return inputVoltage;
}

double getCurrent(int pin) {
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here

  double voltage, vrms, arms;

  uint32_t start_time = millis();

  while ((millis() - start_time) < 1000) //sample for 1 Sec
  {
    readValue = analogRead(pin);
    // see if you have a new maxValue
    if (readValue > maxValue)
    {
      /*record the maximum sensor value*/
      maxValue = readValue;
    }
    if (readValue < minValue)
    {
      /*record the maximum sensor value*/
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
