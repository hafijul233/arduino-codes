#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Losant.h>

// WiFi credentials.
const char* WIFI_SSID = "EMK-MAKERLAB";
const char* WIFI_PASS = "emkmakerpatrons";

// Losant credentials.
const char* LOSANT_DEVICE_ID = "5c694c4a8f3e0c0009458509";
const char* LOSANT_ACCESS_KEY = "c12a0cf1-f5d8-4795-978c-a4fd6e451810";
const char* LOSANT_ACCESS_SECRET = "9b2cdf01740d4bc55f56e6265af6267948f0b4ca2f2f3191215400169ac6ec02";

// Create WiFi Client
WiFiClientSecure wifiClient;

//Create Losant Instance
LosantDevice device(LOSANT_DEVICE_ID);

void connect_cloud()
{
  // Connect to the wifi
  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Waiting for WiFi: ");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // WiFi Connection Done


  // Now connect to Losant MQTT Broker

  // Authenticate the device
  Serial.print("Authenticating Device...");
  HTTPClient http;
  http.begin("http://api.losant.com/auth/device");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Accept", "application/json");

  // Create a Json Payload
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["deviceId"] = LOSANT_DEVICE_ID;
  root["key"] = LOSANT_ACCESS_KEY;
  root["secret"] = LOSANT_ACCESS_SECRET;
  String buffer;
  root.printTo(buffer);
  int httpCode = http.POST(buffer);

  switch(httpCode)
  {
    case HTTP_CODE_OK: Serial.println("This device is authorized!"); break;
    case 400: Serial.println("ID, access key, or access secret in wrong format."); break;
    case 401: Serial.println("Invalid credentials to Losant"); break;
    default : Serial.println("Unknown response from API");
  }
  http.end();
  // Autorization Done


  // Now complete connection to Losant
  Serial.println("Connecting to Losant: ");
  device.connectSecure(wifiClient, LOSANT_ACCESS_KEY, LOSANT_ACCESS_SECRET);
  while(!device.connected()) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Successfully Connected to Losant!");
}


// Now create a function to publish Data
void publish_data(double tempC, double humidity, double realfeel)
{
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["temperature"] = tempC;
  root["humidity"] = humidity;
  root["realfeel"] = realfeel;
  device.sendState(root);
  Serial.println("Data has been published!");
}

void setup() 
{
  Serial.begin(115200);
  connect_cloud();
}

void loop() 
{
  if ((!device.connected()) || (WiFi.status() != WL_CONNECTED)) connect_cloud();

  else publish_data(20,50,25);

  delay(5000);
}
