// PISKEL stars

// Peter Gullberg 2018-02-08
// Trinket pro 5V/16Mhz, using serial upload
// A Adafruit dotstar 8x8 pixel LCD

/*
 * Have some kind of timing/memory bug, that 
 * Needs to be investigated.
 */

#include <stdint.h>
#include <Adafruit_DotStar.h>
#include "pixel_star.h"
// I have in mind to also support neopixel as well, that would be "clever"
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#include <SHT21.h>  // include SHT21 library
#include "Wire.h"
// PINS are SCL/SDA
// on ESP32
SHT21 sht;
void sensor_setup()
{
  //Wire.begin(I2C_SDA, I2C_SCL);
  Wire.begin(21, 22);		// begin Wire(I2C)
  Serial.printf("initalizing I2C\n");
}

int sensor_read(float *temp, float *humidity)
{
  *temp = sht.getTemperature();  // get temp from SHT 
  *humidity = sht.getHumidity(); // get temp from SHT

  Serial.print("Temp: ");			// print readings
  Serial.print(*temp);
  Serial.print("\t Humidity: ");
  Serial.println(*humidity);
  delay(85);	// min delay for 14bit temp reading is 85ms
  return 1;
}

void glcd_move_left( uint8_t clear_last_col );


//https://www.piskelapp.com/p/agxzfnBpc2tlbC1hcHByEwsSBlBpc2tlbBiAgMDdjNODCww/edit
//Edit your stuff in the piskelapp, and then export from as "Other" C-code. Then copy / paste into the source
// Make sure you have the correct size of the image (8x8 piskels)
#include "./image_data.h"   // All piskel images... (today assume 8x8 pixels)
// And YES, I do declare the variables in the header file :)

// WIDTH AND HEIGHT must be 8, entire program is hardcoded for these paramters!
// I have an urge to increase, so I can have more realistic images, but that's for the future
#define FRAME_WIDTH 8
#define FRAME_HEIGHT 8
#define NUMPIXELS (FRAME_WIDTH * FRAME_HEIGHT) // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define CLOCKPIN   18
#define DATAPIN    23
Adafruit_DotStar strip = Adafruit_DotStar(
                           NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);

uint32_t color = 0x0F0000;      // 'On' color (starts red)



/* LOOP */
#define  NORM_INTENSITY 2
#define FRAMES(x) (sizeof(  x ) / (sizeof(uint32_t) * 64))
// Intensity divisions of two
void show_piskel( uint32_t *ptr, int nFrames, uint32_t _delay, uint32_t _clear_delay, uint8_t intensity)
{
  uint32_t color;
  byte red, green, blue;
  for (int frame = 0; frame < nFrames; frame++ ) {
    // Show first frame
    for (int height = 0; height < FRAME_HEIGHT; height++) {
      for (int width = 0; width < FRAME_WIDTH; width++) {
        color = pgm_read_dword_near(ptr + (frame * 64) + (height * FRAME_HEIGHT) + width );
        // xBGR - image
        // xGBR - dotstar

        blue = ((color & 0x00FF0000) >> 16);
        green = ((color & 0x0000FF00) >> 8);
        red = (color & 0x000000FF);

        // set brightness
        red = red >> intensity;
        green = green >> intensity;
        blue = blue >> intensity;
#if 1   // gamma correction
        red = pgm_read_byte(&gamma8[red]),
        green = pgm_read_byte(&gamma8[green]),
        blue = pgm_read_byte(&gamma8[blue]);
#endif

        strip.setPixelColor((height * FRAME_HEIGHT) + (FRAME_WIDTH - width - 1), red,green,blue);

      }
    }
    if ( 0 != intensity ) {
      strip.show();
    }
    delay( _delay );    // Show for _delay
    
    if ( _clear_delay ) {   // Clear and delay?
      clearPiskel(1);
      delay( _clear_delay );
    }
  }
}


void piskel_write_col( uint32_t *ptr, uint8_t width,uint8_t dest_width, uint8_t intensity)
{
  uint32_t color;
  byte red, green, blue;
  int frame = 0;

  for (int height = 0; height < FRAME_HEIGHT; height++) {
    color = pgm_read_dword_near(ptr + (frame * 64) + (height * FRAME_HEIGHT) + width );
    // xBGR - image
    // xGBR - dotstar

    blue = ((color & 0x00FF0000) >> 16);
    green = ((color & 0x0000FF00) >> 8);
    red = (color & 0x000000FF);

    // set brightness
    red = red >> intensity;
    green = green >> intensity;
    blue = blue >> intensity;
#if 1   // gamma correction
      red = pgm_read_byte(&gamma8[red]),
      green = pgm_read_byte(&gamma8[green]),
      blue = pgm_read_byte(&gamma8[blue]);
#endif

      strip.setPixelColor((height * FRAME_HEIGHT) + (FRAME_WIDTH - dest_width - 1), red,green,blue);

    }
    if ( 0 != intensity ) {
      strip.show();
    }
    //delay( _delay );    // Show for _delay
}
void piskel_scroll_left( uint32_t *ptr, uint8_t intensity)
{
  for (int width = 0; width < FRAME_WIDTH; width++) {
    piskel_write_col( ptr, width, FRAME_WIDTH-1, intensity);
    glcd_move_left( true );
    delay(100);    
  }
}


