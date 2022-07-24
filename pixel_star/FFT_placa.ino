#include "pixel_star.h"
#include "esp32-hal-cpu.h"
#include <FastLED.h>
#include <LEDMatrix.h>
//#include <fix_fft.h>   //to get input from audio source, connect audio output to Analog 0.
#include "FFT_interrupt.h"
#include "FFT_stuff.h"

const char compile_date[] = "v1.00 " __DATE__ " " __TIME__;


//<LedMatrix.h> 
//https://github.com/AaronLiddiment/LEDMatrix


// For my dotstar

#define mHeight 8
#define mWidth 8
#define mSize (mWidth*mHeight)
#define mLayout HORIZONTAL_MATRIX
#define CLOCK_PIN   18
#define DATA_PIN    22

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
    Serial.begin(115200);
    delay(200);
    setCpuFrequencyMhz(240);
    Serial.printf("Starting\n");
    FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, BGR>(leds[0], leds.Size());
    //  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds[0], leds.Size());
    FastLED.setBrightness(70);
    //Serial.begin(9600);

    leds.DrawLine(0, 0, 0, 5,CRGB::Lime );
    leds.DrawLine(1, 0, 1, 4,CRGB::Red );
    leds.DrawLine(2, 0, 2, 3,CRGB::Blue );
    delay(1000);
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
    data[0]=data[1];        // FIX since we have a large DC-component, that messes up things
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
        leds.DrawLine(i, 0, i, data_out[i], ColorFromPalette((const CRGBPalette16 &) BlueToRed, 12 * i));
    }

    FastLED.show();

}


#if 0
/**
    M5StickC_AudioVisLedApp:
    This application has been developed to use an M5StickC device (ESP32)
    as an audio sampling and visualization device. It samples audio data
    from the built-in microphone using i2s. The sampled data is transformed
    into the frequency domain using the arduinoFFT library.
    Copyright (C) 2021 by Ernst Sikora
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Arduino.h>

//#include <M5StickC.h>
#include <driver/i2s.h>

#include <math.h>

#include <FastLED.h>

#include <arduinoFFT.h>

#include <fix_fft.h>
// For my dotstar
#define DATA_PIN    22
#define CLOCK_PIN   18

/* ----- General constants ----- */

const uint16_t kSampleRate = 44100; // Unit: Hz

/* ----- FFT constants ----- */

typedef float fftData_t;

const uint8_t kFFT_SampleCountLog2 = 11;

const uint16_t kFFT_SampleCount = 1 << kFFT_SampleCountLog2;

const fftData_t kFFT_SampleCountInv = 1.0f / kFFT_SampleCount;

const fftData_t kFFT_SamplingFreq = (fftData_t) kSampleRate;

const uint16_t kFFT_FreqBinCount = kFFT_SampleCount / 2;

const float kFFT_FreqStep = kFFT_SamplingFreq / kFFT_SampleCount;

/* ----- FFT variables ----- */

fftData_t fftDataReal_[kFFT_SampleCount] = {0.0};

fftData_t fftDataImag_[kFFT_SampleCount] = {0.0};

fftData_t magnitudeSpectrumAvg_[kFFT_FreqBinCount] = {0};

ArduinoFFT<fftData_t> fft_ = ArduinoFFT<fftData_t>(fftDataReal_, fftDataImag_, kFFT_SampleCount, kFFT_SamplingFreq); // Create FFT object

/* ----- i2s hardware constants ----- */

const i2s_port_t kI2S_Port = I2S_NUM_0;

const int kI2S_PinClk = 0;

const int kI2S_PinData = 34;

/* ----- i2s constants ----- */

const i2s_bits_per_sample_t kI2S_BitsPerSample = I2S_BITS_PER_SAMPLE_16BIT;

const uint8_t kI2S_BytesPerSample = kI2S_BitsPerSample / 8;

const uint16_t kI2S_ReadSizeBytes = kFFT_SampleCount * kI2S_BytesPerSample;

