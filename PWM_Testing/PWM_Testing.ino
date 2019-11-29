
//int brightness = 0;

void setup() {
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i <= 255; i += 10) {
    analogWrite(9, i);
    float percentage = (i * 100) / 255;
    Serial.print(percentage);
    Serial.println("");
    delay(100);
  }
  for (int i = 255; i >= 0; i -= 10) {
    analogWrite(9, i);
    float percentage = (i * 100) / 255;
    Serial.print(percentage);
    Serial.println("");
    delay(100);
  }

}
