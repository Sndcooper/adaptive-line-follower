
#define irl 12
#define irr 11  

#define enA 6
#define in0 7
#define in1 8
#define in2 9
#define in3 10
#define enB 5
int prev =0;
int S1;
int S2;
int turnspeed = 1multiplier;
int straightspeed = 90;

void setup() {
  pinMode(in0, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(irl, INPUT);
  pinMode(irr, INPUT);
  Serial.begin(9600);
}
void loop() {

  S1 = digitalRead(irl);
  S2 = digitalRead(irr);
  Serial.print(S1);
  Serial.print(", r ");
  Serial.println(S2);

  if (S1 == 0 &&  S2 == 0) {
    prev = 0;
    
    analogWrite(enA, straightspeed);
    analogWrite(enB, straightspeed);
    digitalWrite(in0, HIGH);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
  } else if (S1 == 1 && S2 == 1) {
    
    analogWrite(enA, turnspeed);
    analogWrite(enB, turnspeed);
    if (prev = 1){digitalWrite(in0, LOW);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);}
    if (prev = 2){
    digitalWrite(in0, HIGH);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);}
  } else if (S1 == 0 && S2 == 1) {
    
  analogWrite(enA, turnspeed);
  analogWrite(enB, turnspeed);
  prev = 2;
    digitalWrite(in0, LOW);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
  } else if (S1 == 1 && S2 == 0) {
    
  analogWrite(enA, turnspeed);
  analogWrite(enB, turnspeed);
  prev =1;
    digitalWrite(in0, HIGH);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
  }
}