#define PROGMEM 
const uint8_t gamma8[] PROGMEM = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

static const uint32_t empty[][64] PROGMEM = {
{ // Heart
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
},
};

static const uint32_t fmxwpow_data[][64] PROGMEM = {
{ // Heart
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0xff0000ff, 0xff0000ff, 0x00000000, 0x00000000, 0xff0000ff, 0xff0000ff, 0x00000000,
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff,
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff,
0x00000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000,
0x00000000, 0x00000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0xff0000ff, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
},
{ // Skull
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000, 0x00000000,
0xff0000ff, 0x00000000, 0x00000000, 0xff0000ff, 0x00000000, 0x00000000, 0xff0000ff, 0x00000000,
0xff0000ff, 0x00000000, 0x00000000, 0xff0000ff, 0x00000000, 0x00000000, 0xff0000ff, 0x00000000,
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000,
0x00000000, 0xff0000ff, 0xff0000ff, 0x00000000, 0xff0000ff, 0xff0000ff, 0x00000000, 0x00000000,
0x00000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000, 0x00000000,
0x00000000, 0xff0000ff, 0x00000000, 0xff0000ff, 0x00000000, 0xff0000ff, 0x00000000, 0x00000000
}
};

static const uint32_t NITTO_2[][64] PROGMEM = {
{
0xff411f16, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff411f16,
0xff411f16, 0xff411f16, 0xfffc9a28, 0xfffc9a28, 0xfffc9a28, 0xff411f16, 0xfffc9a28, 0xff411f16,
0xff411f16, 0xff000000, 0xff411f16, 0xff411f16, 0xfffc9a28, 0xfffc9a28, 0xff411f16, 0xff411f16,
0xff411f16, 0xff000000, 0xff000000, 0xff411f16, 0xff411f16, 0xff411f16, 0xff000000, 0xff411f16,
0xff411f16, 0xffe2eeff, 0xffe2eeff, 0xff000000, 0xff000000, 0xffe2eeff, 0xffe2eeff, 0xff411f16,
0xff411f16, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff411f16,
0xff411f16, 0xff9ac1fe, 0xff9ac1fe, 0xffe2eeff, 0xffe2eeff, 0xff9ac1fe, 0xff9ac1fe, 0xff411f16,
0x00000000, 0xff411f16, 0xff9ac1fe, 0xff9ac1fe, 0xff9ac1fe, 0xff9ac1fe, 0xff411f16, 0x00000000
},
{
0x00000000, 0xff2a3e99, 0xff2a3e99, 0xff2a3e99, 0xff2a3e99, 0xff2a3e99, 0xff2a3e99, 0x00000000,
0xff2a3e99, 0xff2a3e99, 0xff2a3e99, 0xff2a3e99, 0xff2a3e99, 0xff2a3e99, 0xff9ac1fe, 0xff2a3e99,
0xff2a3e99, 0xff2a3e99, 0xffe2eeff, 0xffe2eeff, 0xff9ac1fe, 0xff9ac1fe, 0xff9ac1fe, 0xff2a3e99,
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
0xff000000, 0xffe2eeff, 0xffe2eeff, 0xff000000, 0xff000000, 0xffe2eeff, 0xffe2eeff, 0xff000000,
0xff000000, 0xff000000, 0xff000000, 0xff9ac1fe, 0xff9ac1fe, 0xff000000, 0xff000000, 0xff000000,
0xff9ac1fe, 0xff9ac1fe, 0xff9ac1fe, 0xffe2eeff, 0xffe2eeff, 0xff9ac1fe, 0xff9ac1fe, 0xff9ac1fe,
0x00000000, 0xff9ac1fe, 0xff9ac1fe, 0xff9ac1fe, 0xff9ac1fe, 0xff9ac1fe, 0xff9ac1fe, 0x00000000
}
};

static const uint32_t giphy_data_6[][64] PROGMEM = {
  { // Happy ghost#1
    0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff000000,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff000000, 0xff4f00ff, 0xff000000, 0xff000000, 0xff4f00ff, 0xff000000, 0xff4f00ff
  },
  { // Happy ghost#2
    0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
    0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff000000,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff
  },
  { //Happy ghost#3
    0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff000000,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff000000, 0xff4f00ff, 0xff000000, 0xff000000, 0xff4f00ff, 0xff000000, 0xff4f00ff
  },
  {
    0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
    0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff000000,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff
  },
  {  // Happy ghost #4
    0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff000000,
    0xff4f00ff, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
    0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff000000, 0xff4f00ff, 0xff000000, 0xff4f00ff,
    0xff4f00ff, 0xff000000, 0xff4f00ff, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000
  }

};



