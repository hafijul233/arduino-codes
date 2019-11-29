#include <ESP8266WiFi.h>
//WiFi Info
const char* ssid     = "Hridoy";
const char* password = "9876543210";

WiFiServer server(80);
String header;

String light1state = "off";
String light2state = "off";
String fan1state = "off";
String fan2state = "off";

// Assign output variables to GPIO pins
const int light1 = 23;
const int light2 = 22;
const int fan1 = 19;
const int fan2 = 18;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  // Set outputs to HIGH
  digitalWrite(light1, HIGH);
  digitalWrite(light2, HIGH);
  digitalWrite(fan1, HIGH);
  digitalWrite(fan2, HIGH);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("\nIP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            //Light 1 ON
            if (header.indexOf("GET /23/on") >= 0) {
              Serial.println("Light 1 is ON");
              light1state = "on";
              digitalWrite(light1, LOW);
            }
            // Light 1 OFF
            else if (header.indexOf("GET /23/off") >= 0) {
              Serial.println("Light 2 is OFF");
              light1state = "off";
              digitalWrite(light1, HIGH);
            }
            //Light 2 ON
            if (header.indexOf("GET /22/on") >= 0) {
              Serial.println("Light 2 is ON");
              light2state = "on";
              digitalWrite(light2, LOW);
            }
            // Light 2 OFF
            else if (header.indexOf("GET /22/off") >= 0) {
              Serial.println("Light 2 is OFF");
              light2state = "off";
              digitalWrite(light2, HIGH);
            }
            //-------------------------------------------
            //Fan 1 ON
            if (header.indexOf("GET /23/on") >= 0) {
              Serial.println("Fan 1 is ON");
              fan1state = "on";
              digitalWrite(fan1, LOW);
            }
            // Fan 1 OFF
            else if (header.indexOf("GET /23/off") >= 0) {
              Serial.println("Fan 2 is OFF");
              fan1state = "off";
              digitalWrite(fan1, HIGH);
            }

            //Fan 2 ON
            if (header.indexOf("GET /22/on") >= 0) {
              Serial.println("Fan 2 is ON");
              fan2state = "on";
              digitalWrite(fan2, LOW);
            }
            // Fan 2 OFF
            else if (header.indexOf("GET /22/off") >= 0) {
              Serial.println("Fan 2 is OFF");
              fan2state = "off";
              digitalWrite(fan2, HIGH);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html{font-family:Helvetica;display:inline-block;margin:0 auto;text-align:center}.button{background-color:#195b6a;border:none;color:#fff;padding:16px 40px;text-decoration:none;font-size:30px;margin:2px;cursor:pointer}.button2{background-color:#77878a}.button3{background-color:##5cb85c}");
            client.println("</style></head>");
            client.println("<body><h1>Home Automation Server</h1>");

            //light 1
            client.println("<p>Light 1 - State " + light1state + "</p>");
            if (light1state == "off") {
              client.println("<p><a href=\"/23/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/23/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            //light 2
            client.println("<p>Light 2 - State " + light2state + "</p>");
            if (light2state == "off") {
              client.println("<p><a href=\"/22/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/22/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            //light 1
            client.println("<p>Fan 1 - State " + fan1state + "</p>");
            if (fan1state == "off") {
              client.println("<p><a href=\"/19/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/19/off\"><button class=\"button button3\">OFF</button></a></p>");
            }

            //light 1
            client.println("<p>Fan 2 - State " + fan2state + "</p>");
            if (fan2state == "off") {
              client.println("<p><a href=\"/18/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/18/off\"><button class=\"button button3\">OFF</button></a></p>");
            }

            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
