#include <Servo.h>
#define servo_PIN_3 3
#define servo_PIN_5 5
#define servo_PIN_6 6
#define servo_PIN_9 9

#define sw1 2
#define sw2 4

#define ver1 A0
#define hor1 A1
#define ver2 A2
#define hor2 A3

Servo iniServo[4];
int angle[4] = {0, 0, 0, 0};
const int limit_angle = 180;

// ---------------------------------------- Change speed
int speed = 1;
// -----------------------------------------------------

void setup() {
  Serial.begin(9600);
  iniServo[0].attach(servo_PIN_3);
  iniServo[1].attach(servo_PIN_5);
  iniServo[2].attach(servo_PIN_6);
  iniServo[3].attach(servo_PIN_9);
  for (int i = 0; i < 4; i++) {
    iniServo[i].write(angle[i]);
  }
}

void loop() {
  if (angle[0] < limit_angle && analogRead(hor1) < 512) {
    rotate(0, "CW");
  }
  if (angle[0] > 0 && analogRead(hor1) > 512) {
    rotate(0, "CCW");
  }
  if (angle[1] < limit_angle && analogRead(ver1) < 512) {
    rotate(1, "CW");
  }
  if (angle[1] > 0 && analogRead(ver1) > 512) {
    rotate(1, "CCW");
  }
  if (angle[2] < limit_angle && analogRead(hor2) < 512) {
    rotate(2, "CW");
  }
  if (angle[2] > 0 && analogRead(hor2) > 512) {
    rotate(2, "CCW");
  }
  if (angle[3] < limit_angle && analogRead(ver2) < 512) {
    rotate(3, "CW");
  }
  if (angle[3] > 0 && analogRead(ver2) > 512) {
    rotate(3, "CCW");
  }
}

void rotate(int index, String direction) {
  if (direction == "CW") {
    angle[index] += speed;
  } else {
    angle[index] -= speed;
  }
  iniServo[index].write(angle[index]);
  delay(20);
  Serial.println(angle[index]);
}
