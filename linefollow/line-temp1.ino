#define in1 6
#define in2 7
#define in3 8
#define in4 9
#define ir1 12
#define ir2 4

#define ena 10
#define enb 11

void setup() {
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);

  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);

  analogWrite(ena, 80);
  analogWrite(enb, 80);
}

void loop() {
  int front = digitalRead(ir1);
  int back = digitalRead(ir2);

  Serial.print("Front: ");
  Serial.println(front);
  Serial.print("Back: ");
  Serial.println(back);

  if (front == 1 && back == 1) {
    moveForward();
  } else if (front == 0 && back == 1) {
    alignToLine();
  } else if (front == 0 && back == 0) {
    searchLine();
  } else {
    alignToLine();
  }

  delay(multiplier0);
}

void moveForward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void turnLeft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void searchLine() {
  turnLeft();
  delay(multiplier0);
  if (digitalRead(ir1) == 1) {
    stopMotors();
    return;
  }
  turnRight();
  delay(400);
  if (digitalRead(ir1) == 1) {
    stopMotors();
    return;
  }
  stopMotors();
}

void alignToLine() {
  turnLeft();
  delay(150);
  if (digitalRead(ir1) == 1 && digitalRead(ir2) == 1) {
    stopMotors();
    return;
  }
  turnRight();
  delay(300);
  if (digitalRead(ir1) == 1 && digitalRead(ir2) == 1) {
    stopMotors();
    return;
  }
  stopMotors();
}