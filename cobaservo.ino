#include <Servo.h>

Servo servo1;
Servo servo2;

#define joyX A0
#define joyY A1
#define SERVO1_PIN 3
#define SERVO2_PIN 9

int angle1 = 90;
int angle2 = 90;

void setup() {
  Serial.begin(9600);
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);

  servo1.write(angle1);
  servo2.write(angle2);
  delay(500);
}

void loop() {
  int joyYValue = analogRead(joyY);
  int joyXValue = analogRead(joyX);
  Serial.print(joyYValue);
  Serial.print(" - ");
  Serial.println(angle1);

  if (joyYValue > 600) {
    angle1++;
    // spin1();
  }
  if (joyYValue < 400) {
    angle1--;
    // spin1();
  }

  if (joyXValue > 600) {
    angle2++;
    spin2();
  }
  if (joyXValue < 400) {
    angle2--;
    spin2();
  }
  
  angle1 = constrain(angle1, 0, 180);
  servo1.write(angle1);

  delay(10);
}

void spin1() {
  angle1 = constrain(angle1, 0, 180);
  servo1.write(angle1);
}

void spin2() {
  angle2 = constrain(angle2, 0, 180);
  servo2.write(angle2);
}