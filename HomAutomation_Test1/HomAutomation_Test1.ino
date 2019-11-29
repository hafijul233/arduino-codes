#define light1 A4
#define light2 A5

const int sensorIn = A0;
int mVperAmp = 100; // use 100 for 20A Module and 66 for 30A Module

double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

void setup() 
{
  Serial.begin(9600);  
  pinMode(light1,OUTPUT);
  pinMode(light2,OUTPUT);
  pinMode(sensorIn,INPUT);

}

void loop() 
{
  Serial.print("Power: ");
  Serial.print(getPower());
  Serial.println("W");
  if(Serial.available()>0){
    char c = Serial.read();
    switch(c)
    {
      case 'A': digitalWrite(light1, LOW);
                Serial.println("Light1 is ON");
        break;
        
      case 'a': digitalWrite(light1, HIGH);
                Serial.println("Light1 is OFF");
        break;

      case 'B': digitalWrite(light2, LOW);
                Serial.println("Light2 is ON");
        break;
        
      case 'b': digitalWrite(light2, HIGH);
                Serial.println("Light2 is OFF");
        break; 
    }
  }
}


float getPower()
{
  float result; 
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;

   VRMS = (result/2.0) *0.707; 
  AmpsRMS = (VRMS * 1000)/mVperAmp;
      return (AmpsRMS*220.0)/10;
 }