const uint16_t kI2S_BufferSizeSamples = 1024;

const uint16_t kI2S_BufferSizeBytes = kI2S_BufferSizeSamples * kI2S_BytesPerSample;

const uint16_t kI2S_BufferCount = (3 * kFFT_SampleCount) / (2 * kI2S_BufferSizeSamples);

const uint8_t kI2S_BufferCountPerFFT = kFFT_SampleCount / kI2S_BufferSizeSamples;

const int kI2S_QueueLength = 16;

/* ----- i2s variables ----- */

int16_t micReadBuffer_[kFFT_SampleCount] = {0};

QueueHandle_t pI2S_Queue_ = nullptr;

/* ----- Fastled constants ----- */

//PeGe Not used
const uint8_t kPinLedStrip = 32; // M5StickC grove port, yellow cable

const uint8_t kNumLeds = 64;

const uint8_t kLedStripBrightness = 50;

/* ----- Fastled variables ----- */

// LED strip controller
CRGB ledStrip_[kNumLeds];

// Frequency bands
// Source: https://www.teachmeaudio.com/mixing/techniques/audio-spectrum
//
// Sub-bass:       20-60 Hz
// Bass:           60-250 Hz
// Low midrange:   250-500 Hz
// Midrange:       500-2000 Hz
// Upper midrange: 2000-4000 Hz
// Presence:       4000-6000 Hz
// Brilliance:     6000-20000 Hz

// 20Hz, 25Hz, 31.5Hz, 40Hz, 50Hz, 63Hz, 80Hz, 100Hz, 125Hz 160Hz, 200Hz, 250Hz, 315Hz, 400Hz, 500Hz, 630Hz, 800Hz, 1kHz, 1.25kHz, 1.6kHz, 2kHz, 2.5kHz, 3.15kHz, 4kHz, 5kHz, 6.3kHz, 8kHz, 10kHz, 12.5kHz, 16kHz, 20kHz

//const uint8_t kFreqBandCount = 7;
//const float kFreqBandStartHz = 20;
//const float kFreqBandEndHz[kFreqBandCount] = {60, 250, 500, 2000, 4000, 6000, 20000};

const uint8_t kFreqBandCount = 20;

const float kFreqBandStartHz = 20;

// Index:                                         0     1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18      19
const float kFreqBandEndHz[kFreqBandCount] = {   30,   50,   75,  100,  140,  180,  225,  270,  350,  440,  550,  700,  900, 1100, 1400, 1800, 2200, 2800, 3550,  18000};
const float kFreqBandAmp[kFreqBandCount]   = { 0.15f, 0.3f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.3f, 0.4f, 0.4f, 0.4f, 0.5f, 0.8f,    1,    1,    1,    1,    1,   0.3f};

fftData_t sensitivityFactor_ = 1;
const float kSensitivityFactorMax = 1000.0f;

float magnitudeBandMax_[kFreqBandCount] = { 0.0f };

/* Start indices, end indices and normalization factors for each frequency band
    The indices relate to the frequency bins resulting from the FFT */
uint16_t freqBandBinIdxStart_[kFreqBandCount] = { 0 };
uint16_t freqBandBinIdxEnd_[kFreqBandCount] = { 0 };
uint16_t freqBandBinCount_[kFreqBandCount] = { 0 };

/* ----- Beat detection constants and variables ----- */

const uint8_t kBeatDetectBand = 3;

const float kBeatThreshold = 4.0f;

float beatHist_[3] = {0.0f};

uint8_t beatVisIntensity_ = 0;


