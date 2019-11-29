#define 51 A0   //Trigger Front Sensor 
#define 52 A1   //Echo Front Sensor

#define 53 A2   //Trigger Top Sensor 
#define 54 A3   //Echo Top Sensor

int door state = 0// 0== closed 1==opend
float max_depth = 28, percentage, waste_level;

void setup() {
  Serial.begin(9600);
  
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(2,INPUT);
  Serial.println("Hafijul Islam");
}

void loop(){
  int basket_presence,nearby_distance, waste_level;
   
  basket_presence = digitalRead(2);
  
  if(basket_presence == 1){
    nearby_distance = depth(51,52);
    waste_level = depth(51,52);
    
    if(waste_level <= 21){
      Serial.print("Waste Level: ");
      Serial.print(waste_level);
      Serial.println("%");
    }
    else{
      Serial.println("Waste Bin is Full");
    }

    if(nearby_distance < 30){
      Serial.println("Door Opening");
      door_state = 1;
    }
    else{
      if(){
        
      }
      else{
        
      }
    }
    
  }
  
  else{
    Serial.println("There is No Basket");
  } 
  delay(600);
}

float depth(int trigger, int echo) {
  
  float duration, height;
  
  digitalWrite(trigger, LOW);
 delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  duration = pulseIn(echo,HIGH);
  
  height = duration*0.034/2;

  return height;
}
