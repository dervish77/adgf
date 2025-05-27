#include <Servo.h>
Servo servo;
int servoPin = 11;
int angle = 0;
int delayValue = 1000;

void setup() {
  // put your setup code here, to run once:
  servo.attach(servoPin);
  Serial.begin(115200);
  Serial.println("Set Angle 0 to 180");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    char str[10];
    angle = Serial.parseInt();
    itoa(angle, str, 10);
    Serial.println("Angle ");
    Serial.println(str);
    if (angle >= 0 && angle <= 180)
    {
      servo.write(angle);
      delay(delayValue);
    }
  }
}
