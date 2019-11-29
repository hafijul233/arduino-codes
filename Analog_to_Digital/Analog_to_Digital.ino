#define EmptySense A1
#define FullSense A0

int empty, full;

void setup() {
  Serial.begin(9600);
  
  pinMode(EmptySense, INPUT);
  pinMode(FullSense, INPUT);

  Serial.println("Analog Lequid Indicator");

}

void loop() {

    int empty = analogRead(EmptySense);
    int full = analogRead(FullSense);

    Serial.print("Lower Level Value: ");
    Serial.println(empty);
    
    Serial.print("Higher Level Value: ");
    Serial.println(full);
        
  delay(1000);

}
