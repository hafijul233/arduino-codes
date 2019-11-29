#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

//Wifi Settings
const char *ssid = "Hridoy";
const char *password = "9876543210";
const char *host = "192.168.1.20";

//Server Setting
const char *serverUrl = "http://192.168.1.20/oil/entry_point.php";
String postStr = "";
String apiKey = "TW9oYW1tYWQgSGFmaWp1bCBJc2xhbQ";
//Status Flags
bool wifiStatus = false;

void setup()
{
  Serial.begin(115200);
  //Wifi connection
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  Serial.println("Connecting To Wifi ");
  do {
    if (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("WiFi Connection Failed.");
    } else {
      Serial.println("Wifi Connection Successful.");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());  //IP address assigned to your ESP
      wifiStatus = true;
      break;
    }
    i++;
  } while (i < 5);

  //Check got Any Connection with in 2.5 Sec.
  if (wifiStatus == false) {
    Serial.println("w");
    Serial.flush();
  }
}

void loop()
{
  if (Serial.available() > 0) {
    String data = Serial.readString();
    HTTPClient http;
    postStr = "ol=" + data;
    postStr += "&api=" + apiKey;

    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    //Web Feedback
    int httpCode = http.POST(postStr);
    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);
    http.end();
    delay(5000);
  }
}
