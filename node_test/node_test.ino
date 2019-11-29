#define ldr_sensor A0
#define trigger 4
#define echo 5
#define led 16

float t = 0, dist = 0;

void setup()
{
  Serial.begin(9600);
  
  pinMode(ldr_sensor, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led, OUTPUT);

  digitalWrite(led,LOW);
}

void loop() {
  Serial.print("LDR Response: ");
  Serial.println(analogRead(A0));
  dist_meter();
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.print(" CM\n");
  delay(1000);
}

void dist_meter()
{
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  t = pulseIn(echo, HIGH);
  dist = t * 340 / 20000; //CM
}
