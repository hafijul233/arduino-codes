int value = 0;
void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
}

void loop() {

  value = analogRead(A0);
  Serial.println(value);
  delay(1000);
}
