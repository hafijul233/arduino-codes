#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

// defines pins numbers
#define tank_height 22 //in Centimeter
#define trigPin  A0 //D3
#define echoPin  A1 //D4

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial node_Mcu(10, 11); //RX, TX

void setup() {
  Serial.begin(9600);
  node_Mcu.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME TO   ");
  lcd.setCursor(0, 1);
  lcd.print("IoT Oil Monitor ");
  delay(1000);
  lcd.clear();
}

void loop() {

  float oilLevel = calculate_fuel();

  if (node_Mcu.available() > 0) {
    char errorCode = node_Mcu.read();
    error_handler(errorCode);
  } else {
    //LCD print
    lcd.setCursor(0, 0);
    if (oilLevel >= 0 && oilLevel < 2) {
      lcd.print("Warn: EMPTY");
    } else if (oilLevel >= 2 && oilLevel < 25) {
      lcd.print("Warn: LOW LEVEL");
    } else if (oilLevel >= 25 && oilLevel < 75) {
      lcd.print("Warn: MEDIUM");
    } else if (oilLevel >= 75 && oilLevel <= 100) {
      lcd.print("Warn: FULL");
    } else {
      oilLevel = 74369;
      lcd.print("Warn: INVALID");
    }
  }
  //Oil Level
  lcd.setCursor(0, 1);
  lcd.print("OIL LEV. ");
  lcd.print(oilLevel);
  lcd.print(" %");

  delay(5000);
  lcd.clear();
}

float calculate_fuel() {
  long duration, distance, filled;
  float percentage;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Calculate Distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" CM");

  filled = tank_height - distance;
  percentage = (filled * 100.0) / tank_height;
  return percentage;
}

void error_handler(char command) {
  lcd.setCursor(0, 0);
  switch (command) {
    case 'w' : {
        lcd.print("  WIFI FAILED! "); //WIFI Connection Failed
        break;
      }
    case 'u': {
        lcd.print(" SENSOR ERROR! "); // Sensor Reading Exception
        break;
      }
  }
}
