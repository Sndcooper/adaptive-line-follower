#include <Arduino.h>
#include <EEPROM.h>
#include <L298N.h>

// Motor pins
#define AIN1 7
#define AIN2 8
#define PWMA 5
#define BIN1 10
#define BIN2 9
#define PWMB 6

L298N motorLeft(PWMA, AIN1, AIN2);
L298N motorRight(PWMB, BIN1, BIN2);

// IR sensor pins
#define IR1 A1
#define IR2 A2
#define IR3 A3
#define IR4 A4
#define IR5 A5

// PID variables
float Kp = 25.0, Ki = 0.0, Kd = 15.0;
int error = 0, previousError = 0, integral = 0;

// Speed control variables
int baseSpeed = 95;
int minSpeed = 80;
int turnBoost = 60;

// EEPROM addresses
#define KP_ADDR 0
#define KI_ADDR 4
#define KD_ADDR 8

int readLinePosition() {
  bool s1 = !digitalRead(IR1);
  bool s2 = !digitalRead(IR2);
  bool s3 = !digitalRead(IR3);
  bool s4 = !digitalRead(IR4);
  bool s5 = !digitalRead(IR5);

  int position = 0;
  int activeCount = 0;

  if (s1) { position += -2; activeCount++; }
  if (s2) { position += -1; activeCount++; }
  if (s3) { position += 0;  activeCount++; }
  if (s4) { position += 1;  activeCount++; }
  if (s5) { position += 2;  activeCount++; }

  if (activeCount == 0) return (previousError > 0) ? 2 : -2;
  return position / activeCount;
}

void loadPID() {
  EEPROM.get(KP_ADDR, Kp);
  EEPROM.get(KI_ADDR, Ki);
  EEPROM.get(KD_ADDR, Kd);
}

void motor_drive(int left, int right) {
  left = constrain(left, minSpeed, 255);
  right = constrain(right, minSpeed, 255);

  if (left >= 0) {
    motorLeft.setSpeed(left);
    motorLeft.forward();
  } else {
    motorLeft.setSpeed(-left);
    motorLeft.backward();
  }

  if (right >= 0) {
    motorRight.setSpeed(right);
    motorRight.forward();
  } else {
    motorRight.setSpeed(-right);
    motorRight.backward();
  }
}

void handleSerial() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.startsWith("P=")) {
      Kp = input.substring(2).toFloat();
      Serial.print("Kp set to "); Serial.println(Kp);
    } else if (input.startsWith("I=")) {
      Ki = input.substring(2).toFloat();
      Serial.print("Ki set to "); Serial.println(Ki);
    } else if (input.startsWith("D=")) {
      Kd = input.substring(2).toFloat();
      Serial.print("Kd set to "); Serial.println(Kd);
    } else if (input.equalsIgnoreCase("SAVE")) {
      EEPROM.put(KP_ADDR, Kp);
      EEPROM.put(KI_ADDR, Ki);
      EEPROM.put(KD_ADDR, Kd);
      Serial.println("PID values saved to EEPROM.");
    } else if (input.equalsIgnoreCase("LOAD")) {
      loadPID();
      Serial.println("PID values loaded from EEPROM.");
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);

  loadPID();
  Serial.println("Send P=, I=, D= Type SAVE to store.");
}

void loop() {
  handleSerial();
  Serial.print("IR1: "); Serial.print(digitalRead(IR1));
  Serial.print(" IR2: "); Serial.print(digitalRead(IR2));
  Serial.print(" IR3: "); Serial.print(digitalRead(IR3));
  Serial.print(" IR4: "); Serial.print(digitalRead(IR4));
  Serial.print(" IR5: "); Serial.println(digitalRead(IR5));

  // Sharp turn overrid
  digitalRead(IR2);
  digitalRead(IR3);
  digitalRead(IR4);
  digitalRead(IR5);
  digitalRead(IR1);     
  if (digitalRead(IR1) == 1) {
    motor_drive(0, 255); // Sharp left
    return;
  } else if (digitalRead(IR5) == 1) {
    motor_drive(255, 0); // Sharp right
    return;
  }



  int position = readLinePosition();
  error = 0 - position;

  integral += error;
  int derivative = error - previousError;
  previousError = error;

  int correction = Kp * error + Ki * integral + Kd * derivative;

  int leftSpeed = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  // Apply turn boost if needed
  if (abs(error) > 1) {
    leftSpeed += (error < 0) ? -turnBoost : turnBoost;
    rightSpeed += (error > 0) ? -turnBoost : turnBoost;
  }

  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);

  motor_drive(leftSpeed, rightSpeed);
}