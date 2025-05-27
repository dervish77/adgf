/*
Adafruit Arduino - Lesson 13. DC Motor
*/
 
 
int motorPin = 3;

int motorSpeed = 128;
 
int sensorValue = 0;

int count = 0;

 
void setup() 
{ 
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  
} 
 
 
void loop() 
{ 
  sensorValue = analogRead(0);
    
  //motorSpeed = (1023 - sensorValue) / 4;
  motorSpeed = 64 + (sensorValue) / 8;
  
  count++;
  
  if (count % 10 == 0)
  {
    Serial.print("Speed is ");
    Serial.println(motorSpeed);  
  }
  
  if (motorSpeed >= 0 && motorSpeed <= 255)
  {
    analogWrite(motorPin, motorSpeed);
  }
    
  delay(100);
} 
