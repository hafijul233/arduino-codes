int irSensors[] = {14, 15, 16, 17, 18}; //IR sensor pins
int irReadings[5];

void setup() 
{
  Serial.begin(9600); //debug console

  //Declare all IR sensors as inputs
  for (int pin = 0; pin < 5; pin++) {
    pinMode(irSensors[pin], INPUT);
  }
}

void loop() 
{
    //Read the IR sensors and put the readings in irReadings array
  for (int pin = 0; pin < 5; pin++) {
    irReadings[pin] = digitalRead(irSensors[pin]);
  }

   for(int pin = 0; pin < 5; pin++) {
    Serial.print("[");
    Serial.print(pin);
    Serial.print("] -> ");
    Serial.print(irReadings[pin]);  
    Serial.print(" | ");
   }
   Serial.println();
   delay(1000);
}