void loop_pixel(void)
{
  //  xGRB
  uint32_t color = 0x0000003F;

  strip.setPixelColor(0, color);
  delay(5);
  strip.setPixelColor(0, color);
  for ( int cnt = 1; cnt < 64; cnt++ ) {
    strip.setPixelColor(cnt, color );
    strip.show();
    strip.setPixelColor(cnt - 1, 0x00000000 );
    delay(5);
  }
  strip.setPixelColor(63, 0x00000000 );
  strip.show();
  Serial.printf("!");
}

//#include "col.h"


// waitand then clear screen
void clearPiskel( int ms)
{
  delay(ms);
  for (int pixel = 0; pixel < 64; pixel++ ) {
    strip.setPixelColor(pixel, 0x00000000);
  }
  strip.show();
  //Serial.printf("x");

}


// FONT IMPLEMENTATION
#include "font.h"
#define FRAME_WIDTH 8
#define FRAME_HEIGHT 8
uint8_t glcd_scroll = 1;      // "TRUE"
uint16_t glcd_col_timing = 75;

// convert x,y (0,0 => 7,7) to a value
byte get_screen_pos(byte x, byte y)
{
  return (y * FRAME_HEIGHT) + (FRAME_WIDTH - x - 1);
}

byte glcd_red=0x1F;

byte glcd_green=0x00;
byte glcd_blue=0x00;

void glcd_setColor(byte r, byte g, byte b)
{
  glcd_red=r;glcd_green=g;glcd_blue=b;
}

void glcd_write_col(unsigned char c, unsigned char x, unsigned char y)
{

  if ( glcd_scroll ) {
      //Serial.printf("Move Left\n");
      glcd_move_left(0);   // Move old content
        x=FRAME_WIDTH-1; // Write at right-most column after move.
  }

  for (int cnt = 0; cnt < 7; cnt++ ) {
    //Serial.printf("cnt\n");
    if ( c & (1 << cnt) )
      strip.setPixelColor(get_screen_pos(x, y + cnt), glcd_red,glcd_green,glcd_blue);
    else
      strip.setPixelColor(get_screen_pos(x, y + cnt), 0, 0, 0);

    //Serial.printf("1");
  }
  if ( glcd_scroll ) {
    //Serial.printf("cnt\n");
    strip.show();  // Turn all LEDs off ASAP
    delay(glcd_col_timing);
    //Serial.printf("2");
  }

}
void glcd_move_left( uint8_t clear_last_col )
{
  int x, y;

  for (x=1; x < FRAME_WIDTH; x++ ) {
    for ( y=0; y<FRAME_HEIGHT; y++ ) {
      strip.setPixelColor(get_screen_pos(x-1,y), strip.getPixelColor( get_screen_pos(x,y)) );

    }
  }
  if ( clear_last_col )
    glcd_write_col(0x00, 0, FRAME_WIDTH );
}


void glcd_putc_5x7(char c, byte x, byte y)
{
  int i, temp;

  //Serial.printf("putc\n");
  /* write ascii character */
  for (i = 0; i < 5; i++) {
    //Serial.printf("prepare linen");
    /*cloumns*/
    //Serial.printf("col\n");
    temp = Font5x7[(c - 0x20) * 5 + (i)];
    glcd_write_col(temp, x + i, y);
    //Serial.printf("6\n");
  }
  if ( glcd_scroll ) {      // Add one column
    //Serial.printf("scrol\n");
    glcd_write_col(0x00,x,y);
  }
  else {
    strip.show();
    delay(glcd_col_timing*10);
    //Serial.printf("7\n");
  }

  //Serial.printf("7.1\n");
}

#if 0
uint8_t glcd_puts_5x7(unsigned char *s, int len, uint8_t page, uint8_t col, uint8_t cs, uint8_t cement)
{
  int i;
  uint8_t current_col;

  for (i = 0; i < len; i++) {
    current_col = glcd_ putc_5x7(s[i], page, col, cs, cement);
    col = current_col + 1;
    page = current_page;
    cs = current_cs;
  }

  return current_col;
}



#endif


