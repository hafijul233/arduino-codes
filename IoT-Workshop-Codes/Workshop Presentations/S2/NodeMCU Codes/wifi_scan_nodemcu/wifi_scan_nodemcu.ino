#include <ESP8266WiFi.h>

//=======================================================================
//                     SETUP
//=======================================================================
void setup() {
  Serial.begin(115200);
  Serial.println(""); //Remove garbage

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();  //ESP has tendency to store old SSID and PASSword and tries to connect
  delay(100);

  Serial.println("WiFi Netwoek Scan Started");
}

//=======================================================================
//                        LOOP
//=======================================================================
void loop() {
 
  // WiFi.scanNetworks will return the number of networks found
  Serial.println("Started Scanning...");
  int n = WiFi.scanNetworks();
   
  Serial.println("Scanning done");
  
  if (n == 0)
    Serial.println("No Networks Found");
  else
  {
    Serial.print(n);
    Serial.println(" Networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);  //Sr. No
      Serial.print(": ");
      Serial.print(WiFi.SSID(i)); //SSID
      Serial.print("\t(");
      Serial.print(WiFi.RSSI(i)); //Signal Strength
      Serial.print(")\tMAC:");
      Serial.print(WiFi.BSSIDstr(i));
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?"\tUnsecured":"\tSecured");
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before starting New scanning again
  delay(10000);
}
