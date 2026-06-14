#include <AccelStepper.h>

// 定义引脚
AccelStepper motor1(AccelStepper::DRIVER, 2, 5); // STEP1=2, DIR1=5
AccelStepper motor2(AccelStepper::DRIVER, 3, 6); // STEP2=3, DIR2=6

int VRX_PIN = A0;
int VRY_PIN = A1;

void setup() {
  pinMode(8, OUTPUT); // EN1
  pinMode(9, OUTPUT); // EN2
  digitalWrite(8, LOW); 
  digitalWrite(9, LOW);

  motor1.setMaxSpeed(1000);
  motor1.setAcceleration(500);
  motor2.setMaxSpeed(3000);
  motor2.setAcceleration(500);
}

void loop() {
  int xVal = analogRead(VRX_PIN);
  int yVal = analogRead(VRY_PIN);

  // 映射逻辑：将摇杆读数转为电机速度
  // 512为中间值，设定死区
  int speed1 = map(xVal, 0, 1023, -1000, 1000);
  int speed2 = map(yVal, 0, 1023, -1000, 1000);

  if (abs(speed1) < 100) speed1 = 0; // 死区处理
  if (abs(speed2) < 200) speed2 = 0;

  motor1.setSpeed(speed1);
  motor2.setSpeed(speed2);
  
  motor1.runSpeed();
  motor2.runSpeed();
}