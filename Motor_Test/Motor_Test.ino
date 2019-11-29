void setup() {
  Serial.begin(9600);

   pinMode(7,OUTPUT);
   pinMode(8,OUTPUT);
   pinMode(9,OUTPUT);
   
   digitalWrite(7,HIGH);   


}

void loop() {
  if(Serial.available()>0){
    char state  = Serial.read();

    if(state == '1'){
      digitalWrite(6,HIGH);
      digitalWrite(5,LOW);
      Serial.println("ON");
    }
    
    else if(state == '0'){
      digitalWrite(6,LOW);
      digitalWrite(5,LOW);
      Serial.println("OFF");
    }
    else{
      digitalWrite(6,HIGH);
      digitalWrite(5,LOW);
      Serial.println("ON");
    }
  }
  delay(1000);
}
