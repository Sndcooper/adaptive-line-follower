#include<Arduino.h>

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

int multiplier = 15;
int baseSpeed = 85;
int baseTurnSpeed = 65;
int turnSpeed = 120;
int curveCount = 0;
int direction = 0;
int LcurveSpeed = 0;
int RcurveSpeed = 0;
int s1, s2, s3, s4 ,s5;

void forward(int Lspeed, int Rspeed){
    Lspeed = constrain(Lspeed, 0, 210); //left motor speed
    Rspeed = constrain(Rspeed, 0, 210); //right motor speed
    if (Lspeed >=0)
    {
        digitalWrite(BIN1, 1);
        digitalWrite(BIN2, 0);
        analogWrite(PWMB, Lspeed);
        
    }else {
        digitalWrite(BIN1, 0);
        digitalWrite(BIN2, 1);
        analogWrite(PWMB, -Lspeed);
    }

    if (Rspeed >=0)
    {
        digitalWrite(AIN1, 1);
        digitalWrite(AIN2, 0);
        analogWrite(PWMA, Rspeed);

    }else {
        digitalWrite(AIN1, 0);
        digitalWrite(AIN2, 1);
        analogWrite(PWMA, -Rspeed);
    }
    
    
}

void setup(){

    Serial.begin(9600);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(IR1, OUTPUT);
    pinMode(IR2, OUTPUT);
    pinMode(IR3, OUTPUT);
    pinMode(IR4, OUTPUT);
    pinMode(IR5, OUTPUT);

}

void loop (){
    s1 = digitalRead(IR1);
    s2 = digitalRead(IR2);
    s3 = digitalRead(IR3);
    s4 = digitalRead(IR4);
    s5 = digitalRead(IR5);

    if()
    


}