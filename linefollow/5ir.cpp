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
int defaultSpeed = 150;
int sharpspeed = 180;
int turnspeed = 170;
int baseTurnSpeed = 60;
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

void pastD(){ // 0 is straight 1 is mid left 2 is slight left 3 is sharpleft 4 is 90 left
  
}

void loop() {
  Serial.print("IR1: "); Serial.print(digitalRead(IR1));
  Serial.print(" IR2: "); Serial.print(digitalRead(IR2));
  Serial.print(" IR3: "); Serial.print(digitalRead(IR3));
  Serial.print(" IR4: "); Serial.print(digitalRead(IR4));
  Serial.print(" IR5: "); Serial.println(digitalRead(IR5));

  int s1 = digitalRead(IR1);
  int s2 = digitalRead(IR2);
  int s3 = digitalRead(IR3);
  int s4 = digitalRead(IR4);
  int s5 = digitalRead(IR5);

  // if ( (s2 ==1) && (s4 ==1 )&& (s3 ==1)) {
  //   pastD();
  // }else 
  if (s4 == 1) {
    forward(-sharpspeed, sharpspeed);
  }else if (s2 == 1) {
    forward(sharpspeed, -sharpspeed);
  } else if( s5 == 1) {
    forward(-sharpspeed, sharpspeed);
    delay(100);
  } else if (s1 == 1) {
    forward(sharpspeed, -sharpspeed);
    delay(100);
  } else if (s3 == 1){
    forward(defaultSpeed, defaultSpeed);
  }
  else if((s5 == 1) && (s4 == 1)){
    forward(-sharpspeed, sharpspeed);
  }else if ((s1 == 1) && (s2 == 1)){
    forward(sharpspeed, -sharpspeed);
  }
  
  else if (s2 == 1 && s3 ==1) {
    forward(turnspeed, 0);
  }
  else if( s4 == 1 && s3 ==1) {
    forward(0, turnspeed);
  }else if((s1 == 1) && (s2 ==1) && (s3==1)) {
    forward(sharpspeed, -sharpspeed);
    delay(800);
  }else if (s3 == 1){
    forward(defaultSpeed, defaultSpeed);
  }
  else if ((s3 == 1) && (s2 ==0) && (s4 ==0)) {
    forward(defaultSpeed, defaultSpeed);
  }else if ((s5 == 1) && (s4 ==1) && (s3==1)) {
    forward(-sharpspeed, sharpspeed);
    delay(800);
  }
  else if((s1 == 1) && (s2 ==1) && (s3==1) && (s4==1)) {
    forward(sharpspeed, 0);
    delay(100);
  }
  else if((s1 == 1) && (s2 == 1) && (s4 == 1) && (s5 == 1)) {
    forward(0,0);
  } 
  else if ((s5 == 1) && (s4 ==1) && (s3==1) && (s2==1)) {
    forward(0, sharpspeed);
    delay(100);
  } 
  else {
    pastD();
  }
}