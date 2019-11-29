void setup() {
  Serial.begin(9600);
  pinMode(3,INPUT);

}

void loop() {

  if(digitalRead(3) == HIGH){
    Serial.println("1");
  }
  if(digitalRead(3) == LOW){
    Serial.println("0");
  }
  delay(500);
}
