#include <SPI.h>
#include <Ethernet.h>
#include <LiquidCrystal_I2C.h>

// defines pins numbers
const int trigPin = 14; //A0
const int echoPin = 15; //A1

// defines variables
int max_height = 22;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// use the numeric IP instead of the name for the server:
//IPAddress server(192, 168, 1, 23); // numeric IP for Google (no DNS)
// if you don't want to use DNS (and reduce your sketch size)
char server[] = "www.google.com";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
//IPAddress ip(192, 168, 1, 177); //IP Address
//IPAddress myDns(192, 168, 1, 1); //Default Gateway

// Initialize the Ethernet client library
EthernetClient client;
LiquidCrystal_I2C lcd(0x27, 20, 4);
// Variables to measure the speed

unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;

bool printWebData = true;  // set to false for better speed measurement

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  lcd.init();
  lcd.backlight();

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  beginMicros = micros();
  //LCD initialization
  lcd.setCursor(0, 0);
  lcd.print("  Initializing  ");
  lcd.setCursor(0, 1);
  lcd.print("IoT Fuel Monitor");
  delay(1000);
  lcd.clear();
}

void loop() {
  // if there are incoming bytes available
  //LCD print
  lcd.setCursor(3, 0);
  lcd.print("Fuel Indicator");
  lcd.setCursor(0, 1);
  lcd.print("Fuel Status: ");

  int percent = calculate_fuel();

  if (percent >= 0 && percent <= 100) {
    if (percent < 2) {
      lcd.print("EMPTY");
      lcd.setCursor(1, 3);
      lcd.print("!! TURN POWER OFF !!");

    } else if (percent >= 2 && percent < 25) {
      lcd.print("LOW");
      lcd.setCursor(1, 3);
      lcd.print("!!PLEASE REFILL!!");

    } else if (percent >= 25 && percent < 75) {
      lcd.print("MEDIUM");
      lcd.setCursor(1, 3);
      lcd.print("!!FUEL EFFICIENT!!");

    } else if (percent >= 75 && percent <= 100) {
      lcd.print("FULL");
      lcd.setCursor(1, 3);
      lcd.print("!!FUEL FILLED!!");
    }

    lcd.setCursor(2, 2);
    lcd.print("Percentage: ");
    lcd.print(percent);
    lcd.print("%");

  } else {
    lcd.print("INVALID");
    lcd.setCursor(1, 3);
    lcd.print("!! CHECK SYSTEM !!");
  }

  delay(1000);
  lcd.clear();
  // from the server, read them and print them:
  int len = client.available();
  if (len > 0) {
    byte buffer[80];
    if (len > 80) len = 80;
    client.read(buffer, len);
    if (printWebData) {
      Serial.write(buffer, len); // show in the serial monitor (slows some boards)
    }
    byteCount = byteCount + len;
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    endMicros = micros();
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    Serial.print("Received ");
    Serial.print(byteCount);
    Serial.print(" bytes in ");
    float seconds = (float)(endMicros - beginMicros) / 1000000.0;
    Serial.print(seconds, 4);
    float rate = (float)byteCount / seconds / 1000.0;
    Serial.print(", rate = ");
    Serial.print(rate);
    Serial.print(" kbytes/second");
    Serial.println();

    // do nothing forevermore:
    while (true) {
      delay(1);
    }
  }
}

int percentage(int dist)
{
  int filled = max_height - dist;
  int percent = (filled * 100) / max_height;

  return percent;
}

int calculate_fuel()
{
  long duration;
  int distance;

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;

  return percentage(distance);
}
