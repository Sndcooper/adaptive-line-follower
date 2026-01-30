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
int turnSpeed = 130;
int sharpspeed = 180;
int baseTurnSpeed = 50;
int prev = -1;

int curve =0;

int leftAmp = 0;
int rightAmp = 0;
int multiplier = 20;

void forward(int leftSpeed, int rightSpeed) {
  // Set left motor direction forward
  rightSpeed = constrain(rightSpeed, 0, 255);
  leftSpeed = constrain(leftSpeed, 0, 255);
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
  analogWrite(PWMA, sharpspeed);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, 0);
  delay(60);
}

void right(){
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW); 
  analogWrite(PWMA, 0);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, sharpspeed);
  delay(60);
}

void pastD(){
  if(prev == 3){
    left(); 
  }else if (prev == 4){
    right();
  }else if(prev == 1){
    forward(turnSpeed+rightAmp, baseTurnSpeed);
  }else if (prev == 2){
    forward(baseTurnSpeed, turnSpeed+leftAmp);
  }else if (prev == 0){
    forward(baseSpeed, baseSpeed);
    forward(0,0);
  }
}

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
  Serial.print(" IR5: "); Serial.print(digitalRead(IR5));
  Serial.print(" leftAmp: "); Serial.print(leftAmp);
  Serial.print(" rightAmp: "); Serial.println(rightAmp);
  int s2 = digitalRead(IR2);
  int s4 = digitalRead(IR4);
  int s1 = digitalRead(IR1);
  int s5 = digitalRead(IR5);
  int s3 = digitalRead(IR3);
  // if (leftAmp > 60)
  // {
  //   left();
  //   prev = 3;
  // }
  // else if (rightAmp > 60)
  // {
  //   right();
  //   prev = 4;
  // }

  if((s1 ==0) && (s2 == 0) && (s4 == 0) && (s5 == 0)){
    forward(baseSpeed, baseSpeed);
    prev = 0;
    leftAmp = 0;
    rightAmp = 0;
  }
  else if((s1 ==1) && (s2 ==1) && (s3 ==1) && (s4 ==1) ){ // && (s5 ==1)
    pastD();
  }
  else if ((s1 ==1) && (s2 ==1) && (s5 ==1) && (s4 ==1)){
    pastD();
  }
  // else if (s1 ==1 && s2 ==1 && s4 ==1){
  //   right();
  //   prev = 4;
  //   // rightAmp += multiplier;
  // }
  else if(s4 ==1 && s5 ==1 && s2 ==1){
    pastD();
  }
  else if (s2 ==1 && s4 ==1)
  {
    pastD();
  }
  // else if(s1 ==1 && s5 ==1) {
  //   pastD();
  // }
  else if ((s1 == 1) && (s2 ==1)) {
    right();
    prev = 4;
  }
  else if ((s5 == 1) && (s4 ==1)) {
    left();
    prev = 3;

  }
  else if(s5 == 1) {
    // if (prev !=0){
    //   forward(baseTurnSpeed, turnSpeed+leftAmp); // Turn left
    //   prev = 2;
    // }else{
    //   right();
    //   prev = 4;
    // }
    right();
    prev = 4;
  }
  else if (s1 == 1) {
    // if (prev !=0){
    //   forward(turnSpeed+rightAmp, baseTurnSpeed); // Turn right
    //   prev = 1;
    // }else{
    //   left();
    //   prev = 3;
    // }
    left();
    prev = 3;
  }
  else if (s2 == 1) {
    forward(turnSpeed+rightAmp, baseTurnSpeed); // Turn right
    prev = 1;
    rightAmp += multiplier;
    // delay(10);
  } 
  else if (s4 == 1) {
    forward(baseTurnSpeed, turnSpeed+leftAmp); // Turn left
    prev = 2;
    leftAmp += multiplier;
    // delay(10);
  }
  else {
    forward(0, 0); // Stop
  }
}