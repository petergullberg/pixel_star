# pixel_star
Pixel start is a small wearble retro image sprite viewer project using an (ESP32) and a 8x8 DotStar-display.
It shouldn't be difficult to port to an Neopixel or whatever.
(Trinket pro is deprecated)

The objective of this repo is to make a small image viewer of retro-sprites using a small Arduino, it also has a text-scroll function.
It allows you to scroll text and show small 8x8 image sprites
# functions
Right now, it has two main functions

- Piskel images and text showing, including a temp-sensor (SI7021)
- FFT, where it shows frequence.

#status
The repo is currently somewhat messed up, since I merged the two parts.
I also didn't document well the other parts, but I'm planning on doing that sometime in the future,
I'm also thinking of moving to neopixel, adding a larger display, either wider, or simply more pixels.


# How it works,
 the code implement a small "image" viewer, which take a predefined C-code struct, and displays it. the images are located in the image_data.h include file, each struct may contain one or more images.
The device also has a text-viewer, which allows you to display scrolling text. Just call the function with the text you want to show.
# Hardware used
ESP32,
Microphone, and a SI7021 tempeature sensor connected
Trinket pro 5V/16Mhz, using serial upload
A Adafruit dotstar 8x8 pixel LCD.

# make your own sprites
piskel is a simple web-program that allows you to create your own sprites.
https://www.piskelapp.com/
Edit your stuff in the piskelapp, and then export from as "Other" C-code. Then copy / paste into the source
Make sure you have the correct size of the image (8x8 piskels)
#include "./image_data.h"   // All piskel images... (today assume 8x8 pixels)
WIDTH AND HEIGHT must be 8, entire program is hardcoded for these paramters!
