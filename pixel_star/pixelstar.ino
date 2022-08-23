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
    Serial.printf("fram:%d\n",frame);
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

// Foreground colours for text operations...
byte glcd_red;
byte glcd_green;
byte glcd_blue;
// Background colours
byte glcd_bg_red;
byte glcd_bg_green;
byte glcd_bg_blue;

void glcd_setDefaultColors( void ) 
{
  glcd_red=0x1F;
  glcd_green=0x00;
  glcd_blue=0x00;

  glcd_bg_red=0x00;
  glcd_bg_green=0x00;
  glcd_bg_blue=0x00;
}

// Background colours ??

void glcd_setColor(byte r, byte g, byte b)
{
  glcd_red=r;glcd_green=g;glcd_blue=b;
}
void glcd_setBgColor(byte r, byte g, byte b)
{
  glcd_bg_red=r;glcd_bg_green=g;glcd_bg_blue=b;
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
      strip.setPixelColor(get_screen_pos(x, y + cnt), glcd_bg_red,glcd_bg_green,glcd_bg_blue);
      //strip.setPixelColor(get_screen_pos(x, y + cnt), 0, 0, 0);

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

  glcd_setDefaultColors();
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
  static int state = 0;
 
  Serial.printf("state:%d\n",state);
  switch ( state++ ) {
    case 0:
      delay(3000);    // keep, this is a hard-code stuff!
      glcd_scroll = 1;
      loop_text( "*** ");
      clearPiskel(500);
      delay(3000);
      break;
    case 1:
      sensor_read(&temp,&humidity);
      if ( temp > 29 ) {
        sprintf(buf,"Warm! %2.1f %2.1f%RH", temp, humidity);
      }
      else {
        sprintf(buf,"Temp:%2.1fC %2.1f%RH ", temp, humidity);
      }
      loop_text(buf);
      Serial.printf(buf);

      Serial.printf("%f %f\n", temp, humidity);

      clearPiskel(500);
      delay(3000);
      break;
    case 2:
      // Violet / purple	4	204, 68, 204    
    	// Violet #0xCC 0x44 0xCC
      // Blue	#0x00 0x00 0xAA

      //glcd_setBgColor(0xCC,0x44, 0xCC);
      loop_text( "  ");
      glcd_setColor(0xCC,0x44, 0xCC);
      //glcd_setBgColor(0x00, 0x00, 0xAA);
      loop_text( "?SYNTAX ERROR ");
      //glcd_setBgColor(0xCC,0x44, 0xCC);
      loop_text( "  ");
      clearPiskel(500);
      delay(3000);
      //loop_text( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrustuvwxyz0123456789!\"#¤%&/()=?");
      //clearPiskel(500);
      //delay(3000);
      glcd_setDefaultColors(); 
      break;
    case 3:
      glcd_scroll = 1;
      loop_text( "*** ");
      Serial.printf("Y");
      clearPiskel(500);
      break;
    case 4:
      piskel_scroll_left((uint32_t *)& arcade_rockstars[0], NORM_INTENSITY);
      piskel_scroll_left((uint32_t *)& empty, NORM_INTENSITY);
      break;
    case 5:
      piskel_scroll_left((uint32_t *)& arcade_rockstars[1], NORM_INTENSITY);
      piskel_scroll_left((uint32_t *)& empty, NORM_INTENSITY);
      break;
    case 6:
      piskel_scroll_left((uint32_t *)& arcade_rockstars[2], NORM_INTENSITY);
      piskel_scroll_left((uint32_t *)& empty, NORM_INTENSITY);
      clearPiskel(500);
      break;
    case 7:
      loop_text( "* * * ");
      clearPiskel(500);
      delay(3000);
      break;
    case 8:
      show_piskel((uint32_t *)& arcade_rockstars, FRAMES(arcade_rockstars), 1500, WAIT_BETWEEN, NORM_INTENSITY);
      clearPiskel(500);
      break;
    case 9:
      //show_piskel((uint32_t *)& arcade_rockstars, FRAMES(arcade_rockstars), 1500, WAIT_BETWEEN, NORM_INTENSITY);
      //clearPiskel(500);
      break;
    case 10:
      show_piskel((uint32_t *)& batman_2, FRAMES(batman_2), 1500, WAIT_BETWEEN, NORM_INTENSITY);
      clearPiskel(500);

      break;
    case 11:
      show_piskel((uint32_t *) & fmxwpow_data, FRAMES(fmxwpow_data), 1500, WAIT_BETWEEN, NORM_INTENSITY);
      clearPiskel(500);
      break;
    case 12:
      show_piskel((uint32_t *)&  heart_data_red_1, FRAMES(heart_data_red_1), 3000, WAIT_BETWEEN, NORM_INTENSITY);
      clearPiskel(500);
      break;
    case 13:
      show_piskel((uint32_t *) & X, FRAMES(X), 1500, WAIT_BETWEEN, NORM_INTENSITY);
      clearPiskel(500);
      break;
    case 14:
      show_pumping_heart();
      clearPiskel(WAIT_BETWEEN);
      break;
    case 15:
      glcd_scroll = 1;
      loop_text( "* * PeGe was here * *  ");
      clearPiskel(WAIT_BETWEEN);
      break;
    case 16:
      //show_piskel((uint32_t *)& arcade_rockstars, FRAMES(arcade_rockstars), 1500, WAIT_BETWEEN, NORM_INTENSITY);
      //clearPiskel(10);
      break;
    case 17:
      show_piskel((uint32_t *)& NITTO_2, FRAMES(NITTO_2), 1500, WAIT_BETWEEN, NORM_INTENSITY);
      clearPiskel(WAIT_BETWEEN);
      break;
    case 18:
      //show_piskel((uint32_t *)& giphy_data_6, FRAMES(giphy_data_6), 1500, WAIT_BETWEEN, NORM_INTENSITY);
      //clearPiskel(WAIT_BETWEEN);
      break;
    case 19:
      show_piskel((uint32_t *)& heart_data_1, FRAMES(heart_data_1), 1500, WAIT_BETWEEN, NORM_INTENSITY);
      clearPiskel(WAIT_BETWEEN);
      break;
    case 20:
      KNIGHTRIDER_setup();
      for (int cnt =0; cnt < 316; cnt++ ) {
        KNIGHTRIDER_loop();
      }
      break;
    default:
      state = 0;
      clearPiskel(WAIT_BETWEEN);
  }
}


