
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
 
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
  strip.begin();
  strip.setBrightness(48);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // put your main code here, to run repeatedly:
  int p;
  int n = strip.numPixels();
  
  for (p = 0; p < n; p++)
  {
    strip.setPixelColor(p-3, 0, 0, 0);
    strip.setPixelColor(p, p, n-p, p);
    strip.show();
    delay(100);
  }

  strip.setPixelColor(37, 0, 0, 0);
  strip.setPixelColor(38, 0, 0, 0);
  strip.setPixelColor(39, 0, 0, 0);
  strip.show();
}
