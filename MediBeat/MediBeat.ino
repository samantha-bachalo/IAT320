
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>


// General Variables

int vMotor = A1; // Vibration motor pin
int timer = 600; // 100 BPM = 1 beat per every 600 ms
int soundLength = 75; // Each sound plays for 75 milliseconds.
int soundTone = 784; // The tone (frequency in Hz) of the beep --> G5
int mode = 0; // Mode switcher --> 0 = light + vibration + sound, 1 = vibration + sound
bool power = false; // Power controlling variable --> false = power is off, true = power is on
bool togglePower = true; // Toggle switch variable for power --> turns buttons into toggle buttons
bool toggleMode = true; // Toggle switch variable for mode --> turns buttons into toggle buttons



// Metronome Timer Variables

long lightTimer = 0;
long vibrationTimer = 0;



// Debounce Variables

bool powerButtonState = false;
bool modeButtonState = false;
int modeCounter = 0; // Debounce variable for mode
int powerCounter = 0; // Debounce variable for power
int buttonCountMax = 50; // The amount of times a return statement happens in order to switch status of button



void setup() 
{
  // Initialize serial.
  Serial.begin(9600); 
  
  // Initialize Circuit Playground library.
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(80); // Set lights to max brightness

  //Initialize the outputs
  pinMode(vMotor, OUTPUT); // Motor and MOSFET pin --> only needs to be digital (on/off)
}



void loop() 
{ 

  int currentTime = millis();

  checkButtons();
  

  // POWER ON / OFF
  
  if( (powerButtonState == true) && (power == false) && (togglePower == true) ) 
  {
    power = true;    // Turn the metronome ON
    togglePower = false;
    Serial.println("ON");
  }
  
  if( (powerButtonState == true) && (power == true) && (togglePower == true) ) 
  {
    power = false;    // Turn the metronome OFF
    togglePower = false;
    Serial.println("OFF");
    for(int i = 0; i < 10; i++) CircuitPlayground.clearPixels();                          // Turn OFF all lights
    digitalWrite(vMotor, LOW);                                                            // Turn OFF vibration motor
  }

  if(powerButtonState == false) togglePower = true;



  // SWITCH MODE

  if( (modeButtonState == true) && (power == true) && (toggleMode == true) && (mode == 0) ) 
  {
    mode = 1;                                                                             // Switch to the lights mode
    toggleMode = false;
    Serial.println("SWITCH TO MODE 1");
  }
  
  if( (modeButtonState == true) && (power == true) && (toggleMode == true) && (mode == 1) ) 
  {
    mode = 0;                                                                             // Switch back to NO lights mode
    toggleMode = false;
    Serial.println("SWITCH TO MODE 0");
  }

  if(modeButtonState == false) toggleMode = true;



  // Lights + Vibration + Sound Mode
  
  if( (power == true) && (mode == 0) && (currentTime > lightTimer) && (currentTime > vibrationTimer) )
  {

    lightTimer = currentTime + timer;                                                     // Everything happens at 100 BPM
                                                                                          
    for(int i = 0; i < 10; i++) CircuitPlayground.setPixelColor(i, 200, 200, 200);        // Turn ON all lights (from 0-9) with a bright white colour
    digitalWrite(vMotor, HIGH);                                                           // Turn ON vibration motor
    
    CircuitPlayground.playTone(soundTone, soundLength);                                         // Play tone

    for(int i = 0; i < 10; i++) CircuitPlayground.clearPixels();                          // Turn OFF all lights for flash effect
    digitalWrite(vMotor, LOW);                                                            // Turn OFF vibration motor

    Serial.println("Mode 1");
    
  }


  // Vibration + Sound Mode
  
  if( (power == true) && (mode == 1) && (currentTime > vibrationTimer) && (currentTime > lightTimer) )
  {
    
    vibrationTimer = currentTime + timer;                                                  // Everything happens at 100 BPM    
                                                  
    for(int i = 0; i < 10; i++) CircuitPlayground.clearPixels();                           // Makes sure all lights are off         

    digitalWrite(vMotor, HIGH);                                                            // Turn ON vibration motor
    
    CircuitPlayground.playTone(soundTone, soundLength);                                          // Play tone
    
    digitalWrite(vMotor, LOW);                                                             // Turn OFF vibration motor

    Serial.println("Mode 0");
        
  }


  
}


// Debounce code --> saves current state, checks if it has been changed a set amount of times in a row, and then changes state

void checkButtons()
{

  // POWER
  
    int currentPowerButtonState = CircuitPlayground.rightButton();
    
    if( currentPowerButtonState != powerButtonState )
    {
      powerCounter++;
      if( powerCounter >= buttonCountMax ) powerButtonState = currentPowerButtonState;
    }
    
    else powerCounter = 0;


  // MODE

    int currentModeButtonState = CircuitPlayground.leftButton();
    
    if( currentModeButtonState != modeButtonState )
    {
      modeCounter++;
      if( modeCounter >= buttonCountMax ) modeButtonState = currentModeButtonState;
    }
    
    else modeCounter = 0;
  
}
