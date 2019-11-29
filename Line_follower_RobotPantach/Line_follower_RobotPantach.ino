#define ena 6
#define enb 3

const int MotR_A = 2; // DC Motor1 Pole_A
const int MotR_B = 4; // DC Motor1 Pole_B
const int MotL_A = 5; // DC Motor2 Pole_A
const int MotL_B = 7; // DC Motor2 Pole_B

unsigned int sense[5]={0};

void setup(){
Serial.begin(9600);

//Motor DriverDeclearation
pinMode(ena, OUTPUT);
pinMode(enb, OUTPUT);
pinMode(MotR_A, OUTPUT);
pinMode(MotR_B, OUTPUT);
pinMode(MotL_A, OUTPUT);
pinMode(MotL_B, OUTPUT);

//IR Array 
pinMode(8,INPUT);
pinMode(9,INPUT);
pinMode(10,INPUT);
pinMode(11,INPUT);
pinMode(12,INPUT);

//Initialize Motor 
analogWrite(ena,127);
analogWrite(enb,127);

}
void loop(){
  
sense[0] = digitalRead(8);
sense[1] = digitalRead(9);
sense[2] = digitalRead(10);
sense[3] = digitalRead(11);
sense[4] = digitalRead(12);

for(int i=0; i<5;i++){
  Serial.print(sense[i]);
  Serial.print(" |");
}
Serial.println();

  if(sense[0] == 1 || sense[1] == 1){
    Robo_Right();
  }
  else if(sense[3] == 1 || sense[4] == 1){
    Robo_Left();
  }
  else if(sense[0] == 1 && sense[1] == 1 && sense[2] == 1 && sense[3] == 1 && sense[4] == 1){
    Robo_Stop();
  }
  else{
    Robo_Front();
  }
  delay(100);
}
void Robo_Front(){
  Serial.print("Front");
digitalWrite(MotR_A, LOW);
digitalWrite(MotR_B, HIGH);
digitalWrite(MotL_B, LOW);
digitalWrite(MotL_A, HIGH);
}

void Robo_Right(){
  Serial.print("Right Right");
digitalWrite(MotR_A, HIGH);
digitalWrite(MotR_B, LOW);
digitalWrite(MotL_B, LOW);
digitalWrite(MotL_A, HIGH);
}
void Robo_Left(){
Serial.print("Right Left");
digitalWrite(MotR_A, LOW);
digitalWrite(MotR_B, HIGH);
digitalWrite(MotL_B, HIGH);
digitalWrite(MotL_A, LOW);
}
void Robo_Stop(){
Serial.print("Stop");
digitalWrite(ena,LOW);
digitalWrite(enb,LOW);
}

