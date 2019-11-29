    /*
       Arduino Robot Car Wireless Control using the HC-05 Bluetooth
       
                    == MASTER DEVICE - Joystick ==
                       
       by Dejan Nedelkovski, www.HowToMechatronics.com
    */
    int xAxis, yAxis;
    void setup() {
      Serial.begin(38400); // Default communication rate of the Bluetooth module
      pinMode(A0,INPUT);
      pinMode(A1,INPUT);
      
    }
    void loop() {
      xAxis = analogRead(A0); // Read Joysticks X-axis
      yAxis = analogRead(A1); // Read Joysticks Y-axis
      Serial.print("X = ");
      Serial.print(xAxis/4); // Dividing by 4 for converting from 0 - 1023 to 0 - 256, (1 byte) range
      Serial.print("| Y = ");
      Serial.println(yAxis/4);
      // Send the values via the serial port to the slave HC-05 Bluetooth device
      Serial.write(xAxis/4); // Dividing by 4 for converting from 0 - 1023 to 0 - 256, (1 byte) range
      Serial.write(yAxis/4);
      delay(1000);
    }
