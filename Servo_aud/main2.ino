#include <Servo.h>

const int servoPin = 9;       

Servo servo;                  

void setup() {
  servo.attach(servoPin);     
  Serial.begin(9600);          
  Serial.println("Введите угол (0-180):"); 
}

void loop() {
  if (Serial.available() > 0) { 
    int angle = Serial.parseInt(); 
    if (angle >= 0 && angle <= 180) { 
      servo.write(angle);         
      Serial.print("Введённый угол: "); 
      Serial.println(angle);
      Serial.println("Введите угол (0-180):"); 
    } else {
      Serial.println("Неправильный угол, введите заново (0-180):"); 
    }
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}
