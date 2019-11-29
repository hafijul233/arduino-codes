  #include <LiquidCrystal.h>
  #include <SoftwareSerial.h>
  
  //Ultrasonce Sensor Pinout
  #define trigger A0
  #define echo A1
  
  //Analog Sensor Pinout
  #define analogempty A2
  #define analogfull  A3
  
  //GSM Module Pinout
  #define SIM800_TX_PIN 5
  #define SIM800_RX_PIN 6
  
  
  //Relay Pinout
  #define relayPin 3
  
  //Setup a LcdConnection
  const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  
  //Setup a GSM Connection
  SoftwareSerial serialSIM800(SIM800_TX_PIN, SIM800_RX_PIN);
  
  const float max_height = 20;//Tank Max Heighth
  
  float duration=0, distance=0, water_level=0, percentage=0;
  
  char text[25] = "Liquid Level Indicator";
  
  int emptyconfirm = 0;

  int fullconfirm = 0;

  void setup() {
  
    pinMode(trigger,OUTPUT);
    pinMode(echo,INPUT);
  
    pinMode(analogempty,INPUT);
    pinMode(analogfull,INPUT);
    pinMode(relayPin,OUTPUT);

    Serial.begin(9600);
    while(!Serial);
     
    //Being serial communication with Arduino and SIM800
    serialSIM800.begin(9600);
    	delay(1000);
    Serial.println("Setup Complete!");
  
    //Lcd Output
    lcd.begin(16,2);
       lcd.setCursor(0,0);
    lcd.print("   WELCOME TO   ");
       lcd.setCursor(1,0);
       lcd.autoscroll();
    for (int i = 0; i < 24; i++) {
      lcd.print(text[i]);
    }
      delay(1000);
      
    lcd.noAutoscroll();
    lcd.clear();
  }
  
  void loop() {
    lcd.setCursor(0,0);
  
    //Calculate Liquid depth
  	digitalWrite(trigger, LOW);
      	delayMicroseconds(2);
    	digitalWrite(trigger, HIGH);
     		delayMicroseconds(10);
    	digitalWrite(trigger, LOW);
    
    		duration = pulseIn(echo,HIGH);

    		distance = duration*0.034/2;

    		water_level = max_height - distance;
  
    		percentage = (water_level*100)/max_height;   
    
      
    lcd.print(" Filled: ");//first row Output : Filled: 45.0%
    lcd.print(percentage);
    lcd.println("%");
      
    lcd.setCursor(1,0); //second row Output Conditional
  
    if(percentage <= 3.00)
    {
      Serial.print(percentage);
      lcd.print("Tank is EMPTY"); //Empty Output
      Serial.println("Tank is Empty");
      //moto On
      digitalWrite(relayPin,HIGH);
      //Send SMS
      EmptySmsAlert();
      emptyconfirm = 1;
    }
    
    else if(percentage > 3.00 && percentage <= 80.00)
    {
      Serial.print(percentage);
      lcd.print("Efficient Liquid"); //Avg Output
      Serial.println("Efficient Liquid");
      
    }
    
    else
    {
      Serial.print(percentage);
      lcd.print("Tank is FULL ");// full Output
      Serial.println("Tank is FULL ");
      //moto On
      digitalWrite(relayPin,LOW);
      //Send SMS
      FullSmsAlert();
      fullconfirm = 1;
    }
    
    delay(1000);
  
    lcd.clear();
  }
  

  
  void EmptySmsAlert(){
  if(emptyconfirm == 0){
    Serial.println("Sending SMS...");
     
    //Set SMS format to ASCII
    serialSIM800.write("AT+CMGF=1\r\n");
    delay(1000);
   
    //Send new SMS command and message number
    serialSIM800.write("AT+CMGS=\"01710534092\"\r\n");
    delay(1000);
     
    //Send SMS content
    serialSIM800.write("Container is EMPTY");
    delay(1000);
     
    //Send Ctrl+Z / ESC to denote SMS message is complete
    serialSIM800.write((char)26);
    delay(1000);
       
    Serial.println("SMS Sent!");
    fullconfirm = 0;
  }
  
  }

    void FullSmsAlert()
    {
      if(fullconfirm == 0){
    Serial.println("Sending SMS...");
     
    //Set SMS format to ASCII
    serialSIM800.write("AT+CMGF=1\r\n");
    delay(1000);
   
    //Send new SMS command and message number
    serialSIM800.write("AT+CMGS=\"01710534092\"\r\n");
    delay(1000);
     
    //Send SMS content
    serialSIM800.write("Container is FULL");
    delay(1000);
     
    //Send Ctrl+Z / ESC to denote SMS message is complete
    serialSIM800.write((char)26);
    delay(1000);
       
    Serial.println("SMS Sent!");
    emptyconfirm = 0;
      }
  }
