///Note: Relay are Active Low
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

#define in4 7 //Light 1 working (Green)
#define in3 6 //Light 2 working (Blue)
#define in2 5 //Fan 1 
#define in1 4 //Fan 2

#define tx 11 //Bluetoth Transmitter
#define rx 10 //Bluetoth Receiver

#define fire A0 //Fire Sensor
#define buzz 9 //Buzzer

//Software Serial for Bluetooth
SoftwareSerial bluetooth(rx, tx); // RX,TX
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool ss = true; //system status
bool ba = true; // buzzer status
char c = 's';
void setup() {
  Serial.begin(115200);
  bluetooth.begin(9600);

  pinMode(in4, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(fire, INPUT);
  pinMode(buzz, OUTPUT);

  digitalWrite(in4, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in1, HIGH);
  digitalWrite(fire, HIGH);
  digitalWrite(buzz, LOW);

  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME TO   ");
  lcd.setCursor(0, 1);
  lcd.print("   SMART HOME   ");
  delay(1000);
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("  Notification ");
  lcd.setCursor(0, 1);
  if (bluetooth.available() > 0) {
    char c = bluetooth.read();
    Serial.println(c);
    if (c == 'A' && ss == true) {
      digitalWrite(in4, LOW);
      Serial.println("Light 1 is ON");
      lcd.print("  LIGHT 1 is ON");
    }
    else if (c == 'a' && ss == true) {
      digitalWrite(in4, HIGH);
      Serial.println("Light 1 is OFF");
      lcd.print("  LIGHT 1 is OFF");
    }
    else if (c == 'B' && ss == true) {
      digitalWrite(in3, LOW);
      Serial.println("Light 2 is ON");
      lcd.print("  LIGHT 2 is ON ");
    }
    else if (c == 'b' && ss == true) {
      digitalWrite(in3, HIGH);
      Serial.println("Light 2 is OFF");
      lcd.print("  LIGHT 2 is OFF");
    }
    else if (c == 'C' && ss == true) {
      digitalWrite(in2, LOW);
      Serial.println("Fan 1 is ON");
      lcd.print("  FAN 1 is ON");
    }
    else if (c == 'c' && ss == true) {
      digitalWrite(in2, HIGH);
      Serial.println("Fan 1 is OFF");
      lcd.print("  FAN 1 is OFF");
    }
    else if (c == 'D' && ss == true) {
      digitalWrite(in1, LOW);
      Serial.println("Fan 2 is ON");
      lcd.print("  FAN 2 is ON");
    }
    else if (c == 'd' && ss == true) {
      digitalWrite(in1, HIGH);
      Serial.println("Fan 2 is OFF");
      lcd.print("  FAN 2 is OFF");
    }
    else if (c == 's' && ss == true) {
      digitalWrite(in4, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in2, HIGH);
      digitalWrite(in1, HIGH);
      Serial.println("System is Power Off");
      lcd.print("   System OFF");
      ss = false;
    }
    else if (c == 'S' && ss == false) {
      lcd.print("   System ON");
      ss = true;
    }
    else if (c == 'W' && ba == false) {
      Serial.println("Buzzer Alert ON");
      lcd.print("   Alert ON");
      ba = true;
    }
    else if (c == 'w' && ba == true) {
      Serial.println("Buzzer Alert OFF");
      lcd.print("   Alert OFF");
      ba = false;
    }

    delay(1000);
    lcd.clear();
  }
  fireAlert();
}

void fireAlert() {
  Serial.println(analogRead(fire));
  if (analogRead(fire) < 50 && ba == true) {
    lcd.print("   Fire Alarm ");
    digitalWrite(in4, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in2, HIGH);
    digitalWrite(in1, HIGH);
    digitalWrite(buzz, HIGH);
    delay(1000);
    digitalWrite(buzz, LOW);
    delay(500);
    lcd.clear();
  }
}
