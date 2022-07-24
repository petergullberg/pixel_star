
#ifndef FFT_PLACA_H_
#define FFT_PLACA_H_

#include <FastLED.h>
#include <LEDMatrix.h>

#define mHeight 8
#define mWidth 8
#define mSize (mWidth*mHeight)
#define mLayout HORIZONTAL_MATRIX
#define CLOCK_PIN   18
#define DATA_PIN    23


void PLACA_setup(void);
void PLACA_loop(void);
extern cLEDMatrix<mWidth, mHeight, mLayout> leds;

#endif // FFT_PLACA_H_