bool setupI2Smic()
{
    esp_err_t i2sErr;

    // i2s configuration for sampling 16 bit mono audio data
    //
    // Notes related to i2s.c:
    // - 'dma_buf_len', i.e. the number of samples in each DMA buffer, is limited to 1024
    // - 'dma_buf_len' * 'bytes_per_sample' is limted to 4092
    // - 'I2S_CHANNEL_FMT_ONLY_RIGHT' means "mono", i.e. only one channel to be received via i2s
    //   In the M5StickC microphone example 'I2S_CHANNEL_FMT_ALL_RIGHT' is used which means two channels.
    //   Afterwards, i2s_set_clk is called to change the DMA configuration to just one channel.
    //
    i2s_config_t i2sConfig = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
        .sample_rate = kSampleRate,
        .bits_per_sample = kI2S_BitsPerSample,
        .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
//PEGE FIX
//        .communication_format = I2S_COMM_FORMAT_I2S,
        .communication_format = I2S_COMM_FORMAT_I2S
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = kI2S_BufferCount,
        .dma_buf_len = kI2S_BufferSizeSamples
    };

    i2sErr = i2s_driver_install(kI2S_Port, &i2sConfig, kI2S_QueueLength, &pI2S_Queue_);

    if (i2sErr)
    {
        Serial.printf("Failed to start i2s driver. ESP error: %s (%x)", esp_err_to_name(i2sErr), i2sErr);
        return false;
    }

    if (pI2S_Queue_ == nullptr)
    {
        log_e("Failed to setup i2s event queue.");
        return false;
    }

    // Configure i2s pins for sampling audio data from the built-in microphone of the M5StickC
    i2s_pin_config_t i2sPinConfig = {
        .bck_io_num = I2S_PIN_NO_CHANGE,
        .ws_io_num = kI2S_PinClk,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = kI2S_PinData
    };

    i2sErr = i2s_set_pin(kI2S_Port, &i2sPinConfig);

    if (i2sErr)
    {
        log_e("Failed to set i2s pins. ESP error: %s (%x)", esp_err_to_name(i2sErr), i2sErr);
        return false;
    }

    return true;
}

bool setupSpectrumAnalysis()
{
    bool success = true;

    // Variables for bin indices and bin count belonging to the current frequency band
    uint16_t binIdxStart; // Index of the first frequency bin of the current frequency band
    uint16_t binIdxEnd;   // Index of the last frequency bin of the current frequency band
    
    // Set bin index for the start of the first frequency band
    binIdxStart = ceilf( kFreqBandStartHz / kFFT_FreqStep);

    // Compute values for all frequency bands
    for (uint8_t bandIdx = 0; bandIdx < kFreqBandCount; bandIdx++)
    {
        // Store index of first frequency bin of current band
        if ( binIdxStart < kFFT_FreqBinCount )
        {
            freqBandBinIdxStart_[bandIdx] = binIdxStart;
        }
        else
        {
            freqBandBinIdxStart_[bandIdx] = 0;
            
            success = false;

            log_e("Failed to set start bin index for frequency band no. %d", bandIdx);
        }
        
        // Compute index of last frequency bin of current band
        binIdxEnd = ceilf( kFreqBandEndHz[bandIdx] / kFFT_FreqStep ) - 1;
        
        if ( binIdxEnd < kFFT_FreqBinCount)
        {
            freqBandBinIdxEnd_[bandIdx] = binIdxEnd;
        }
        else
        {
            freqBandBinIdxEnd_[bandIdx] = 0;
            binIdxEnd = kFFT_FreqBinCount - 1;

            success = false;

            log_e("Failed to set end bin index for frequency band no. %d", bandIdx);
        }

        // Compute bin count for current band
        freqBandBinCount_[bandIdx] = binIdxEnd - binIdxStart + 1;

        // Set binIdxStart for next band
        binIdxStart = binIdxEnd + 1;

        log_d("Bins in band %d: %d to %d. Number of bins: %d.",
            bandIdx,
            freqBandBinIdxStart_[bandIdx], freqBandBinIdxEnd_[bandIdx],
            freqBandBinCount_[bandIdx]);
    }

    return success;
}

