#define echoPin 13 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 12 //attach pin D3 Arduino to pin Trig of HC-SR04

const int IN1 = 7;//LEFT FORWARD
const int IN2 = 6;//LEFT BACKWARD 
const int IN3 = 5;//RIGHT FORWARD
const int IN4 = 4;//RIGHT BACKWARD

const int ENA = 10;
const int ENB = 11;

long duration;
int distance;

char r;
int goForward;
  
void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  goForward = 0;

  Serial.begin(9600);

}

void loop() {
  if (Serial.available()) {
    r = Serial.read();
    Serial.println(r);
  }

  analogWrite(ENA, 150);
  analogWrite(ENB, 150);

  distance = getDistance();

  if(distance <= 15){
    moveStop();
  }

  if(r == '1'){ 
    r = '0';
    moveForward();
    goForward = 1;
  }
  
  else if(r == '2'){ 
     r = '0';
     if(goForward == 1){
      moveStop();
      goForward = 0;
     }else{
      moveBackward();
      goForward = 0;
      delay(500);
      moveStop(); 
     }
  
  }

  else if(r == '4'){ 
    r = '0';
    turnLeft();         
  }

  else if(r == '3'){ 
    r = '0';         
    turnRight();
  }

  else if(r == '5'){     
    moveStop();
  }

  else if(r == '6'){  
    r = '6';   
    enjoy();
  }

}

  void moveForward(){
    Serial.println("moveForward");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN4, LOW);
  }

   void moveBackward(){
    Serial.println("moveBackward");
    digitalWrite(IN2, HIGH);
    digitalWrite(IN4, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN3, LOW);
   }

   void turnLeft(){
    Serial.println("turnLeft");
    digitalWrite(IN2, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(150);
    moveStop();
   }

   void turnRight(){
    Serial.println("turnRight");
    digitalWrite(IN4, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    delay(150);
    moveStop();
   }

   void moveStop(){
    Serial.println("moveStop");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
   }

   int getDistance(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
  
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
//    Serial.println(distance);
    return distance;
  }

  void enjoy(){
    if(distance <= 15){
      moveStop();
      delay(300);
      turnRight();
    }else{
      moveForward();
    }
  }
