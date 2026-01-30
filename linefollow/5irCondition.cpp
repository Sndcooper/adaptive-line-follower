#include <Arduino.h>

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

int s1, s2, s3, s4, s5;

// Speed control variables
int defaultSpeed = 120;
int sharpspeed = 130;
int avoidSpeed = -150;
// int curveSpeed = -80;
// int turnspeed = 140;
// int baseTurnSpeed = 60;
int past = 0;

int standardDelay = 80;
int extremeDelay = 180;

int lSpeed ;
int rSpeed ;

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
  
  Serial.print(" leftSpeed: "); Serial.print(lSpeed);
  Serial.print(" rightSpeed: "); Serial.println(rSpeed);
  // Set left motor direction forward
  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);
  lSpeed = leftSpeed;
  rSpeed = rightSpeed;
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
    rightSpeed -=10;
    analogWrite(PWMA, -rightSpeed);
  }else{
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  rightSpeed+=10;
  analogWrite(PWMA, rightSpeed);}

}

void show(){
  s1 = digitalRead(IR1);
  s2 = digitalRead(IR2);
  s3 = digitalRead(IR3);
  s4 = digitalRead(IR4);
  s5 = digitalRead(IR5);
  Serial.print("IR1: "); Serial.print(s1);
  Serial.print(" IR2: "); Serial.print(s2);
  Serial.print(" IR3: "); Serial.print(s3);
  Serial.print(" IR4: "); Serial.print(s4);
  Serial.print(" IR5: "); Serial.print(s5);
  Serial.print(" Past: "); Serial.print(past);
}

void pastD(){
  // if(past == 0){
  //   forward(defaultSpeed, defaultSpeed);
  //   delay(standardDelay);
  // } else
   if (past == 1){
    forward(sharpspeed, -sharpspeed); // Turn right
    // delay(standardDelay);
  } else if (past == -1){
    forward(-sharpspeed, sharpspeed); // Turn left
    // delay(standardDelay);
  } else if (past == 2){
    forward(sharpspeed, -sharpspeed); // Turn right
    // delay(standardDelay);
  } else if (past == -2){
    forward(-sharpspeed, sharpspeed); // Turn left
    // delay(standardDelay);
  }
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

void loop() {
  show();

  if(s5 && s4&& s3 && s2){
    if(past != 0){  //fix when its left turn and not sharp curve.. viceversa
      forward(sharpspeed, -sharpspeed);
      delay(extremeDelay);
      past = -2;
    } else {
      forward(-sharpspeed, sharpspeed);
      delay(extremeDelay);
      past = -2;
    }
      
  }else if(s1 && s2 && s3 && s4){
    if (past !=0){ //fix when its left turn and not sharp curve.. viceversa
      forward(-sharpspeed, sharpspeed);
      delay(extremeDelay);
      past =2;
    } else {
      forward(sharpspeed, -sharpspeed);
      delay(extremeDelay);
      past =2;
    }
  }
  else if(s1 && s2 && s3 &&s4 &&s5){
    forward(-120, -120);
  }
  else if(s5 && s4 && s3){ 
    if(past<0){  // fix for left turn and 3 sens touching on sharp curves
      forward(sharpspeed, avoidSpeed);
      delay(extremeDelay);
      past =1;
    } else {
      forward(-10, sharpspeed);
      delay(extremeDelay);
      past = -1;
    }
  }else if(s1 && s2 && s3){
    
    if (past){   // fix for left turn and 3 sens touching on sharp curves
      forward(avoidSpeed, sharpspeed);
      delay(extremeDelay);
      past = -1;
    } else {
      forward(sharpspeed, -10);
      delay(extremeDelay);
      past =1;
    }
  } 
  else if(s2 && !s1 && !s3 && !s4 && !s5){ //glitch with light turns
    // if(past == -1 || past == -2){
    //   forward(avoidSpeed, sharpspeed); // Turn right
    //   past =-1;
    // } else {
    //   forward(avoidSpeed, sharpspeed); // Turn right
    //   past =-1;
    // }
    forward(sharpspeed, -10); // Turn left
    past = 2;
  } else if(s4 && !s5 && !s3 && !s2 && !s1){ //glitch with light turns
    // if (past == 1 || past ==2){
    //   forward(sharpspeed, avoidSpeed); // Turn left
    //   past = 1;
    // } else {
    //   forward(sharpspeed, avoidSpeed); // Turn left
    //   past = 1;
    // }
    forward(-10, sharpspeed); // Turn right
    past =-2;
    
  }
  else if (s2) {
    if(past == -1 || past == -2){ //checking ir if prev it was sharp curve
      forward(sharpspeed, avoidSpeed); // Turn right
      delay(standardDelay);
      past =2;
  } else {
    if (s1){
      forward(sharpspeed, -sharpspeed);
      delay(extremeDelay);
      past =2;
    } else {
      forward(sharpspeed, avoidSpeed); // Turn right
      delay(standardDelay);
      past =1;
    }
  }  
  }else if (s5) {
    forward(-sharpspeed, sharpspeed);
    delay(extremeDelay);
    past = -2;
  } else if (s1) {
    forward(sharpspeed, -sharpspeed);
    delay(extremeDelay);
    past = 2;
  } else if (s4) {
  if (past == 1 || past ==2){ //checking ir prev it was sharp curve
    forward(avoidSpeed, sharpspeed); // Turn left
    delay(standardDelay);
    past = -2;
  } else {
    if(s5){
      forward(-sharpspeed, sharpspeed);
      delay(extremeDelay);
      past = -2;
    } else {
      forward(avoidSpeed, sharpspeed); // Turn left
      past = -1;
      delay(standardDelay);
    }
  }
  }
  else if (s5) {
    forward(-sharpspeed, sharpspeed);
    delay(extremeDelay);
    past = -2;
  } else if (s1) {
    forward(sharpspeed, -sharpspeed);
    delay(extremeDelay);
    past = 2;
  }
  else if (s3 && s2) {
    forward(sharpspeed, -sharpspeed);
    delay(0);
    past = 2;
  }
  else if (s3 && s4) {
    forward(-sharpspeed, sharpspeed);
    delay(0);
    past = -2;
  }
  else if (s3) {
    if (past == 0){
      forward(defaultSpeed, defaultSpeed);
      past =0;
    }
    // else if (IR1 || IR2 || IR4 || IR5){
    //   pastD();
    // }
    else{
      past = 0;
      forward(105, 105);
    }
  }
  else {
    pastD();
  }
}
