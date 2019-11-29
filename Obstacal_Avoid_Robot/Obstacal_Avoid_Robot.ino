#define ena 6
#define enb 3

#define in1 7
#define in2 5
#define in3 4
#define in4 2

#define trig A1
#define echo A0

void setup() {
  Serial.begin(9600);
  pinMode(in4,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(in1,OUTPUT);
  
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

  analogWrite(ena,255);
  analogWrite(enb,255);
  
}

void loop() {
  int distance;
  distance = dist_calc();
  
    if(distance < 10){
      right();
    }
    else{
      forward();
    }

  delay(100);
}

int dist_calc(){
  int duration, distance;
  digitalWrite(trig, LOW);
 delayMicroseconds(2);
  digitalWrite(trig, HIGH);
    delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  duration = pulseIn(echo,HIGH);
  
  distance = duration*0.034/2;
  Serial.println(distance);
  return distance;
}

void forward(){

  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("FORWARD");
}

void right(){

  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  Serial.println("RIGHT FORWARD");
}

void left(){

  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("LEFT FORWARD");
}

