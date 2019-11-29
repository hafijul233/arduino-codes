#define gaspin A0

int temp = 0;
float tempC = 0.0;

void setup() {
  Serial.begin(9600);
//  analogReference(INTERNAL);
}

void loop() {
  Serial.print("Tempareture Value: ");
//  analogReference(INTERNAL);
  temp = analogRead(gaspin);
  //tempC = ((temp/1024)*5000)/10;  
  Serial.println(temp);

  delay(1000);
}
