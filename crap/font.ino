// font.c - 


// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#include <Adafruit_DotStar.h>
#include <stdint.h>


#define NUMPIXELS 64 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    4
#define CLOCKPIN   5
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}
/************************************/

#include "font.h"
#define FRAME_WIDTH 8
#define FRAME_HEIGHT 8

// convert x,y (0,0 => 7,7) to a value
byte get_screen_pos(byte x,byte y)
{
  return (y*FRAME_HEIGHT)+ (FRAME_WIDTH-x-1);
}


void glcd_write_data(unsigned char c, unsigned char x, unsigned char y)
{
    for (int cnt=0; cnt < 7; cnt++ ) {
      if ( c & (1<<cnt) )
        strip.setPixelColor(get_screen_pos(x,y+cnt),0x1F,0,0);
      else
        strip.setPixelColor(get_screen_pos(x,y+cnt),0,0,0);
    }
}


byte glcd_putc_5x7(char c, byte x, byte y)
{
  int i,col,temp;
  
  /* write ascii character */
  for(i=0; i<=4; i++)
    {
      /*cloumns*/
      temp = Font5x7[(c-0x20)*5 + (i)];
      glcd_write_data(temp, x+i,y);
    }  
}

#if 0
uint8_t glcd_puts_5x7(unsigned char *s, int len, uint8_t page, uint8_t col, uint8_t cs, uint8_t cement)
{
  int i;
  uint8_t current_col;
  
  for(i=0;i<len;i++){
    current_col=glcd_putc_5x7(s[i], page, col, cs, cement);
    col = current_col+1;
    page = current_page;
    cs=current_cs;
  }
  
  return current_col;
}



#endif

void clear( int ms)
{
  delay(ms);
  for (int pixel=0; pixel<64; pixel++ ) {
     strip.setPixelColor(pixel,0x00000000);
  }
  strip.show();
  
}
    

void loop(void) 
{
  char *string = "* * Peter Gul lberg * * ar bast ";
  byte len;
#if 0

  for (int cnt=0;cnt<200; cnt+=5 ) {
    for (int cnt2=0; cnt2<5; cnt2++ ) {
      glcd_write_data(Font5x7[cnt+cnt2], cnt2, 0);
    }
    strip.show();  // Turn all LEDs off ASAP
    delay(500);
  }
#endif
  len = strlen(string);
  for ( int cnt=0; cnt <len; cnt++ ){
    glcd_putc_5x7(string[cnt],1,1);
    strip.show();  // Turn all LEDs off ASAP
    delay(300);
  }
  
}

