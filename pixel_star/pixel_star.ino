#include "pixel_star.h"
#include "pixelstar.h"
#include "FFT_placa.h"

// This is a multi-framework on Lolin D32


int function=0;
void setup(void)
{
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif
  Serial.begin(115200);
  delay(100);
  Serial.printf("Starting\n");
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(plusPin, INPUT_PULLUP);
  pinMode(minusPin, INPUT_PULLUP);
// chose
  delay(100);
  
  if ( 0== digitalRead(buttonPin) ) {
    function = 1;
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
}