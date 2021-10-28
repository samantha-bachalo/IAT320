/* Code modified by Samantha Bachalo from Adafruit Carter Nelson's "Hello Capacitive Touch" example code: 
    
    Title: Hello Capacitive Touch
    Author: Nelson, C.
    Date: 2016
    Availability: https://learn.adafruit.com/circuit-playground-fruit-drums/hello-capacitive-touch 

*/

#include <Adafruit_CircuitPlayground.h>

#define CAP_THRESHOLD   500
#define DEBOUNCE        250 // one quarter of a second

int timer = 0; // timer variable that will be used to count up
int completeTime = 9; // beeps ten times before it's complete, since the delay is a quarter of a second
boolean completeCounter = false; // counter to see if the completion sound has played once
boolean failedCounter = false; // counter to see if the failure sound has played once

////////////////////////////////////////////////////////////////////////////
boolean capButton(uint8_t pad) 
{
  if (CircuitPlayground.readCap(pad) > CAP_THRESHOLD) 
  {
    return true;  
  } 
  
  else 
  {
    return false;
  }
}

////////////////////////////////////////////////////////////////////////////
void setup() 
{
  // Initialize serial.
  Serial.begin(9600); 
  
  // Initialize Circuit Playground library.
  CircuitPlayground.begin();
}

////////////////////////////////////////////////////////////////////////////
void loop() 
{
  // Check if capacitive touch exceeds threshold.
  if (capButton(1)) 
  {      
      failedCounter = false;

      // if the sensor is being held, but hasn't yet reached the full completion status of the process
      if(timer <= completeTime && completeCounter == false)
      {
        
        timer++; // increment timer variable
        
        CircuitPlayground.playTone(440,100);    // output a 440 Hz sound (A4) for a tenth of a second
      
        // But not too often.
        delay(DEBOUNCE); 
        
      }

      // once the process is complete - AKA the timer has reached completion time
      else if(completeCounter == false)
      {

        // play a jingle to show process is complete
        
        CircuitPlayground.playTone(294,100); // D4
        CircuitPlayground.playTone(392,100); // G4
        CircuitPlayground.playTone(494,100); // B4
        CircuitPlayground.playTone(587,100); // D5
        CircuitPlayground.playTone(494,100); // B4
        CircuitPlayground.playTone(587,100); // D5
        CircuitPlayground.playTone(784,400); // G5
        
        completeCounter = true; // set the counter to true to show the jingle has played and won't play again

        timer = 0;
      }
      
  }

  else
  {
    if(failedCounter == false && timer > 0)
    {
      // play a short jingle to show process failed

      CircuitPlayground.playTone(349,60); // F4
      CircuitPlayground.playTone(294,100); // D4

      failedCounter = true; //set the counter to true to show the jingle has played and won't play again
      
    }

    timer = 0;
    completeCounter = false;
    
  }
}
