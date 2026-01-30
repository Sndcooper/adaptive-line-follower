#include <Arduino.h>
#define middle_pin A3//middle sensor pin
#define right_pin A2//right sensor pin
#define left_pin A4//left sensor pin

#define AIN1 7
#define AIN2 8
#define PWMA 5
#define BIN1 10
#define BIN2 9
#define PWMB 6

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


void setup(){

  pinMode(left_pin, INPUT);
  pinMode(right_pin, INPUT);
  pinMode(middle_pin, INPUT);
}

void loop() {
  //control straight function
  if (digitalRead(middle_pin) == 1 && digitalRead(left_pin) == 0 && digitalRead(right_pin) == 0){
  forward(130 , 130);

  }

  //control right function
  if (digitalRead(right_pin) == 1 && digitalRead(left_pin) == 0){

  if(digitalRead(middle_pin)!= 1){
  forward(200, -200);
    delay(100);
  }
  if(digitalRead(middle_pin)== 1 && digitalRead(right_pin)==1){
  forward(200, -200);
    delay(100);
  }
}
  // control left function
  if (digitalRead(left_pin) == 1 && digitalRead(right_pin) == 0){

  if(digitalRead(middle_pin)!= 1){
  forward(-200, 200);
  delay(100);
  }
  }
  if (digitalRead(middle_pin)== 1 && digitalRead(left_pin)==1){
  if(digitalRead(left_pin)!= 0){
  forward(-180, 200);
  delay(100);
  }
  }
}
