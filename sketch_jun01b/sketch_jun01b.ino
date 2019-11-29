#define waste_trigger A4
#define waste_echo A5

float waste, duration;

void setup() {
    Serial.begin(9600);
    pinMode(waste_trigger, OUTPUT);
    pinMode(waste_echo, INPUT);
}

void loop() {
  digitalWrite(waste_trigger, LOW);
    delayMicroseconds(2);
  digitalWrite(waste_trigger, HIGH);
    delayMicroseconds(10);
  digitalWrite(waste_trigger, LOW);
  duration = pulseIn(waste_echo,HIGH);
  
  waste = duration*0.034/2;
  Serial.print(waste);
  Serial.println(" CM");
delay(1000);
}
