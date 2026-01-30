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
int leftSpeed = 0;
int rightSpeed = 0;
int defaultSpeed = 130;
int turnspeed = 180;
int past = 0;

void forward(int leftSpeed, int rightSpeed) {
  // Set left motor direction forward
  if (leftSpeed < 0) {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    analogWrite(PWMB, -leftSpeed);
  }else{
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    analogWrite(PWMB, leftSpeed);
  }
  if (rightSpeed < 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, -rightSpeed);
  }else{
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, rightSpeed);}

}

void setup() {
  Serial.begin(9600);
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
}

void pastD(){ // 0 straight 1 is right 2 is left
  if (past == 0){
    forward(defaultSpeed, defaultSpeed); 
    leftSpeed = 0;
    rightSpeed = 0;
  }else if (past == 1){
    leftSpeed = -turnspeed;
    rightSpeed = turnspeed;
    forward(leftSpeed, rightSpeed);
  }else if (past == 2){
    leftSpeed = turnspeed;  
    rightSpeed = -turnspeed;  
    forward(leftSpeed, rightSpeed);
  }
}

void loop() {
  // Serial.print("IR1: "); Serial.print(digitalRead(IR1));
  Serial.print(" IR2: "); Serial.print(digitalRead(IR2));
  Serial.print(" IR3: "); Serial.print(digitalRead(IR3));
  Serial.print(" IR4: "); Serial.print(digitalRead(IR4));
  // Serial.print(" IR5: "); Serial.print(digitalRead(IR5));
  Serial.print(" lSpeed: "); Serial.print(leftSpeed);
  Serial.print(" rSpeed: "); Serial.println(rightSpeed);

  // int s1 = digitalRead(IR1);
  int s2 = digitalRead(IR2);
  int s3 = digitalRead(IR3);
  int s4 = digitalRead(IR4);
  // int s5 = digitalRead(IR5);

  if ( s2 ==1 && s4 ==1 && s3 ==0) {
    pastD();
  }
  else if (s2 == 1 && s3 ==1) {
    leftSpeed = turnspeed;
    rightSpeed = -turnspeed;
    forward(leftSpeed, rightSpeed);
    past = 1;
    delay(130);
  }
  else if( s4 == 1 && s3 ==1) {
    leftSpeed = -turnspeed;
    rightSpeed = turnspeed;
    forward(leftSpeed, rightSpeed);
    past = 2;
    delay(130);
  }
  else if (s3 == 1) {
    forward(defaultSpeed, defaultSpeed);
    leftSpeed = 0;
    rightSpeed = 0;
    past = 0;
  }
  else if (s4 == 1) {
    leftSpeed = -turnspeed;
    rightSpeed = turnspeed;
    forward(leftSpeed, rightSpeed);
    past = 1;
  }else if (s2 == 1) {
    leftSpeed = turnspeed;
    rightSpeed = -turnspeed;
    forward(leftSpeed, rightSpeed);
    past = 2;
  }
}