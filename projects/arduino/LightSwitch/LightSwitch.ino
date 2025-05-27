/*
  LightSwitch
  Changes the blink rate of LED based on signal level on light sensor.
 
  This example code is in the public domain.
 */

const int ledA = 13;
const int ledB = 12;

#define BLINK_SLOW        1000
#define BLINK_MEDIUM      500
#define BLINK_FAST        250
#define BLINK_VERY_FAST   100
#define BLINK_SUPER_FAST  50

int dly = BLINK_FAST;

int count = 0;

int sensorValue = 0;

//
// Main code here
//

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  
  pinMode(9, OUTPUT);   // attach piezo to pin 9
  beep(50);
  beep(50);
  
  Serial.begin(9600);
  Serial.println("LightSwitch, v0.1");
}

void loop() {
  sensorValue = analogRead(0);

  if (sensorValue < 850)
  {
    dly = BLINK_FAST;
  }
  else
  {
    dly = BLINK_SUPER_FAST;
  }
   
  digitalWrite(ledA, HIGH);   // set the LED on
  digitalWrite(ledB, LOW);    // set the LED on
  if (dly == BLINK_SUPER_FAST)
  {
    beep(dly);
  }
  else
  {
    delay(dly);              // wait for a second
  }
  
  digitalWrite(ledA, LOW);    // set the LED off
  digitalWrite(ledB, HIGH);   // set the LED off
  delay(dly);              // wait for a second
  
  count++;
  
  if (count % 10 == 0)
  {
    Serial.print(count);
    Serial.print(" dly ");
    Serial.print(dly);
    Serial.print(" ");
    Serial.println(sensorValue);
  }
}

void beep(unsigned char delayms){
  analogWrite(9, 20);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  analogWrite(9, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms   
}  