static const uint32_t heart_data_1[][64] PROGMEM = {
  {
    0x00000000, 0xff7940f9, 0xff7940f9, 0x00000000, 0xff7940f9, 0xff7940f9, 0x00000000, 0x00000000,
    0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0x00000000,
    0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0x00000000,
    0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0x00000000,
    0x00000000, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0x00000000, 0x00000000,
    0x00000000, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0xff7940f9, 0x00000000, 0x00000000, 0x00000000, 0x00000000
  }
};

static const uint32_t heart_data_red_1[1][64] PROGMEM = {
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0xff7940f9, 0xff7940f9, 0x00000000, 0x00000000, 0xff7940f9, 0xff7940f9, 0x00000000,
    0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9,
    0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9,
    0x00000000, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0x00000000,
    0x00000000, 0x00000000, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0xff7940f9, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0xff7940f9, 0xff7940f9, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  }
};



static const uint32_t X[][64] PROGMEM = {

  /* Green ghost */
  {
    0x00000000, 0xff529922, 0xff529922, 0xff529922, 0xff529922, 0xff529922, 0xff529922, 0x00000000,
    0xff529922, 0xff529922, 0xff529922, 0xff529922, 0xff529922, 0xff529922, 0xff529922, 0xff529922,
    0xff529922, 0xff0000ff, 0xff529922, 0xff529922, 0xff0000ff, 0xff529922, 0xff529922, 0xff529922,
    0xff529922, 0xff529922, 0xff529922, 0xff529922, 0xff529922, 0xff529922, 0xff529922, 0xff529922,
    0xff529922, 0xff529922, 0xffffffff, 0xff000000, 0xffffffff, 0xff000000, 0xffffffff, 0xff529922,
    0xff529922, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff529922,
    0xff529922, 0xffffffff, 0xff000000, 0xffffffff, 0xff000000, 0xffffffff, 0xff000000, 0xff529922,
    0xff529922, 0xff529922, 0xff529922, 0xff529922, 0xff529922, 0xff529922, 0xff529922, 0xff529922
  },
};

static const uint32_t batman_2[][64] PROGMEM = {
{
0xffff000f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xffff000f,
0xffff000f, 0xffff000f, 0xfffc9a28, 0xfffc9a28, 0xfffc9a28, 0xffff000f, 0xfffc9a28, 0xffff000f,
0xffff000f, 0xff630541, 0xffff000f, 0xffff000f, 0xfffc9a28, 0xfffc9a28, 0xffff000f, 0xffff000f,
0xffff000f, 0xff630541, 0xff630541, 0xffff000f, 0xffff000f, 0xffff000f, 0xff630541, 0xffff000f,
0xffff000f, 0xffe2eeff, 0xffe2eeff, 0xff630541, 0xff630541, 0xffe2eeff, 0xffe2eeff, 0xffff000f,
0xffff000f, 0xff630541, 0xff630541, 0xff630541, 0xff630541, 0xff630541, 0xff630541, 0xffff000f,
0xffff000f, 0xff7baefd, 0xff7baefd, 0xffe2eeff, 0xffe2eeff, 0xff7baefd, 0xff7baefd, 0xffff000f,
0x00000000, 0xffff000f, 0xff7baefd, 0xff7baefd, 0xff7baefd, 0xff7baefd, 0xffff000f, 0x00000000
},
{
0x00000000, 0xff2348ae, 0xff2348ae, 0xff2348ae, 0xff2348ae, 0xff2348ae, 0xff2348ae, 0x00000000,
0xff2348ae, 0xff2348ae, 0xff2348ae, 0xff2348ae, 0xff2348ae, 0xff2348ae, 0xff7baefd, 0xff2348ae,
0xff2348ae, 0xff2348ae, 0xffe2eeff, 0xffe2eeff, 0xff7baefd, 0xff7baefd, 0xff7baefd, 0xff2348ae,
0xff274665, 0xff274665, 0xff274665, 0xff274665, 0xff103961, 0xff103961, 0xff103961, 0xff103961,
0xff274665, 0xffe2eeff, 0xffe2eeff, 0xff274665, 0xff103961, 0xffe2eeff, 0xffe2eeff, 0xff103961,
0xff274665, 0xff274665, 0xff274665, 0xff7baefd, 0xff7baefd, 0xff103961, 0xff103961, 0xff103961,
0xff7baefd, 0xff7baefd, 0xff7baefd, 0xffe2eeff, 0xffe2eeff, 0xff7baefd, 0xff7baefd, 0xff7baefd,
0x00000000, 0xff7baefd, 0xff7baefd, 0xff7baefd, 0xff7baefd, 0xff7baefd, 0xff7baefd, 0x00000000
}
};