void setupLedStrip()
{

    // My DotStar
    FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, BGR>(kPinLedStrip, kNumLeds);
    //FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, BGR>(kPinLedStrip, kNumLeds);
    //FastLED.addLeds<NEOPIXEL, kPinLedStrip>(ledStrip_, kNumLeds);
    FastLED.clear();
    FastLED.setBrightness(kLedStripBrightness);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 450); // Set maximum power consumption to 5 V and 450 mA
    ledStrip_[0].setHSV(60, 255, 255);
    FastLED.show();
}

void setup() {
#if 0
    M5.begin();
    M5.Lcd.setRotation(1);
    M5.Lcd.fillScreen(BLACK);

    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(WHITE, BLUE);
    M5.Lcd.println("Audio Vis");
#endif
    Serial.printf("Audio Vis");
    setupI2Smic();

    setupSpectrumAnalysis();

    setupLedStrip();

    Serial.printf("Setup successfully completed.");

    Serial.printf("portTICK_PERIOD_MS: %d", portTICK_PERIOD_MS);

    delay(1000);
}

unsigned long timeReadLastMicros_ = 0;

uint8_t userTrigger_ = 0;

uint8_t cycleNr_ = 0;

float maxCurrent_ = 0.0f;

/*
uint16_t testSignalFreqFactor_ = 0;
*/

