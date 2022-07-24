#include "pixel_star.h"
#include "esp32-hal-cpu.h"
//#include <fix_fft.h>   //to get input from audio source, connect audio output to Analog 0.
#include "FFT_interrupt.h"
#include "FFT_stuff.h"

const char compile_date[] = "v1.00 " __DATE__ " " __TIME__;


//<LedMatrix.h>
//https://github.com/AaronLiddiment/LEDMatrix


// For my dotstar



uint32_t maxFreqAmplitude = 3000;   // Change this value to adjust the sensitivity

double *data;
//char data[128], im[128];  // FFT Array Variables
uint32_t data_out[20];
uint32_t average[64];
uint32_t average_cnt = 0;
int color_command = 0;

uint32_t calc_avg(void)
{
    uint32_t avg = 0;
    for (int cnt = 0;cnt < mWidth; cnt++ ) {
        avg += data_out[cnt];        
    }
    avg /= mWidth;
    average[average_cnt] = avg;

    average_cnt++;
    if ( average_cnt>= 64) {
        average_cnt=0;
    }

    avg = 0;
    for ( int cnt = 0; cnt < 64; cnt++ ) {
        avg+=average[cnt];
    }
    return (avg/64);
}


uint32_t _max[64];
uint32_t _max_cnt=0;

// Släpande max över 64 mätningar
uint32_t calc_max(void)
{
    uint32_t val  = 0;
    for (int cnt = 0;cnt < mWidth; cnt++ ) {
        val = max(val,data_out[cnt]);
    }
    
    _max[_max_cnt] = val;

    _max_cnt++;
    if ( _max_cnt>= 64) {
        _max_cnt=0;
    }

    val  = 0;
    for ( int cnt = 0; cnt < 64; cnt++ ) {
        val = max(val,_max[cnt]);
    }
    return val;
}


//********************************************** Defining Custom RGB Palettes

// Position, Gval, Rval, Bval

DEFINE_GRADIENT_PALETTE(BlueToRed)
{
  0, 0, 0, 255,
  255,  255, 0, 0
};

//**********************************************

cLEDMatrix<mWidth, mHeight, mLayout> leds;
//cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;
CRGBPalette16 hue;
void PLACA_setup(void)
{
    FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, BGR>(leds[0], leds.Size());
    //  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds[0], leds.Size());
    FastLED.setBrightness(70);
    //Serial.begin(9600);

    leds.DrawLine(0, 0, 0, 5,CRGB::Lime );
    leds.DrawLine(1, 0, 1, 4,CRGB::Red );
    leds.DrawLine(2, 0, 2, 3,CRGB::Blue );
    FastLED.show();
    delay(3000);
    FastLED.clear();
    FastLED.show();
    //for(;;)    ;
    FFT_setup();
}

void PLACA_loop(void)
{
    // returns 64N
    data = myFFT_compute();

    if ( checkPin(plusPin) ) {
        if ( maxFreqAmplitude < 40000  ) {
             maxFreqAmplitude += 500;
        }
        while ( checkPin(plusPin) )
            ;
    }
    if ( checkPin(minusPin) ) {
        if ( maxFreqAmplitude > 500 ) {
             maxFreqAmplitude -= 500;
        }
        while ( checkPin(minusPin) )
            ;
    }

// What do we do now?
    //data[0]=data[1];        // FIX since we have a large DC-component, that messes up things
    // Just by accident that my width and 32B works...
    // Ignore first two to remove dc-bias)... This is specific to sampling frequencye and buffer size...
    for (int i = 0; i < mWidth; i++) {
        //data_out[i] = (data[i * 3] + data[i * 3 + 1] + data[i * 3 + 2])/3;
        data_out[i] = (data[i * 3+2] + data[i * 3 + 3] + data[i * 3 + 4] + data[i * 3 + 5]+ data[i * 3 + 5])/5;
    }
    
    for (int i = 0; i < mWidth; i++) {
        data_out[i] = map(data_out[i], 0, maxFreqAmplitude, 0, mHeight);
//        data_out[i] = map(data_out[i], 0, max_val, 0, mHeight);
    }
    FastLED.clear();

    for (int i = 0; i < mWidth; i++)
    {
        //leds.DrawLine(i, 0, i, data_out[i], ColorFromPalette((const CRGBPalette16 &) BlueToRed, 12 * i));
        leds.DrawLine(i, mHeight-data_out[i]-1, i, mHeight-1, ColorFromPalette((const CRGBPalette16 &) BlueToRed, 12 * i));
    }

    FastLED.show();

}
