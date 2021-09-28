// NeoPixel test program --> Example code used, altered and written mostly by Samantha Bachalo

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    12

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  4

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 20 // Set BRIGHTNESS to about 1/5 (max = 255)


// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 ledBrightness)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)



//Variables

static const int ledNum = LED_COUNT; //NUMBER OF LEDs

int ledBrightness[ledNum];
int ledAdd[ledNum];

int maxBrightness = 45;
int wait = 5;
int delayB = 60;


void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.


  //Initializing arrays
    
  for(int i = 0; i < ledNum; i++)
  {
    ledBrightness[i] = ( (maxBrightness*(i+1)) / ledNum );    
    ledAdd[i] = -1;
  }

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
}

void loop() {
  
  int color;
  int ledBCounter;

  for (int i = 0; i < ledNum; i++)
  { 
    ledBCounter = ledBrightness[i];    
    
    if(ledBCounter >= maxBrightness) ledBCounter = maxBrightness;
  
    color = strip.ColorHSV(44000,50,ledBCounter);
    
    strip.setPixelColor(i,color);
  
    strip.show();
    delay(wait);
  
    ledBrightness[i] += ledAdd[i];
    
    if( (ledBrightness[i] >= delayB) || (ledBrightness[i] <= 0) ) ledAdd[i] *= -1;
  }  
  
}