void FFT_loop() {

    esp_err_t i2sErr = ESP_OK;

    size_t i2sBytesRead = 0;

    // Store time stamp for debug output
    unsigned long timeBeforeReadMicros = micros();

    // Note: If the I2S DMA buffer is empty, 'i2s_read' blocks the current thread until data becomes available
    i2sErr = i2s_read(kI2S_Port, micReadBuffer_, kI2S_ReadSizeBytes, &i2sBytesRead, 100 / portTICK_PERIOD_MS);

    // Get timestamp after reading
    unsigned long timeAferReadMicros = micros();

    // Compute read duration for debug output
    unsigned long timeInRead = timeAferReadMicros - timeBeforeReadMicros;

    // Compute duration since last read
    unsigned long timeBetweenRead = timeAferReadMicros - timeReadLastMicros_;

    // Store timestamp for next computation
    timeReadLastMicros_ = timeAferReadMicros;

    // Check i2s error state after reading
    if (i2sErr)
    {
        Serial.printf("i2s_read failure. ESP error: %s (%x)", esp_err_to_name(i2sErr), i2sErr);
    }

    // Check whether right number of bytes has been read
    if (i2sBytesRead != kI2S_ReadSizeBytes)
    {
        Serial.printf("i2s_read unexpected number of bytes: %d", i2sBytesRead);
    }

    // Analyse event queue to check whether i2s is working correctly
    i2s_event_t i2sEvent = {};
    uint8_t i2sEventRxDoneCount = 0;

    uint8_t i2sMsgCount = uxQueueMessagesWaiting(pI2S_Queue_);
    
    Serial.printf("Number of I2S events waiting in queue: %d", i2sMsgCount);

    // Iterate over all events in the i2s event queue
    for (uint8_t i = 0; i < i2sMsgCount; i++)
    {
        // Take next event from queue
        if ( xQueueReceive(pI2S_Queue_, (void*) &i2sEvent, 0) == pdTRUE )
        {
            switch (i2sEvent.type)
            {
                case I2S_EVENT_DMA_ERROR:
                    Serial.printf("I2S_EVENT_DMA_ERROR");
                    break;
                
                case I2S_EVENT_TX_DONE:
                    Serial.printf("I2S_EVENT_TX_DONE");
                    break;

                // Count the number of "RX done" events
                case I2S_EVENT_RX_DONE:
                    Serial.printf("I2S_EVENT_RX_DONE");
                    i2sEventRxDoneCount += 1;
                    break;

                case I2S_EVENT_MAX:
                    Serial.printf("I2S_EVENT_MAX");
                    break;
            }
        }
    }

    // If there are more RX done events in the queue than expected, probably data processing takes too long
    if (i2sEventRxDoneCount > kI2S_BufferCountPerFFT)
    {
        Serial.printf("Frame loss. Number of I2S_EVENT_RX_DONE events is: %d", i2sEventRxDoneCount);    
    }
    else
    {
        if (i2sEventRxDoneCount < kI2S_BufferCountPerFFT)
        {
            Serial.printf("Configuration error? Number of I2S_EVENT_RX_DONE events is: %d", i2sEventRxDoneCount);    
        }
    }

    Serial.printf("Read duration [µs]: %d. Duration since last read [µs]: %d", timeInRead, timeBetweenRead);

    // Store start time of processing to compute duration later on
    unsigned long timeStartMicros = micros();

    // Compute sum of the current sample block
    int32_t blockSum = micReadBuffer_[0];

    for (uint16_t i = 1; i < kFFT_SampleCount; i++)
    {
        blockSum += micReadBuffer_[i];
    }

    // Compute average value for the current sample block
    int16_t blockAvg = blockSum / kFFT_SampleCount;

    /*
    // Increment factor for test signal frequency
    if ( slotNr_ == 0 )
    {
        testSignalFreqFactor_ += 1;

        if ( testSignalFreqFactor_ > kFFT_FreqBinCount )
        {
            testSignalFreqFactor_ = 1;
        }
    }
    */

    // Initialize fft input data
    for (uint16_t i = 0; i < kFFT_SampleCount; i++)
    {
        // Corrected input value: Subtract the block average from each sample in order remove the DC component
        int16_t v = micReadBuffer_[i] - blockAvg;

        // Constant for normalizing int16 input values to floating point range -1.0 to 1.0
        const fftData_t kInt16MaxInv = 1.0f / __INT16_MAX__;

        // Input value in floating point representation
        fftData_t r;

        // Compute input value for FFT
        r = kInt16MaxInv * v;

        /*
        // Generate test signal
        const float k2Pi = 6.2831853f;
        const float k2PiSampleCountInv = k2Pi * kFFT_SampleCountInv;
        
        r = sinf( k2PiSampleCountInv * (testSignalFreqFactor_ * i) );
        */
        
        // Store value in FFT input array
        fftDataReal_[i] = r;
        fftDataImag_[i] = 0.0f;
    }

    //fft_.windowing(FFTWindow::Hamming, FFTDirection::Forward);

//PEGE FIX
//    fft_.compute(FFTDirection::Forward);
    fft_.Compute(FFT_FORWARD);
     
    
    fftData_t magnitudeSum = 0;

    // Compute magnitude value for each frequency bin, i.e. only first half of the FFT results
    for (uint16_t i = 0; i < kFFT_FreqBinCount; i++)
    {
        float magValNew = sqrtf( fftDataReal_[i] * fftDataReal_[i] + fftDataImag_[i] * fftDataImag_[i] );
        
        // Update the averaged spectrum using the current values
        const float w1 = 16.0f / 128.0f;
        const float w2 = 1 - w1;

        // Compute low pass filtered magnitude for each frequency bin
        magnitudeSpectrumAvg_[i] = magValNew * w1 + magnitudeSpectrumAvg_[i] * w2;
        
        // Compute overall sum of all (low pass filtered) frequency bins
        magnitudeSum += magnitudeSpectrumAvg_[i];
    }

    // Compute magnitude for each frequency band as maximum over all contained frequency bins
    float magnitudeBand[kFreqBandCount] = { 0.0f };

    float magnitudeBandWeightedMax = 0.0f;

    for (uint8_t bandIdx = 0; bandIdx < kFreqBandCount; bandIdx++)
    {
        // Interate over all frequency bins assigned to the frequency band
        for (uint16_t binIdx = freqBandBinIdxStart_[bandIdx]; binIdx <= freqBandBinIdxEnd_[bandIdx]; binIdx++)
        {
            // Apply maximum norm to the frequency bins of each frequency band
            if ( magnitudeSpectrumAvg_[binIdx] > magnitudeBand[bandIdx] )
                magnitudeBand[bandIdx] = magnitudeSpectrumAvg_[binIdx];
        }

        float magnitudeBandWeighted = magnitudeBand[bandIdx] * kFreqBandAmp[bandIdx];

        // Compute maximum magnitude value for each frequency band
        if ( magnitudeBand[bandIdx] > magnitudeBandMax_[bandIdx] )
        {
            magnitudeBandMax_[bandIdx] = magnitudeBand[bandIdx];
        }

        // Compute maximum magnitude value across all frequency bands
        if ( magnitudeBandWeighted > magnitudeBandWeightedMax )
        {
            magnitudeBandWeightedMax = magnitudeBandWeighted;
        }
    }

    // Update the sensitivity factor
    const float s1 = 8.0f / 1024.0f;
    const float s2 = 1.0f - s1;
    sensitivityFactor_ =  min( (250.0f / magnitudeBandWeightedMax) * s1 + sensitivityFactor_ * s2, kSensitivityFactorMax );

    // ----- Beat detection -----

    // Maintain history of last three magnitude values of the bass band
    beatHist_[0] = beatHist_[1];
    beatHist_[1] = beatHist_[2];
    beatHist_[2] = magnitudeBand[kBeatDetectBand] * kFreqBandAmp[kBeatDetectBand] * sensitivityFactor_;

    float diff1 = beatHist_[1] - beatHist_[0];
    float diff2 = beatHist_[2] - beatHist_[1];

    // Detect magnitude peak
    if ( ((diff1 >= kBeatThreshold) && (diff2 < 0)) || ((diff1 > 0) && (diff2 <= -kBeatThreshold)) )
    {
        beatVisIntensity_ = 250;
    }
    else {
        if ( beatVisIntensity_ >= 25 )
            beatVisIntensity_ -= 25;
    }

    // ----- Update the Led strip -----

    if (kNumLeds <= 2*kFreqBandCount + 4)
    {
        // Show beat detection at the beginning of the strip
        const uint8_t numBassLeds = (kNumLeds - kFreqBandCount) / 2;

        for (int i = 0; i < numBassLeds; i++)
        {
            ledStrip_[i].setHSV( 250, 255, beatVisIntensity_ );
        }

        // Show frequency intensities on the remaining Leds
        const uint8_t colorStart = 30;
        const uint8_t colorEnd   = 210;
        const uint8_t colorStep  = (colorEnd - colorStart) / kFreqBandCount;

        for (int k = 0; k < kFreqBandCount; k++)
        {
            uint8_t color = colorStart + k * colorStep;
            uint8_t lightness = min( int(magnitudeBand[k] * kFreqBandAmp[k] * sensitivityFactor_), 255);
            
            ledStrip_[k+numBassLeds].setHSV(color, 255, lightness);
        }

        // Show beat detection at the beginning of the strip
        for (int i = numBassLeds + kFreqBandCount; i < kNumLeds; i++)
        {
            ledStrip_[i].setHSV( 250, 255, beatVisIntensity_ );
        }
    }
    else
    {
        // Show beat detection at the beginning of the strip
        const uint8_t numBassLeds = (kNumLeds - 2 * kFreqBandCount) / 2;

        for (int i = 0; i < numBassLeds; i++)
        {
            ledStrip_[i].setHSV( 250, 255, beatVisIntensity_ );
        }

        // Show frequency intensities on the remaining Leds
        const uint8_t colorStart = 30;
        const uint8_t colorEnd   = 210;
        const uint8_t colorStep  = (colorEnd - colorStart) / kFreqBandCount;

        for (int k = 0; k < kFreqBandCount; k++)
        {
            uint8_t color = colorStart + k * colorStep;
            uint8_t lightness = min( int(magnitudeBand[k] * kFreqBandAmp[k] * sensitivityFactor_), 255);
            
            ledStrip_[numBassLeds + k].setHSV(color, 255, lightness);

            ledStrip_[numBassLeds + 2*kFreqBandCount - k - 1].setHSV(color, 255, lightness);
        }

        // Show beat detection at the beginning of the strip
        for (int i = numBassLeds + 2*kFreqBandCount; i < kNumLeds; i++)
        {
            ledStrip_[i].setHSV( 250, 255, beatVisIntensity_ );
        }
    }
    
    FastLED.show();

    // Determine current consumption from USB
    float vBusCurrent = 1; //M5.Axp.GetVBusCurrent();

    if (vBusCurrent > maxCurrent_)
    {
        maxCurrent_ = vBusCurrent;
    }

    // Determine current consumption from battery
    float batCurrent = 0.5f * 1; //M5.Axp.GetIdischargeData();

    if (batCurrent > maxCurrent_)
    {
        maxCurrent_ = batCurrent;
    }

    // Show current consumption on display
    if (cycleNr_ == 1)
    {
//        M5.Lcd.setTextSize(2);
//        M5.Lcd.setTextColor(WHITE, BLACK);
        int16_t cursorX;// = M5.Lcd.getCursorX();
        int16_t cursorY;// = M5.Lcd.getCursorY();
//        M5.Lcd.printf("%03.0f mA", maxCurrent_);
//        M5.Lcd.setCursor(cursorX, cursorY);

        maxCurrent_ = 0;
    }

    // If user presses ButtonA, print the current frequency spectrum to serial
//    M5.BtnA.read();

    // Compute duration of processing
    unsigned long timeEndMicros = micros();
    unsigned long timeDeltaMicros = timeEndMicros - timeStartMicros;

    if (userTrigger_ == 0)
    {
        // PeGe!!! no keys yet
        if ( 0 /*M5.BtnA.isPressed()*/ )
        {
            userTrigger_ = 5;
        }
    }
    else {
        if (userTrigger_ == 1)
        {
            Serial.printf("AXP192: VBus current: %.3f mA\n", 1 /*M5.Axp.GetVBusCurrent()*/);
            Serial.printf("FastLed Brightness: %d %%\n", FastLED.getBrightness());
            
            Serial.printf("Processing time: %d\n", timeDeltaMicros);
            Serial.printf("Sensitivity: %.1f\n", sensitivityFactor_);

            for (uint8_t i = 0; i < kFreqBandCount; i++)
            {
                Serial.printf("to %.0f Hz: %.2f (Max: %.2f)\n", kFreqBandEndHz[i], magnitudeBand[i], magnitudeBandMax_[i]);
            }
        }
        userTrigger_ -= 1;
    }

    float nf;

    if (fabs(magnitudeBand[1]) < 0.001f)
    {
        nf = 1.0f;
    }
    else
    {
        nf = 1.0f / magnitudeBand[1];
    }

    Serial.printf("0:%04.2f 1:%04.2f 2:%04.2f 3:%04.2f 4:%04.2f 5:%04.2f 6:%04.2f 7:%04.2f 8:%04.2f 9:%04.2f 10:%04.2f 11:%04.2f 12:%04.2f 13:%04.2f 14:%04.2f 15:%04.2f 16:%04.2f 17:%04.2f 18:%04.2f 19:%04.2f Sum:%05.1f Sens: %04.1f t: %d",
        magnitudeBand[0] * nf,
        magnitudeBand[1] * nf,
        magnitudeBand[2] * nf,
        magnitudeBand[3] * nf,
        magnitudeBand[4] * nf,
        magnitudeBand[5] * nf,
        magnitudeBand[6] * nf,
        magnitudeBand[7] * nf,
        magnitudeBand[8] * nf,
        magnitudeBand[9] * nf,
        magnitudeBand[10] * nf,
        magnitudeBand[11] * nf,
        magnitudeBand[12] * nf,
        magnitudeBand[13] * nf,
        magnitudeBand[14] * nf,
        magnitudeBand[15] * nf,
        magnitudeBand[16] * nf,
        magnitudeBand[17] * nf,
        magnitudeBand[18] * nf,
        magnitudeBand[19] * nf,
        magnitudeSum,
        sensitivityFactor_,
        timeDeltaMicros);

    cycleNr_ = (cycleNr_ + 1) % 20;

}
#endif
