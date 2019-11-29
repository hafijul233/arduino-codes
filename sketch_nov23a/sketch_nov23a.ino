#define fire A0
#define buzz 9 

void setup() {
  Serial.begin(9600);
  pinMode(fire, INPUT);
}

void loop() {
  int value = analogRead(fire);
  if(value > 200) {
    Serial.println("No Person Setting");
  }
  if(value < 200) {
    Serial.println("A Person is Setting");
  }
}
