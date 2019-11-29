#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define D2 4
#define D1 5
#define DHTPIN 0
#define DHTTYPE DHT22

int autoPump = 1;
int pumpStatus = 0;

LiquidCrystal_I2C lcd(0x3F, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  //Use predefined PINS consts
  Wire.begin(D2, D1);
  Serial.println(F("DHTxx test!"));
  dht.begin();

  lcd.begin();
  lcd.home();
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME TO");
  lcd.setCursor(0, 1);
  lcd.print("   Smart Farm");
  Serial.println("Status\tHumidity (%)\tTemperature (C)\tHeatIndex (C)");
  delay(1000);
  lcd.clear();
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("Pump : ");

  //currently pump status
  if (pumpStatus == 1)
    lcd.print(" ON ");
  else
    lcd.print(" OFF ");

  //manual override status
  if (autoPump == 1)
    lcd.print(" A");
  else
    lcd.print(" M");

  lcd.setCursor(0, 1);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float hic = dht.computeHeatIndex(t, h, false);
  int m = analogRead(A0);
  m = constrain(m, 400, 1023); // Keep the ranges!
  m = map(m, 400, 1023, 100, 0); // Map m : 400 will be 100 and 1023 will be 0

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    lcd.println("Failed to read");
    return;
  }
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("Humid: ");
  lcd.print(h);
  lcd.print(" %");
  delay(1000);

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("Temp.: ");
  lcd.print(t);
  lcd.print(" C");
  delay(1000);

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("HeatInd: ");
  lcd.print(hic);
  lcd.print(" C");
  delay(1000);

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("Moistur: ");
  lcd.print(m);
  lcd.print(" %");

  delay(1000);
}