void loop_text( const char *string)
{
//  char *string = "* * Peter * *  ";
  byte len;

  len = strlen(string);
  //Serial.printf("len=%d\n",len);
  for ( int cnt = 0; cnt < len; cnt++ ) {
    glcd_putc_5x7(string[cnt], 1, 1);
    if ( ! glcd_scroll ) {
      strip.show();  // Turn all LEDs off ASAP
      delay(300);
    }
    //Serial.printf("8\n");
  }
  //Serial.printf("9");

}

void show_pumping_heart( void) 
{
  show_piskel((uint32_t *)&  heart_data_red_1, FRAMES(heart_data_red_1), 0, 0, 0);   // 0 = intensity, do not show...
 

  for ( int cnt = 0; cnt < 4; cnt++ ) {

    for ( int i = 0; i < 160 ; i+=5 ) {
      strip.setBrightness(i+15);
      strip.show();
      delay(30);
    }
    delay(300);
    
    for ( int i = 0; i < 160; i+=5 ) {
      strip.setBrightness((160-i)+15);
      strip.show();
      delay(30);
    }
    delay(200);
  }
  clearPiskel(1);

  strip.setBrightness(255);   // Since we fiddled with brightness, make sure to reset it
  strip.show();

}



/****************************************************/

void setAllPixel( float thresh )
{

  for (int cnt =0; cnt<64; cnt++) {
    strip.setPixelColor(cnt, 0x1F, 0,0 );

  }
      strip.show();  // Turn all LEDs off ASAP
}


/* SETUP */
void PIXEL_setup(void) {

  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
  strip.setBrightness(255);   // Set default brightness
  sensor_setup();
  
}

#define WAIT_BETWEEN 3000
void PIXEL_loop(void)
{
  float temp, humidity;
  char buf[64];
  delay(3000);


  glcd_scroll = 1;

  loop_text( "*** ");
  clearPiskel(500);
  delay(3000);

  //loop_text( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrustuvwxyz0123456789!\"#¤%&/()=?");
  //clearPiskel(500);
  //delay(3000);

  sensor_read(&temp,&humidity);
  if ( temp > 29 ) {
    sprintf(buf,"Warm! %fC ", temp);
  }
  else {
    sprintf(buf,"Temp:%2.1f C ", temp);
  }
  loop_text(buf);
  Serial.printf(buf);

  Serial.printf("%f %f\n", temp, humidity);

  clearPiskel(500);
  delay(3000);

  glcd_scroll = 1;

  loop_text( "*** ");
  Serial.printf("Y");
  clearPiskel(500);

  piskel_scroll_left((uint32_t *)& arcade_rockstars, NORM_INTENSITY);
  piskel_scroll_left((uint32_t *)& empty, NORM_INTENSITY);

  piskel_scroll_left((uint32_t *)& arcade_rockstars[1], NORM_INTENSITY);
  piskel_scroll_left((uint32_t *)& empty, NORM_INTENSITY);

  piskel_scroll_left((uint32_t *)& arcade_rockstars[2], NORM_INTENSITY);
  piskel_scroll_left((uint32_t *)& empty, NORM_INTENSITY);

  clearPiskel(500);
  
  loop_text( "* * * ");
  clearPiskel(500);
  delay(3000);

  show_piskel((uint32_t *)& arcade_rockstars, FRAMES(arcade_rockstars), 1500, WAIT_BETWEEN, NORM_INTENSITY);
  clearPiskel(500);

  show_piskel((uint32_t *)& arcade_rockstars, FRAMES(arcade_rockstars), 1500, WAIT_BETWEEN, NORM_INTENSITY);
  clearPiskel(500);

  show_piskel((uint32_t *)& batman_2, FRAMES(batman_2), 1500, WAIT_BETWEEN, NORM_INTENSITY);
  clearPiskel(500);

  show_piskel((uint32_t *) & fmxwpow_data, FRAMES(fmxwpow_data), 1500, WAIT_BETWEEN, NORM_INTENSITY);
  clearPiskel(500);

  show_piskel((uint32_t *)&  heart_data_red_1, FRAMES(heart_data_red_1), 3000, WAIT_BETWEEN, NORM_INTENSITY);
  clearPiskel(500);

  show_piskel((uint32_t *) & X, FRAMES(X), 1500, WAIT_BETWEEN, NORM_INTENSITY);
  clearPiskel(500);

  show_pumping_heart();

  glcd_scroll = 1;
  loop_text( "* * PeGe was here * *  ");
  clearPiskel(WAIT_BETWEEN);

  show_piskel((uint32_t *)& arcade_rockstars, FRAMES(arcade_rockstars), 1500, WAIT_BETWEEN, NORM_INTENSITY);
  clearPiskel(10);

}