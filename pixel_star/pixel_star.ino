#include "pixel_star.h"
#include "pixelstar.h"
#include "FFT_placa.h"
#include <FastLED.h>
#include <LEDMatrix.h>

// We have a fuckup between dotstar and fastled, needs to be fixed!
extern void loop_text( const char *string);

// This is a multi-framework on Lolin D32
#define INTERNAL_LED  13    // 

int function=0;
void setup(void)
{
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif
  Serial.begin(115200);
  setCpuFrequencyMhz(240);
  delay(1000);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(plusPin, INPUT_PULLUP);
  pinMode(minusPin, INPUT_PULLUP);
  pinMode(INTERNAL_LED, OUTPUT);
  digitalWrite(INTERNAL_LED,1);
  function = 0;
  if ( 0 == digitalRead(buttonPin) ) {
    Serial.printf("Starting FFT\n");
    function = 1;
  }
  else {
        Serial.printf("Starting PixelStar\n");
  }
  switch (function) {
    case 0:

      PIXEL_setup();
      break;
    case 1:
      PLACA_setup();
      break;
  }
}
void loop(void)
{
  switch (function) {
    case 0:
      PIXEL_loop();
      break;
    case 1:
      PLACA_loop();
      break;
  }
  // By holding down buttonPin,  the device restart, and a new function can be selected
  if ( 0 == digitalRead(buttonPin) ) {
    digitalWrite(INTERNAL_LED,0);
    if ( 0 == function ) {
      loop_text( "!");
    }
    else {
      FastLED.clear();
      leds.DrawLine(0, 0, 0, 5,CRGB::Red );
      FastLED.show();
    } 
     delay(1000);
     digitalWrite(INTERNAL_LED,1);
     ESP.restart();
  }

}