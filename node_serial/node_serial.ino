#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#define PASS 4 //D2
#define FAIL 5 //D1

/** WIFI Configuration **/
const char *ssid = "Hridoy";
const char *password = "9876543210";
const char *host = "192.168.0.100";
String card = "";

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  pinMode(PASS, OUTPUT);
  pinMode(FAIL, OUTPUT);
  digitalWrite(PASS,LOW);
  digitalWrite(FAIL, LOW);
  
  //Activate WiFi
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("Connecting");
  
  //Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP  
}

void loop() { // run over and over
  if (Serial.available()) 
  {
    card = Serial.readString();
    
    HTTPClient http;
    String postData;
    //Post Data
    postData = "rfid=" + card;
    http.begin("http://192.168.0.100/sss/attendance_api.php");          //Specify request destination
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header

    int httpCode = http.POST(postData);   //Send the request
    String payload = http.getString();    //Get the response payload

    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload

    http.end();  //Close connection
  }
}
