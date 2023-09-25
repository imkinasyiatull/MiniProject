#include <Servo.h>
#define servo_PIN 3
#define servo_PIN 5
#define servo_PIN 6
#define servo_PIN 9
#define sw1 2
#define sw2 4
#define ver1  A0
#define hor1  A1
#define ver2  A2
#define hor2  A3

Servo iniServo1;
Servo iniServo2;
Servo iniServo3;
Servo iniServo4;

int angle1 = 0;
int angle2 = 0;
int angle3 = 0;
int angle4 = 0;
const int limit_angle = 180;

void setup() {
  Serial.begin(9600);
  iniServo1.attach(3);
  iniServo2.attach(5);
  iniServo3.attach(6);
  iniServo4.attach(9);
  iniServo1.write(angle1);
  iniServo2.write(angle2);
  iniServo3.write(angle3);
  iniServo4.write(angle4);
}

void loop() {
  while(analogRead(hor1) < 512){
    if(angle1 < limit_angle){
      iniServo1.write(angle1);
      angle1 ++;
      delay(20);
      Serial.println(angle1);
    }
  }
  while(analogRead(hor1) > 512){
    if(angle1 > 0){
      iniServo1.write(angle1);
      angle1 --;
      delay(20);
      Serial.println(angle1);
    }
  }
  while(analogRead(ver1) < 512){
    if(angle2 < limit_angle){
      iniServo2.write(angle2);
      angle2 ++;
      delay(20);
      Serial.println(angle2);
    }
  }
  while(analogRead(ver1) > 512){
    if(angle2 > 0){
      iniServo2.write(angle2);
      angle2 --;
      delay(20);
      Serial.println(angle2);
    }
  }
  while(analogRead(hor2) < 512){
    if(angle3 < limit_angle){
      iniServo3.write(angle3);
      angle3 ++;
      delay(20);
      Serial.println(angle3);
    }
  }
  while(analogRead(hor2) > 512){
    if(angle3 > 0){
      iniServo3.write(angle3);
      angle3 --;
      delay(20);
      Serial.println(angle3);
    }
  }
  while(analogRead(ver2) < 512){
    if(angle4 < limit_angle){
      iniServo4.write(angle4);
      angle4 ++;
      delay(20);
      Serial.println(angle4);
    }
  }
  while(analogRead(ver2) > 512){
    if(angle4 > 0){
      iniServo4.write(angle4);
      angle4 --;
      delay(20);
      Serial.println(angle4);
    }
  }
}
