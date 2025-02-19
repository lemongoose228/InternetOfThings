#include <Servo.h>

Servo servo;
const int servoPin = 9;
const int minAngle = 0;
const int maxAngle = 180;


void setup() {
  servo.attach(servoPin);
}

void loop() {
  for (int angle = minAngle; angle <= maxAngle; angle++) {
    servo.write(angle);
    delay(15);
  }
  for (int angle = maxAngle; angle >= minAngle; angle--) {
    servo.write(angle);
    delay(15);
  }
}
