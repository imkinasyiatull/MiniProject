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
#define ECHO_PIN 12
#define TRIG_PIN 13

Servo iniServo[4];
int angle[4] = {0, 0, 0, 0};
const int limit_angle = 180;
const int L1 = 25;
const int L2 = 25;
float x;
float y;
volatile float pi = 3.14159265359;

//--------------------------------------- Speed
int speed = 1;

//--------------------------------------- Setup
void setup() {
  Serial.begin(9600);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  iniServo[0].attach(servo1_PIN);
  iniServo[1].attach(servo2_PIN);
  iniServo[2].attach(servo3_PIN);
  iniServo[3].attach(servo4_PIN);
  for (int i = 0; i < 4; i++) {
    iniServo[i].write(angle[i]);
  }
}

//--------------------------------------- Loop
void loop() {
  if(digitalRead((10))){
    // iniServo[0].write(angle[0]);
    // iniServo[1].write(angle[1]);
    // iniServo[2].write(angle[2]);
    // iniServo[3].write(angle[3]);
    manual();
  }

  else if(digitalRead((11))){
    float distance = readDistance();
    Serial.println("distance : " + String(distance));
    iniServo[1].write(0);
    iniServo[2].write(0);
    x = 32.90;
    y = 29.85;
    inverseKinematics();
    iniServo[0].write(34.5);
    x = 20.23;
    y = 31.85;
    inverseKinematics();
    iniServo[3].write(90);
    delay(1000);
    iniServo[0].write(0);
    iniServo[1].write(0);
    iniServo[2].write(0);
    iniServo[3].write(0);
  }
}

//--------------------------------------- Manual
void manual(){
  if (angle[0] < limit_angle && analogRead(hor1) < 512) {
    manualRotate(0, "CW");
  }
  if (angle[0] > 0 && analogRead(hor1) > 512) {
    manualRotate(0, "CCW");
  }
  if (angle[1] < limit_angle && analogRead(ver1) < 512) {
    manualRotate(1, "CW");
  }
  if (angle[1] > 0 && analogRead(ver1) > 512) {
    manualRotate(1, "CCW");
  }
  if (angle[2] < limit_angle && analogRead(hor2) < 512) {
    manualRotate(2, "CW");
  }
  if (angle[2] > 0 && analogRead(hor2) > 512) {
    manualRotate(2, "CCW");
  }
  if (angle[3] < limit_angle && analogRead(ver2) < 512) {
    manualRotate(3, "CW");
  }
  if (angle[3] > 0 && analogRead(ver2) > 512) {
    manualRotate(3, "CCW");
  }
}

void manualRotate(int index, String direction) {
  if (direction == "CW") {
    angle[index] += speed;
  } else {
    angle[index] -= speed;
  }
  iniServo[index].write(angle[index]);
  delay(20);
  Serial.println(angle[index]);
}

//--------------------------------------- Auto
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

  Serial.println("x is "+ String(x)); 
  Serial.println("y is " + String(y)); 
  Serial.println("angle[0] is " + String(angleik1)); 
  Serial.println("angle[1] is " + String(angleik2)); 
  iniServo[1].write(angleik1); 
  iniServo[2].write(angleik2);
  delay(2000);
}

float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}
