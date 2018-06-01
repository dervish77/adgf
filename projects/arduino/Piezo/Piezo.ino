/*
 Piezo
 
 This example shows how to run a Piezo Buzzer on pin 9
 using the analogWrite() function.
 
 It beeps 3 times fast at startup, waits a second then beeps continuously
 at a slower pace
 
 */
 
#define TONE   20
#define DELAY  200

void setup()  { 
  // declare pin 9 to be an output:
  pinMode(9, OUTPUT);
  beep(50);
  beep(50);
  beep(50);
  
  Serial.begin(9600);
  Serial.println("Piezo, v0.1");
  
  delay(1000);
} 

void loop()  { 
  beep(DELAY); 
}

void beep(unsigned char delayms){
  analogWrite(9, TONE);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  analogWrite(9, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms   
}  
