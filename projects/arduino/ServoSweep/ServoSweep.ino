#include <Servo.h>
Servo servo;
int servoPin = 11;
int angle = 0;
int interval = 3;
int delayValue = 20;
int increment = 1;

void printAngle( int value )
{
  char str[10];
  //Serial.println("printAngle");
  itoa(value, str, 10);
  Serial.println("Angle ");
  Serial.println(str);
}

void updateServo( int value )
{
  //Serial.println("updateServo");
  if (value >= 0 && value <= 180)
  {
    servo.write(value);
    delay(delayValue);
  }
}

void setup() {
    // put your setup code here, to run once:
    servo.attach( servoPin );
    Serial.begin(115200);
    Serial.println("Set Angle 0 to 180");
}

void loop() {

    // put your main code here, to run repeatedly:
    if (Serial.available())
    {
      if (increment)
      {
        angle += interval;
        printAngle( angle );
        updateServo( angle );
        if (angle >= 180)
        {
          increment = 0;
        }
      }
      else
      {
        angle -= interval;
        printAngle( angle );
        updateServo( angle );
        if (angle <= 0)
        {
          increment = 1;
        }
      }
    }
}
