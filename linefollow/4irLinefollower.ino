#define ir1 1   // Leftmost sensor
#define ir2 2   // Left-center
#define ir3 3   // Right-center
#define ir4 4   // Rightmost

#define enA 6
#define in1 7
#define in2 8
#define in3 9
#define in4 10
#define enB 5

int S1, S2, S3, S4;
int prev = 0;

int baseSpeed = 80;     // Normal straight speed
int turnSpeedHigh = 130; // For outer wheel during turns
int turnSpeedLow  = 60;  // For inner wheel during turns

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);

  Serial.begin(9600);
}

void loop() {
  S1 = digitalRead(ir1);
  S2 = digitalRead(ir2);
  S3 = digitalRead(ir3);
  S4 = digitalRead(ir4);

  Serial.print(S1);
  Serial.print(" ");
  Serial.print(S2);
  Serial.print(" ");
  Serial.print(S3);
  Serial.print(" ");
  Serial.println(S4);

  // Default forward
  int leftSpeed = baseSpeed;
  int rightSpeed = baseSpeed;

  // --- Decision Logic ---
  if ((S2 == 1 && S3 == 1) || (S1==0 && S4==0 && S2==1 && S3==1)) {  // On line (center sensors active)
    leftSpeed = baseSpeed;
    rightSpeed = baseSpeed;
    prev = 0;
  }

  else if ((S1 == 1 && S2 == 0 && S3 == 0 && S4 == 0) || (S1 == 1 && S2 == 1 && S3 == 0 && S4 == 0)) { // Hard Left
    leftSpeed = turnSpeedLow;
    rightSpeed = turnSpeedHigh;
    prev = 1;
  }

  else if ((S1 == 0 && S2 == 0 && S3 == 0 && S4 == 1) || (S1 == 0 && S2 == 0 && S3 == 1 && S4 == 1)) { // Hard Right
    leftSpeed = turnSpeedHigh;
    rightSpeed = turnSpeedLow;
    prev = 2;
  }

  else if ((S2 == 1 && S3 == 0) || (S1 == 0 && S2 == 1 && S3 == 0 && S4 == 0)) { // Slight Left
    leftSpeed = turnSpeedLow;
    rightSpeed = turnSpeedHigh;
    prev = 1;
  }

  else if ((S2 == 0 && S3 == 1) || (S1 == 0 && S2 == 0 && S3 == 1 && S4 == 0)) { // Slight Right
    leftSpeed = turnSpeedHigh;
    rightSpeed = turnSpeedLow;
    prev = 2;
  }

  else if (S1 == 0 && S2 == 0 && S3 == 0 && S4 == 0) { // Line lost
    if (prev == 1) { // last seen line on left
      leftSpeed = turnSpeedLow;
      rightSpeed = turnSpeedHigh;
    } else if (prev == 2) { // last seen line on right
      leftSpeed = turnSpeedHigh;
      rightSpeed = turnSpeedLow;
    } else { // lost completely
      leftSpeed = 0;
      rightSpeed = 0;
    }
  }

  else if (S1 == 1 && S2 == 1 && S3 == 1 && S4 == 1) { // All black - intersection
    leftSpeed = baseSpeed;
    rightSpeed = baseSpeed;
  }

  // --- Apply Motor Speeds ---
  analogWrite(enA, constrain(leftSpeed, 0, 255));
  analogWrite(enB, constrain(rightSpeed, 0, 255));

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
