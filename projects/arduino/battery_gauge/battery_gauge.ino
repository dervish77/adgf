#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF


#define PIN 6

#define WIDTH    5
#define HEIGHT   8

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);
  

const uint16_t colors[] = {
  matrix.Color(0, 60, 170), matrix.Color(255, 165, 0), matrix.Color(0, 60, 170), matrix.Color(255, 165, 0) };


void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(16);
  matrix.setTextColor(colors[0]);
}

int x    = matrix.width();
int pass = 0;

void loop() {
  matrix.fillScreen(0);

  for (int i=0; i
  
  
  matrix.show();
  delay(100);
}
