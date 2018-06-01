/*
  Switch
  Changes the blink rate of LED based on switch is press or not pressed.
 
  This example code is in the public domain.
 */

const int ledA = 13;
const int ledB = 12;

const int swA = 8;

#define BLINK_SLOW        1000
#define BLINK_MEDIUM      500
#define BLINK_FAST        250
#define BLINK_VERY_FAST   100
#define BLINK_SUPER_FAST  50

int dly = BLINK_FAST;

int count = 0;

int swValue = 0;

//
// Main code here
//

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  
  pinMode(swA, INPUT);
  
  Serial.begin(9600);
  Serial.println("Switch, v0.1");
}

void loop() {
  swValue = digitalRead(swA);

  if (swValue == HIGH)
  {
    dly = BLINK_FAST;
  }
  else
  {
    dly = BLINK_SUPER_FAST;
  }
   
  digitalWrite(ledA, HIGH);   // set the LED on
  digitalWrite(ledB, LOW);    // set the LED on
  delay(dly);              // wait for a second
  
  digitalWrite(ledA, LOW);    // set the LED off
  digitalWrite(ledB, HIGH);   // set the LED off
  delay(dly);              // wait for a second
  
  count++;
  
  if (count % 10 == 0)
  {
    Serial.print(count);
    Serial.print(" dly ");
    Serial.println(dly);
  }
}

