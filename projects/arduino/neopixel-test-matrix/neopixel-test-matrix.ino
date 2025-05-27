
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6

// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  matrix.setBrightness(8);
  matrix.show(); // Initialize all pixels to 'off'
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;
  char phrase[8] = { 'T','E','A','M',' ','4','6','7' };
  int colors[8] = { BLUE, RED, GREEN, CYAN, CYAN, MAGENTA, YELLOW, WHITE };
  
/*
  matrix.drawPixel( 0, 0, GREEN );
  matrix.drawLine( 0, 1, 4, 5, RED );
  matrix.drawRect( 0, 1, 5, 5, MAGENTA );
*/

/*
  matrix.drawPixel( 2, 2, GREEN );
  matrix.drawCircle( 2, 2, 2, BLUE );
*/

  for (i = 0; i < 8; i++)
  {
    
    matrix.drawChar(0, 0, phrase[i], colors[i], 0, 1);
    matrix.show();
    delay(500);
  }

  matrix.show();
}
