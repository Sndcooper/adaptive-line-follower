#include <Arduino.h>

#define AIN1 7
#define AIN2 8
#define PWMA 5
#define BIN1 10
#define BIN2 9
#define PWMB 6

// IR sensor pins
#define IR2 A2
#define IR3 A3
#define IR4 A4

int s1, s2, s3, s4, s5;

// Speed control variables
int defaultSpeed = 150;
int sharpspeed = 200;
int avoidSpeed = -200;
// int curveSpeed = -80;
// int turnspeed = 140;
// int baseTurnSpeed = 60;
int past = 0;
int ppast = 0;

int standardDelay = 50;
int extremeDelay = 50;

// void stopMotors() {
//   analogWrite(PWMA, 0);
//   analogWrite(PWMB, 0);
//   digitalWrite(AIN1, LOW);
//   digitalWrite(AIN2, LOW);
//   digitalWrite(BIN1, LOW);  
//   digitalWrite(BIN2, LOW);
//   delay(10);
// }

void forward(int leftSpeed, int rightSpeed) {
  
  Serial.print(" leftSpeed: "); Serial.print(leftSpeed);
  Serial.print(" rightSpeed: "); Serial.println(rightSpeed);
  // Set left motor direction forward
  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);
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

void show(){
  s2 = digitalRead(IR2);
  s3 = digitalRead(IR3);
  s4 = digitalRead(IR4);
  Serial.print(" IR1: "); Serial.print(s2);
  Serial.print(" IR2: "); Serial.print(s3);
  Serial.print(" IR3: "); Serial.print(s4);
  Serial.print(" Past: "); Serial.print(past);
}

void pastD(){
  if(past == 0){
    forward(defaultSpeed, defaultSpeed);
    delay(standardDelay);
  } else if (past == 1){
    forward(sharpspeed, avoidSpeed); // Turn right
    // delay(standardDelay);
  } else if (past == -1){
    forward(avoidSpeed, sharpspeed); // Turn left
    // delay(standardDelay);
  } else if (past == 2){
    forward(sharpspeed, avoidSpeed); // Turn right
    // delay(standardDelay);
  } else if (past == -2){
    forward(avoidSpeed, sharpspeed); // Turn left
    // delay(standardDelay);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
}

void loop() {
  show();
  if(s2 && !s3 && !s4){
    forward(sharpspeed, avoidSpeed);
    delay(standardDelay);
    past = 1;
  }
  if(s4 && !s3 && !s2){
    forward(avoidSpeed, sharpspeed);
    delay(standardDelay);
    past = -1;
  }
  if(s2 && s3 && !s4){ // sharp turns
    forward(sharpspeed, avoidSpeed);
    delay(extremeDelay);
    past =2;
  }if(s4 && s3 && !s2){ //sharp turns
    forward(avoidSpeed, sharpspeed);
    delay(extremeDelay);
    past = -2;
  }if(s3 && !s2 && !s1){
    forward(defaultSpeed, defaultSpeed);
    past = 0;
  // } else {
  //   pastD();
  }
}