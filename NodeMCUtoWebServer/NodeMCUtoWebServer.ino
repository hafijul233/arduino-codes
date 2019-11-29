#include <ESP8266WiFi.h>

const char* hostGet = "iot.travelhostbd.com"; //NOT google.com/nothing/after/the/dotcom.html only google.com

String receiveDatafromArd;
void setup() {
    Serial.begin(115200);
}

void loop() {
  if(Serial.available()){
    receiveDatafromArd = Serial.readString();
    Serial.println(receiveDatafromArd);
    postData();
  }
}

void postData() {

   WiFiClient clientGet;
   const int httpGetPort = 80;

   //the path and file to send the data to:
   String urlGet = "/pages/operation/powerDataInsertProcess.php";
  // We now create and add parameters: 
  urlGet += "?data=" + receiveDatafromArd;
   
      Serial.print(">>> Connecting to host: ");
      Serial.println(hostGet);
      
       if (!clientGet.connect(hostGet, httpGetPort)) {
        Serial.print("Connection failed: ");
        Serial.print(hostGet);
      } 
      else {
          clientGet.println("GET " + urlGet + " HTTP/1.1");
          clientGet.print("Host: ");
          clientGet.println(hostGet);
          clientGet.println("User-Agent: ESP8266/1.0");
          clientGet.println("Connection: close\r\n\r\n");
          
          unsigned long timeoutP = millis();
          while (clientGet.available() == 0) {
            
            if (millis() - timeoutP > 10000) {
              Serial.print(">>> Client Timeout: ");
              Serial.println(hostGet);
              clientGet.stop();
              return;
            }
          }
          //just checks the 1st line of the server response. Could be expanded if needed.
          while(clientGet.available()){
            String retLine = clientGet.readStringUntil('\r');
            Serial.println(retLine);
            break; 
          }
      } //end client connection if else             
      Serial.print(">>> Closing host: ");
      Serial.println(hostGet);          
     clientGet.stop();
}
