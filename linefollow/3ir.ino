

// IR sensor pins
const int leftSensorPin = 2;
const int centerSensorPin = 3;
const int rightSensorPin = 4;

// Motor driver pins
const int ENA = 5;     // PWM for left motor
const int IN1 = 7;     // Direction for left motor
const int IN2 = 8;

const int ENB = 6;     // PWM for right motor
const int IN3 = 9;    // Direction for right motor
const int IN4 = 10;

// Speed control variables
int defaultSpeed = 100;
int maxSpeed = multiplier0;
int minSpeed = 60;

void setup() {
  Serial.begin(9600);

  // IR sensors
  pinMode(leftSensorPin, INPUT);
  pinMode(centerSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);

  // Motor control pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  int leftSensor = digitalRead(leftSensorPin);
  int centerSensor = digitalRead(centerSensorPin);
  int rightSensor = digitalRead(rightSensorPin);

  Serial.print("L:");
  Serial.print(leftSensor);
  Serial.print(" C:");
  Serial.print(centerSensor);
  Serial.print(" R:");
  Serial.println(rightSensor);

  if (centerSensor == HIGH && leftSensor == LOW && rightSensor == LOW) {
    moveForward(defaultSpeed, defaultSpeed);
  } else if (leftSensor == HIGH) {
    moveForward(maxSpeed, minSpeed); // Turn left
  } else if (rightSensor == HIGH) {
    moveForward(minSpeed, maxSpeed); // Turn right
  } else {
    stopMotors();
  }

  delay(100);
}

void moveForward(int leftSpeed, int rightSpeed) {
  // Left motor forward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, leftSpeed);

  // Right motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENB, rightSpeed);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}