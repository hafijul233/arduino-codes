#define enA 9
#define in1 7
#define in2 6

#define enB 3
#define in3 5
#define in4 4

int motorSpeedA = 0;
int motorSpeedB = 0;

void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.println("Program Start");

    digitalWrite(enA, HIGH);
    digitalWrite(enB, HIGH);
    
}

void loop() {
  forward();
  delay(1000);
  reverse();
 }

 void forward(){
 digitalWrite(in1, LOW);
 digitalWrite(in2,HIGH);
 digitalWrite(in3, LOW);
 digitalWrite(in4,LOW);
 Serial.println("FORWARD");
 delay(1000);
 }

 void reverse(){
 digitalWrite(in1, HIGH);
 digitalWrite(in2,LOW);
 digitalWrite(in3, HIGH);
 digitalWrite(in4,LOW);
 Serial.println("REVERSE");
 delay(1000);
 }