/*-------------------------------------------------------------------------
  knightrider - 
  A project implementing the Knight Rider KITT Scanner.

  The project uses Neopixel (WS278x RGB) leds to create a
  KITT scanner.
  -------------------------------------------------------------------------
  License goes here....
  -------------------------------------------------------------------------*/


int running = 1;




/* Knight Rider - KIT Scanner*/
#define BYTE unsigned char

// The original KIT scanner used Halogen lamps, with afterglow
#define ON_INTENSITY  30    // 300ms
#define DECAY_RATE  1   // 10 units per 10ms


BYTE lamp_brightness[8];
BYTE lamp_on_off[8];

// Function that emulates halogen light that is slowly decauing, which slowly dims the lamp
void decay_light(void)
{
  int val;
  int cnt;
  for(cnt=0;cnt<8;cnt++) {
    // only decay brightness once lamp is off
    if ( 0 ==  lamp_on_off[cnt] ) {
      val = lamp_brightness[cnt];
      val -= DECAY_RATE;
      if ( val < 0) {
        val=0;
      }
      lamp_brightness[cnt]=val;
    }
  }
}
void set_lamps( BYTE val, BYTE force_off )
{
  int cnt;
  int t=0x80;
  for (cnt=0;cnt<8;cnt++) {
    if ( val & t ) {
      lamp_on_off[cnt] = 1;
      lamp_brightness[cnt] = ON_INTENSITY;
    }
    else {
      lamp_on_off[cnt] = 0;
      //  don't clear brightness let it decay
      if ( force_off ) {
        lamp_brightness[cnt] = 0;
      }
    }
    t = t>>1;
  }
}

// Simply experimental values on red.
uint32_t red_strength[] =
{
    0x00000000,  // red
    0x00000100,  // 
    0x00000300,  // 
    0x00000A00,  // 
    0x00000F00,  // 
    0x00001000,  // 
    0x00001600,  // 
    0x00002000,  // 
    0x00002F00,  // 
    0x00005000,  // 
    0x00005000,  // 
};
void show_lamps( void )
{
int cnt;
int ret;

  for(cnt=0;cnt<8;cnt++) {
    strip.setPixelColor(cnt+(3*8), (uint32_t) red_strength[ lamp_brightness[cnt] / 3 ]<<8);
  }
  strip.show(); // Show all pixel
  
}

int P2[] =  {
 0x80, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01,0x01, 
 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x80,0x80, 0xFFFF,
 };
int  P1[] = { 
 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x01,0x01,
 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x80, 0xFFFF, 
 };

typedef struct {
  char *Name;   // Name of the scheme
  int timing;   // timing (in 10ms)
  int *pattern; // 0xFFFF in the end to restart
} _KITT;

_KITT KITT[] = {
// left=MSB to right=LSB, 0xFFFF = restart
// Name == NULL, stops transaction
/*
 { 
 "Normal scan",
 12,
 P1,
 }
,*/
 {
 "Fast Scan",
 9,
 P2,
 } 
,
/*
 {
 "Test 3",
 25,
 P1,
 }
,*/
 {
 NULL,
 0,
 P1,
 }
};

int pos=0;
int p_cnt=0;
int timing=0;

void KNIGHTRIDER_setup(void)
{

  set_lamps( 0x00,1 );
  show_lamps();

  p_cnt=0;
  pos = 0;
  timing = KITT[p_cnt].timing;
}

void KNIGHTRIDER_loop(void)
{

  //while (running) {
    // run at 10ms speed
    delay(15);
    // Periodically  updates scanner
    if ( ++timing > KITT[p_cnt].timing ) {
      timing = 0;
      if ( 0xFFFF == KITT[0].pattern[pos] ) {
        p_cnt++;
        pos = 0;
        if (NULL == KITT[p_cnt].Name ) {
          p_cnt=0;
        }
        timing = KITT[p_cnt].timing;
        printf("KITT %s\n", KITT[p_cnt].Name);
        printf("KITT timing %d\n", KITT[p_cnt].timing);
      }
      set_lamps(KITT[p_cnt].pattern[pos],0);
      pos++;
    }
    show_lamps();
    decay_light();
 // }
}