static const uint32_t arcade_rockstars[][64] PROGMEM = {

  { // Blue pacman Ghost
    0x00000000, 0x00000000, 0x00000000, 0xffff0000, 0xffff0000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0x00000000, 0x00000000,
    0x00000000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0x00000000,
    0xffff0000, 0xffffffff, 0xffffffff, 0xffff0000, 0xffff0000, 0xffffffff, 0xffffffff, 0xffff0000,
    0xffff0000, 0xffffffff, 0x00000000, 0xffff0000, 0xffff0000, 0xffffffff, 0x00000000, 0xffff0000,
    0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
    0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
    0x00000000, 0xffff0000, 0xffff0000, 0x00000000, 0xffff0000, 0x00000000, 0xffff0000, 0x00000000
  },

  
  { // Pacman
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0x00000000,
    0x00000000, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff,
    0x00000000, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff,
    0x00000000, 0x00000000, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0x00000000, 0x00000000
  },

/*  { // Pacman - non-inverted
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0x00000000, 0x00000000,
    0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0x00000000,
    0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0x00000000,
    0x00000000, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xff00f7ff, 0xff00f7ff, 0xff00f7ff, 0x00000000, 0x00000000, 0x00000000
  },
*/
  { // Blinky - pacman
  0xff020b00, 0xff000012, 0xff4923a1, 0xff4d21bc, 0xff532eb2, 0xff412d75, 0xff030011, 0xff020004,
  0xff080619, 0xff4b28a0, 0xff4e0de5, 0xff520fee, 0xff4400f6, 0xff4d23be, 0xff4e3d80, 0xff09011f,
  0xff462a95, 0xff4b0ce4, 0xffe4c7ff, 0xfff5f0ff, 0xff4718cc, 0xffe7d7ff, 0xffd9daff, 0xff3f375f,
  0xff3b199b, 0xff4200ee, 0xffefe2ff, 0xff000020, 0xff562cd7, 0xff000039, 0xffd8d7ff, 0xff423672,
  0xff3e159c, 0xff4c07ec, 0xff4904f5, 0xff4403f3, 0xff5010fc, 0xff5a19e1, 0xff4a1894, 0xff4e3862,
  0xff3d1598, 0xff4e1acc, 0xff4d0cf2, 0xff4d09f6, 0xff4410d2, 0xff581dd3, 0xff441492, 0xff4f3668,
  0xff3d2a69, 0xff15024b, 0xff502eaa, 0xff4924a8, 0xff000031, 0xff563a93, 0xff452871, 0xff483a56,
  0xff030701, 0xff000700, 0xff000008, 0xff010107, 0xff020b00, 0xff020103, 0xff020008, 0xff030402
  },
/*
  { // SpaceInvaders
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0xff0000ff, 0x00000000, 0xff0000ff, 0x00000000, 0xff0000ff, 0x00000000, 0x00000000,
  0x00000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000, 0x00000000,
  0x00000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000, 0x00000000,
  0x00000000, 0xff0000ff, 0x00000000, 0xff0000ff, 0x00000000, 0xff0000ff, 0x00000000, 0x00000000
  },
*/
  /* Piskel data for "New Piskel" */
  {
  0x00000000, 0x00000000, 0x00000000, 0xff2cd356, 0xff2cd356, 0x00000000, 0x00000000, 0x00000000, 
  0x00000000, 0x00000000, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0x00000000, 0x00000000, 
  0x00000000, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0x00000000, 
  0xff2cd356, 0xff2cd356, 0x00000000, 0xff2cd356, 0xff2cd356, 0x00000000, 0xff2cd356, 0xff2cd356, 
  0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 
  0x00000000, 0x00000000, 0xff2cd356, 0x00000000, 0x00000000, 0xff2cd356, 0x00000000, 0x00000000, 
  0x00000000, 0xff2cd356, 0x00000000, 0xff2cd356, 0xff2cd356, 0x00000000, 0xff2cd356, 0x00000000, 
  0xff2cd356, 0x00000000, 0xff2cd356, 0x00000000, 0x00000000, 0xff2cd356, 0x00000000, 0xff2cd356
  },
/*
{
0x00000000, 0x00000000, 0x00000000, 0xff2cd356, 0xff2cd356, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0x00000000, 0x00000000, 
0x00000000, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0x00000000, 
0xff2cd356, 0xff2cd356, 0x00000000, 0xff2cd356, 0xff2cd356, 0x00000000, 0xff2cd356, 0xff2cd356, 
0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 
0x00000000, 0x00000000, 0xff2cd356, 0x00000000, 0x00000000, 0xff2cd356, 0x00000000, 0x00000000, 
0x00000000, 0xff2cd356, 0x00000000, 0xff2cd356, 0xff2cd356, 0x00000000, 0xff2cd356, 0x00000000, 
0xff2cd356, 0x00000000, 0xff2cd356, 0x00000000, 0x00000000, 0xff2cd356, 0x00000000, 0xff2cd356
},
*/
{
0xff2cd356, 0x00000000, 0xff2cd356, 0x00000000, 0x00000000, 0xff2cd356, 0x00000000, 0xff2cd356, 
0xff2cd356, 0x00000000, 0x00000000, 0xff2cd356, 0xff2cd356, 0x00000000, 0x00000000, 0xff2cd356, 
0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 
0xff2cd356, 0xff2cd356, 0x00000000, 0xff2cd356, 0xff2cd356, 0x00000000, 0xff2cd356, 0xff2cd356, 
0x00000000, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0x00000000, 
0x00000000, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0xff2cd356, 0x00000000, 
0x00000000, 0xff2cd356, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff2cd356, 0x00000000, 
0x00000000, 0x00000000, 0xff2cd356, 0x00000000, 0x00000000, 0xff2cd356, 0x00000000, 0x00000000
}
 
};



