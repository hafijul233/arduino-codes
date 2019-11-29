#define in1 0
#define in2 4
#define in3 5
#define in4 16

void setup()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

}

void loop() 
{
  digitalWrite(in1, HIGH);
  delay(10000);
  
  digitalWrite(in1, LOW);
  delay(1000);
  
  /*digitalWrite(in2, HIGH);
  delay(1000);
  digitalWrite(in2, LOW);
  delay(1000);
  
  digitalWrite(in3, HIGH);
  delay(1000);
  digitalWrite(in3, LOW);
  delay(1000);
  
  digitalWrite(in4, HIGH);
  delay(1000);
  digitalWrite(in4, LOW);
  delay(1000);
  */
}
