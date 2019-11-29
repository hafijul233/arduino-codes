/*
* Create a WiFi access point and provide a web server on it.
* Connect Desktop, Laptop, Mobile Has Wifi Enable to Wifi Named "Free Wifi No Internet"
* Then go to browser type http://local_IP to visit web page and Output Message
*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Free Wifi No Internet"; // HotSpot WIFI SSID  NAME
const char* password = "123456789"; //HotSpot WIFI PASSWORD

//Address Configuare to Visit
IPAddress local_IP(192,168,4,22); //the address whher you can get the web server 
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected to NodeMCU</h1>");
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
  
}

void loop() {
  server.handleClient();
}
