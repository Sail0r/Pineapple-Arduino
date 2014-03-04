
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6

#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF
#define BROWN    matrix.Color(143,93,0)

#include "animation.h"

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
NEO_MATRIX_TOP    + NEO_MATRIX_RIGHT +
NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
NEO_GRB            + NEO_KHZ800);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, PIN, NEO_GRB + NEO_KHZ800);

int x = matrix.width();
const int msgBufferLen = 80;
char msg[msgBufferLen];
char msgSeparator = '\n';
String message;

const String msgConnect = "connect";

void setup()
{
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(10);
  strip.setBrightness(10);
  Serial.begin(115200);
}

void loop()
{
  matrix.fillScreen(0);
  strip.show();
  animatePineapple();
}

void animatePineapple() {
  for(int i=0; i<8; i++) { 
    for(int j=0;j<8; j++){
      matrix.drawPixel(j, i, getColor(pineapple_plain[i][j]));
    }
  }
  matrix.show();
  delay(500);
  
  for(int i=0; i<8; i++) { 
    for(int j=0;j<8; j++){
      matrix.drawPixel(j, i, getColor(pineapple_wave1[i][j]));
    }
  }
  matrix.show();
  delay(500);
  
  for(int i=0; i<8; i++) { 
    for(int j=0;j<8; j++){
      matrix.drawPixel(j, i, getColor(pineapple_wave2[i][j]));
    }
  }
  matrix.show();
  delay(500);
}

uint16_t getColor(char c) {
  if (c == 'W') {
    return WHITE;
  }
  else if (c == 'G') { 
    return GREEN;
  }
  else if (c == 'Y') { 
    return YELLOW;
  }
  else if (c == 'B') {
    return BLACK;
  }
  else if (c == 'M') { 
    return MAGENTA;
  }
}

void serialEvent(){

  Serial.readBytesUntil(msgSeparator, msg, msgBufferLen);
  message = String(msg);  
  //trim newline character from message
  message = message.substring(0, message.length()-1);

  //  Serial.println(message);
  //  Serial.println(msg);

  if (message.equals(msgConnect)) {
    Serial.println("Connect message received");
    connectAnimation("10"); //value hardcoded, nr of connections needs implementation
  }
  else {
    Serial.println("No valid message");
  }  
  //reset the char array
  memset(msg, 0, sizeof msg);  
}

void connectAnimation(String connections) {
  int pass = 0;
  rainbow(2);
  matrix.fillScreen(0);
  for(int i =0;i<85;i++){ 
    matrix.setCursor(x, 0);
    matrix.print(connections + " connects...");
    if(--x < -76) {
      x = matrix.width();
      matrix.setTextColor(WHITE);
    }
    matrix.show();
    delay(60);
    matrix.fillScreen(0);
  }
  rainbow(2);
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
