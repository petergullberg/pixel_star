#include "FFT_stuff.h"
#include "FFT_interrupt.h"
#define audioPin 34 // Left or right channel audio positive lead connects here



#include "arduinoFFT.h"

arduinoFFT FFT = arduinoFFT(); /* Create FFT object */
/*
These values can be changed in order to evaluate the functions
*/
const uint16_t samples = 256; //This value MUST ALWAYS be a power of 2
const double signalFrequency = 1000;
const double samplingFrequency = 5000;
const uint8_t amplitude = 100;
/*
These are the input and output vectors
Input vectors receive computed results from FFT
*/
double vReal[samples];
double vImag[samples];

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03


double *myFFT_compute(void)
{
    /* Build raw data */
    double cycles = (((samples-1) * signalFrequency) / samplingFrequency); //Number of signal cycles that the sampling will read
    uint16_t loopCnt = isrCnt;
    uint16_t localCnt;

    localCnt = isrCnt;
  for (uint16_t i = 0; i < samples; i++)
  {
    // Wait for ISR.
    while ( localCnt == isrCnt )
        ;
    vReal[i] = analogRead(audioPin);
    //vReal[i] =int8_t((amplitude * (sin((i * (twoPi * cycles)) / samples))) / 2.0);/* Build data with positive and negative values*/
    //vReal[i] = uint8_t((amplitude * (sin((i * (twoPi * cycles)) / samples) + 1.0)) / 2.0);/* Build data displaced on the Y axis to include only positive values*/
    vImag[i] = 0.0; //Imaginary part must be zeroed in case of looping to avoid wrong calculations and overflows

  }
#if 0
  for( uint16_t cnt = 0; cnt < samples; cnt++ ) {
    Serial.println(vReal[cnt]);
  }
  delay(1000);
  return vReal;
#endif
  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);	/* Weigh data */
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD); /* Compute FFT */
  FFT.ComplexToMagnitude(vReal, vImag, samples); /* Compute magnitudes */
//  PrintVector(vReal, samples>>1, SCL_PLOT);
  PrintVector(vReal, samples>>1, SCL_FREQUENCY);
  //double x = FFT.MajorPeak(vReal, samples, samplingFrequency);
  //while(1); /* Run Once */
  // delay(2000); /* Repeat after delay */

  return vReal;
}

void PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType)
{
  for (uint16_t i = 0; i < bufferSize; i++)
  {
    double abscissa;
    /* Print abscissa value */
    switch (scaleType)
    {
      case SCL_INDEX:
        abscissa = (i * 1.0);
	      break;
      case SCL_TIME:
        abscissa = ((i * 1.0) / samplingFrequency);
        break;
      case SCL_FREQUENCY:
        abscissa = ((i * 1.0 * samplingFrequency) / samples);
	      break;
    }
    if(scaleType!=SCL_PLOT)
    {
      Serial.print(abscissa, 6);
      if(scaleType==SCL_FREQUENCY)
        Serial.print("Hz");
      Serial.print(" ");
    }
    Serial.println(vData[i], 4);
  }
  Serial.println();
}

void FFT_setup(void)
{
    INT_setup(samplingFrequency);        // used by FFT sampler
}