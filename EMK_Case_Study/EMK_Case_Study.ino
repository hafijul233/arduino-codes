#define light 0
#define trigger 4
#define echo 5
#define ldr_sensor A0
#define alert_light 16

float t = 0, dist = 0;
int light_value, light_std = 40, dist_std = 100, alert = 1;

void setup()
{
  Serial.begin(9600);
  
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  
  pinMode(light, OUTPUT);
  pinMode(ldr_sensor, INPUT);
  
  pinMode(alert_light, OUTPUT);
  
  Serial.print("Distance Calculation\n===========================\n");
  digitalWrite(light,LOW);
  digitalWrite(alert_light,LOW);
  
}

void loop() {
  Serial.print("LDR Response: ");
  light_value = analogRead(ldr_sensor);
  Serial.println(light_value);
  if(light_value < light_std) {
    digitalWrite(light,HIGH);
  }
  else if(light_value > light_std) {
    digitalWrite(light,LOW);
  }
  length_meter();
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.print(" CM\n");

  if(dist < dist_std && alert == 1) {
    digitalWrite(alert_light,HIGH);
  }
  else if(dist < dist_std && alert == 0) {
    digitalWrite(alert_light,LOW);
  }
  //delay(1000);
}

void length_meter()
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