static const uint32_t ugly[][64] PROGMEM = {
{
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff010101, 0xff000000,
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff020000, 0xff000101,
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000006, 0xff000001, 0xff000300,
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000400, 0xff000103
},
{
0xff020000, 0xff0c221d, 0xff619e94, 0xff1a7584, 0xff0b0a0c, 0xff0e0003, 0xff00152a, 0xff334758,
0xff0c0109, 0xff000103, 0xff07403d, 0xff37e0fb, 0xff75d6d2, 0xff65cfd0, 0xff2db5cd, 0xff326f89,
0xff61abdb, 0xff44a5e7, 0xff000308, 0xff85ffff, 0xff00130f, 0xff23f9e6, 0xff4fcfda, 0xff000318,
0xff6ab8e6, 0xff26a9f3, 0xff0b0011, 0xff0032aa, 0xff3fedfe, 0xff3ef5f7, 0xff48dfff, 0xff397483,
0xff000012, 0xff2bafe5, 0xff00001b, 0xff63e7ff, 0xff0ba3da, 0xff00a6df, 0xff2092bb, 0xff000308,
0xff100000, 0xff56c1e2, 0xff53fafd, 0xff00a9dd, 0xff71ebff, 0xff21c0e4, 0xff54cbda, 0xff100010,
0xff020300, 0xff000013, 0xff8dffff, 0xff50c1f9, 0xff275392, 0xff0e64a0, 0xff5185b4, 0xff000200,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
},
{
0xff120000, 0xff000008, 0xff000016, 0xff76b6f0, 0xff7bc0e8, 0xff000b16, 0xff020300, 0xff090000,
0xff00040b, 0xff5bc2e9, 0xff37d0bb, 0xff27ce2b, 0xff43c842, 0xff66c836, 0xff547844, 0xff000a00,
0xff10000b, 0xff5baee2, 0xff25bd59, 0xff74e92e, 0xff001c00, 0xff89d143, 0xff0a1b06, 0xff4e6423,
0xff030206, 0xff00000b, 0xff67e43b, 0xff54e33a, 0xff001800, 0xff88b451, 0xff001b00, 0xff45583d,
0xff000304, 0xff73acf1, 0xff3fae70, 0xff5dc5ac, 0xff197e00, 0xffd4ffa5, 0xff408a14, 0xff435167,
0xff000029, 0xff3e1bed, 0xff441bd1, 0xff60d036, 0xff5cbf34, 0xff75c82c, 0xff7bbe43, 0xff3f5c2e,
0xff64ae94, 0xff3a4081, 0xff386177, 0xff719099, 0xffb7beef, 0xffdeebed, 0xfff2edff, 0xff847791,
0xff457b22, 0xff215a0f, 0xff44782a, 0xff3a1d84, 0xff311e6d, 0xff7d8390, 0xff969a8e, 0xff2c1b40
},
{
0xff000003, 0xff080203, 0xff012d2e, 0xff6edbe3, 0xff53e4dc, 0xff3c97b2, 0xff000211, 0xff0b0107,
0xff000300, 0xff00111a, 0xff49fffe, 0xff289898, 0xff41b6b3, 0xff002340, 0xff71abdf, 0xff000f1f,
0xff19110a, 0xff00030f, 0xff1aeae6, 0xff3e9d99, 0xff58a29e, 0xff002b2d, 0xff539ee2, 0xff000011,
0xff000019, 0xff41eff5, 0xff3dffff, 0xff53f8ff, 0xff52f3ff, 0xff70faee, 0xff23a7e7, 0xff000406,
0xff12a1e5, 0xff22b9de, 0xff48f2fd, 0xff2f97de, 0xff0f1ec8, 0xff000431, 0xff56a1f7, 0xff000e02,
0xff47b7eb, 0xff5f96e7, 0xff002858, 0xff63faff, 0xff61f7ff, 0xff53b0ed, 0xff113a71, 0xff00030a,
0xff0b0000, 0xff000065, 0xff3809e8, 0xff441583, 0xff36264f, 0xff4d2674, 0xff190036, 0xff130014,
0xff000027, 0xff401dbb, 0xff3e1ba8, 0xff351972, 0xff37324d, 0xff483665, 0xff49375e, 0xff08000c
},

{
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff000000,
0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
0xff4f00ff, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff4f00ff,
0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff000000, 0xff000000, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff,
0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff, 0xff4f00ff
},

{
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000, 0xff0000ff, 0xff0000ff, 0x00000000,
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff,
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff,
0x00000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000, 0xff0000ff, 0x00000000,
0x00000000, 0x00000000, 0xff0000ff, 0xff0000ff, 0x00000000, 0xff0000ff, 0xff0000ff, 0x00000000
},
{
0x00000000, 0x00000000, 0xff0000ff, 0x00000000, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0xff0000ff, 0x00000000, 0xff0000ff, 0x00000000, 0xff0000ff, 0x00000000, 0x00000000,
0x00000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000, 0x00000000,
0x00000000, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000, 0xff0000ff, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0xff0000ff, 0x00000000, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
},
/*  UGLY - ??  */
 {
    0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0,
    0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0,
    0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xffc0c0c0,
    0x00000000, 0xffc0c0c0, 0xff0000ff, 0xffc0c0c0, 0xff0000ff, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0,
    0x00000000, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0,
    0x00000000, 0xffc0c0c0, 0xff000000, 0xff000000, 0xff000000, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0,
    0xff000000, 0xffc0c0c0, 0xff000000, 0xffc0c0c0, 0xff000000, 0xffc0c0c0, 0xff000000, 0xff000000,
    0x00000000, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0, 0xffc0c0c0
  },

/* Crab - ugly */
  {
    0x00000000, 0xffffffff, 0xffffffff, 0x00000000, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000,
    0x00000000, 0xffffffff, 0xff000000, 0x00000000, 0xffffffff, 0xff000000, 0x00000000, 0x00000000,
    0x00000000, 0xff0000ff, 0x00000000, 0x00000000, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0xff0000ff, 0x00000000, 0x00000000, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000,
    0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000, 0xff0000ff, 0xff0000ff,
    0xff0000ff, 0xff0000ff, 0xff000000, 0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000,
    0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000, 0xff0000ff, 0xff0000ff,
    0xff0000ff, 0x00000000, 0xff0000ff, 0x00000000, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000
  },

  {
    0x00000000, 0xff515f76, 0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0, 0xff515f76, 0x00000000, 0x00000000,
    0x00000000, 0xff515f76, 0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0, 0xff515f76, 0x00000000, 0x00000000,
    0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0, 0x00000000,
    0x00000000, 0xff6f87a0, 0xff34577a, 0xff34577a, 0xff34577a, 0xff3b3026, 0x00000000, 0x00000000,
    0x00000000, 0xff6f87a0, 0xff68aef5, 0xff68aef5, 0xff68aef5, 0xff6f87a0, 0x00000000, 0x00000000,
    0x00000000, 0xff3b3026, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff3b3026, 0x00000000,
    0x00000000, 0xff3b3026, 0xff34577a, 0xff68aef5, 0xff68aef5, 0xff34577a, 0xff3b3026, 0x00000000,
    0x00000000, 0xff3b30a5, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff3b30a5, 0x00000000, 0x00000000
  },

  {
    0x00000000, 0x00000000, 0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0, 0x00000000, 0x00000000,
    0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0, 0xff2b5fa0,
    0x00000000, 0x00000000, 0xff68aef5, 0xff000000, 0xff68aef5, 0xff000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xff68aef5, 0xff68aef5, 0xff68aef5, 0xff68aef5, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0x00000000,
    0x00000000, 0x00000000, 0xff000000, 0xff68aef5, 0xff68aef5, 0xff68aef5, 0xff000000, 0x00000000,
    0x00000000, 0x00000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0x00000000, 0x00000000
  }
};
