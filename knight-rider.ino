#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_PIXELS  60

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  clearStrip();
  delay(1000);
}

void loop() {
  knightRider(1, 32, 4, 0xFF1000); // Cycles, Speed, Width, RGB Color (original orange-red)
  knightRider(1, 32, 3, 0xFF00FF); // Cycles, Speed, Width, RGB Color (purple)
  knightRider(1, 32, 2, 0x0000FF); // Cycles, Speed, Width, RGB Color (blue)
  knightRider(1, 32, 5, 0xFF0000); // Cycles, Speed, Width, RGB Color (red)
  knightRider(1, 32, 6, 0x00FF00); // Cycles, Speed, Width, RGB Color (green)
  knightRider(1, 32, 7, 0xFFFF00); // Cycles, Speed, Width, RGB Color (yellow)
  knightRider(1, 32, 8, 0x00FFFF); // Cycles, Speed, Width, RGB Color (cyan)
  knightRider(1, 32, 2, 0xFFFFFF); // Cycles, Speed, Width, RGB Color (white)
  clearStrip();
  delay(2000);

  for(byte j=0; j<252; j+=7) {
    knightRider(1, 16, 2, colorWheel(j)); // Cycles, Speed, Width, RGB Color
  }
  clearStrip();
  delay(2000);
}


void knightRider(uint16_t cycles, uint16_t speed, uint8_t width, uint32_t color) {
  uint32_t old_val[NUM_PIXELS]; // up to 256 lights!
  // Larson time baby!
  for(int i = 0; i < cycles; i++){
    for (int count = 1; count<NUM_PIXELS; count++) {
      strip.setPixelColor(count, color);
      old_val[count] = color;
      for(int x = count; x>0; x--) {
        old_val[x-1] = dimColor(old_val[x-1], width);
        strip.setPixelColor(x-1, old_val[x-1]); 
      }
      strip.show();
      delay(speed);
    }
    for (int count = NUM_PIXELS-1; count>=0; count--) {
      strip.setPixelColor(count, color);
      old_val[count] = color;
      for(int x = count; x<=NUM_PIXELS ;x++) {
        old_val[x-1] = dimColor(old_val[x-1], width);
        strip.setPixelColor(x+1, old_val[x+1]);
      }
      strip.show();
      delay(speed);
    }
  }
}

void clearStrip() {
  for( int i = 0; i<NUM_PIXELS; i++){
    strip.setPixelColor(i, 0x000000); strip.show();
  }
}

uint32_t dimColor(uint32_t color, uint8_t width) {
   return (((color&0xFF0000)/width)&0xFF0000) + (((color&0x00FF00)/width)&0x00FF00) + (((color&0x0000FF)/width)&0x0000FF);
}

uint32_t colorWheel(byte WheelPos) {
  byte state = WheelPos / 21;
  switch(state) {
    case 0: return strip.Color(255, 0, 255 - ((((WheelPos % 21) + 1) * 6) + 127)); break;
    case 1: return strip.Color(255, ((WheelPos % 21) + 1) * 6, 0); break;
    case 2: return strip.Color(255, (((WheelPos % 21) + 1) * 6) + 127, 0); break;
    case 3: return strip.Color(255 - (((WheelPos % 21) + 1) * 6), 255, 0); break;
    case 4: return strip.Color(255 - (((WheelPos % 21) + 1) * 6) + 127, 255, 0); break;
    case 5: return strip.Color(0, 255, ((WheelPos % 21) + 1) * 6); break;
    case 6: return strip.Color(0, 255, (((WheelPos % 21) + 1) * 6) + 127); break;
    case 7: return strip.Color(0, 255 - (((WheelPos % 21) + 1) * 6), 255); break;
    case 8: return strip.Color(0, 255 - ((((WheelPos % 21) + 1) * 6) + 127), 255); break;
    case 9: return strip.Color(((WheelPos % 21) + 1) * 6, 0, 255); break;
    case 10: return strip.Color((((WheelPos % 21) + 1) * 6) + 127, 0, 255); break;
    case 11: return strip.Color(255, 0, 255 - (((WheelPos % 21) + 1) * 6)); break;
    default: return strip.Color(0, 0, 0); break;
  }
}
