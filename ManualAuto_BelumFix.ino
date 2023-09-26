#include <Servo.h>
#define servo1_PIN 3
#define servo2_PIN 5
#define servo3_PIN 6
#define servo4_PIN 9
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
const int L1 = 25;
const int L2 = 25;
float x;
float y;
volatile float pi = 3.14159265359;

void setup() {
  Serial.begin(9600);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
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
  if(digitalRead((10))){
    iniServo1.write(angle1);
    iniServo2.write(angle2);
    iniServo3.write(angle3);
    iniServo4.write(angle4);
    manual();
  }
  else if(digitalRead((11))){
    iniServo2.write(0);
    iniServo3.write(0);
    x = 32.90;
    y = 29.85;
    inverseKinematics();
    iniServo1.write(34.5);
    x = 20.23;
    y = 31.85;
    inverseKinematics();
    iniServo4.write(90);
    delay(1000);
    iniServo1.write(0);
    iniServo2.write(0);
    iniServo3.write(0);
    iniServo4.write(0);
  }
}

void manual(){
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

void inverseKinematics(){
  float angleik1;      
  float angleik2;       
  float rad_angle1;  
  float rad_angle2; 
     
  rad_angle2 = acos((sq(x)+ sq(y) - sq(L1) - sq(L2)) / (2*L1*L2));
  rad_angle1= atan(y / x) - atan((L2*sin(rad_angle2)) / (L1+ L2*cos(rad_angle2)));
  delay(1000);

  angleik1= (rad_angle1*180)/pi;
  angleik2= (rad_angle2*180)/pi;

  Serial.print("x is "); 
  Serial.println(x);
  Serial.print("y is "); 
  Serial.println(y);
  Serial.print("angle1 is  "); 
  Serial.println(angleik1);
  Serial.print("angle2 is "); 
  Serial.println(angleik2);
  iniServo2.write(angleik1); 
  iniServo3.write(angleik2);
  delay(2000);
}
