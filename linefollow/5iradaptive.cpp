#include <Arduino.h>

// Motor pins
#define AIN1 7
#define AIN2 8
#define PWMA 5
#define BIN1 10
#define BIN2 9
#define PWMB 6

// IR sensor pins
#define IR1 A1
#define IR2 A2
#define IR3 A3
#define IR4 A4
#define IR5 A5

// Speed control variables
int baseSpeed = 88;
int turnSpeed = 150;
int baseTurnSpeed = 70;
int prev = -1;

int curveBoost = 0;
int curveCount = 0;
int curveDirection = 0; // -1 = left, +1 = right, 0 = straight

int multiplier = 20;

void forward(int leftSpeed, int rightSpeed) {
  // Set left motor direction forward
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, rightSpeed);

  // Set right motor direction forward
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, leftSpeed);
}

void left(){
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH); 
  analogWrite(PWMA, turnSpeed);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, turnSpeed);
}

void right(){
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW); 
  analogWrite(PWMA, turnSpeed);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, turnSpeed);
}

// void pastD(){
//   if(prev == 3){
//     left(); 
//   }else if (prev == 4){
//     right();
//   }else if(prev == 1){
//     forward(turnSpeed+curveBoost, baseTurnSpeed);
//   }else if (prev == 2){
//     forward(baseTurnSpeed, turnSpeed+curveBoost);
//   }else if (prev == 0){
//     forward(baseSpeed, baseSpeed);
//     forward(0,0);
//   }
// }

void setup() {
  Serial.begin(9600);
  // TCCR0B = TCCR0B & B11111000 | B00000010 ;
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  // forward(100, 100);
  
}

void loop() {
  Serial.print("IR1: "); Serial.print(digitalRead(IR1));
  Serial.print(" IR2: "); Serial.print(digitalRead(IR2));
  Serial.print(" IR3: "); Serial.print(digitalRead(IR3));
  Serial.print(" IR4: "); Serial.print(digitalRead(IR4));
  Serial.print(" IR5: "); Serial.println(digitalRead(IR5));
  int s2 = digitalRead(IR2);
  int s4 = digitalRead(IR4);
  int s1 = digitalRead(IR1);
  int s5 = digitalRead(IR5);
  int s3 = digitalRead(IR3);
  
  curveBoost = curveCount * 20;
  curveBoost = constrain(curveBoost, 0, 80);  

  if(curveDirection == 0){
    forward(baseSpeed, baseSpeed);
  }
  else if (curveDirection == -1){
    forward(baseTurnSpeed, turnSpeed+curveBoost); //when only side sensor
  }else if (curveDirection == 1){
    forward(turnSpeed+curveBoost, baseTurnSpeed); //when only side sensor
  }else if(curveDirection == -2){
    forward(baseTurnSpeed, turnSpeed+curveBoost); //when both center and side sensor
  }else if(curveDirection == 2){
    forward(turnSpeed+curveBoost, baseTurnSpeed); //when both center and side sensor
  }else if(curveDirection == -3){
    right();
    // delay(300);
  }else if(curveDirection == 3){
    left();   
    // delay(300);
  } else forward(0,0);  

  if (s1 ==1 && s2 ==1 && s3 ==1 && s4 ==1 && s5 ==1){
    curveDirection = 5;
    curveCount = 0;
  } else if ((s1 ==0) && (s2 ==0) && (s4 ==0) && (s5 ==0) && (s3 == 1)){
    curveDirection = 0;
  } else if((s5 ==1) && (s4 ==1)){
    curveDirection = 3;
    curveCount = 0;
  } else if((s1 ==1) && (s2 ==1)){
    curveDirection = -3;
    curveCount = 0;
  } else if ((s2 ==1) &&  (s4 ==0)){
    curveCount++;
    curveDirection = 1;
    // prev = 0 ;
  } else if ((s4 ==1) &&  (s2 ==0)){
    curveCount++;
    curveDirection = -1;
  }
  else if (s1 == 1) {
    curveCount +=2;
    curveDirection = 2;
  }
  else if (s5 == 1) {
    curveCount +=2;
    curveDirection = -2;
  }
  else {
    curveCount = 0;
    curveDirection = 0;
  }
}