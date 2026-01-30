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
int baseSpeed = 90;
int turnBoost = 40;
int prev = -1;

void forward(int leftSpeed, int rightSpeed) {
  // Set left motor direction forward
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, rightSpeed);

  // Set right motor direction forward
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, leftSpeed);
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

  if(s2 == 0 && s4 == 0) {
    forward(baseSpeed, baseSpeed);
    prev = 0;
  } 
  else if (s2 ==1 && s4 ==1)
  {
    if(prev == 1){
      forward(baseSpeed+50, 0); 
    }
    else if (prev == 2)
    {
      forward(0, baseSpeed+50); 
    }
    else {
      forward(0,0);
    }
    
  }
  else if (s2 == 1) {
    forward(baseSpeed+50, 0); // Turn left
    prev = 1;
  } 
  else if (s4 == 1) {
    forward(0, baseSpeed+50); // Turn right
    prev = 2;
  }
}