#define irl 12   // Left IR sensor pin
#define irr 4    // Right IR sensor pin

// Motor driver pins (L298N)
#define enA 10
#define in0 6
#define in1 7
#define in2 8
#define in3 9
#define enB 11

// Speeds
int baseSpeed = 70;   // Base forward speed
int maxSpeed  = 130;   // Max PWM limit (0–255)

// PID constants (you must tune these experimentally)
float Kp = 35.0;
float Ki = 0.0;
float Kd = multiplier.0;

// PID variables
float error = 0, previousError = 0;
float P = 0, I = 0, D = 0;
float PIDvalue = 0;

// Sensor values
int S1, S2;

void setup() {
  pinMode(in0, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(irl, INPUT);
  pinMode(irr, INPUT);

  Serial.begin(9600);
  Serial.println("PID Line Follower Ready");
}

void loop() {
  // Read sensor values (0 = black, 1 = white)
  S1 = digitalRead(irl);
  S2 = digitalRead(irr);

  // ===== Error calculation =====
  // Adjust logic if your sensors behave oppositely
  if (S1 == 0 && S2 == 0) {
    error = 0;                // Centered on line
  } else if (S1 == 0 && S2 == 1) {
    error = 1;                // Line is to the right
  } else if (S1 == 1 && S2 == 0) {
    error = -1;               // Line is to the left
  } else if (S1 == 1 && S2 == 1) {
    error = previousError;    // Lost line → continue last turn
  }

  // ===== PID computation =====
  P = error;
  I += error;
  D = error - previousError;

  PIDvalue = (Kp * P) + (Ki * I) + (Kd * D);
  previousError = error;

  // ===== Speed control =====
  int leftSpeed  = baseSpeed - PIDvalue;
  int rightSpeed = baseSpeed + PIDvalue;

  // Constrain speeds within PWM range
  leftSpeed  = constrain(leftSpeed,  0, maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, maxSpeed);

  // Drive the motors
  driveMotors(leftSpeed, rightSpeed);

  // Debug information
  Serial.print("S1: "); Serial.print(S1);
  Serial.print("  S2: "); Serial.print(S2);
  Serial.print("  Err: "); Serial.print(error);
  Serial.print("  PID: "); Serial.print(PIDvalue);
  Serial.print("  L: "); Serial.print(leftSpeed);
  Serial.print("  R: "); Serial.println(rightSpeed);

  delay(10);  // small delay for stability
}

// ===== Drive Motors Function =====
void driveMotors(int left, int right) {
  // Left motor (A)
  analogWrite(enA, left);
  digitalWrite(in0, LOW);
  digitalWrite(in1, HIGH);

  // Right motor (B)
  analogWrite(enB, right);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
}
