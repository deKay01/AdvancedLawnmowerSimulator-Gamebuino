// ALS - Advanced Lawnmower Simulator
const char version[] = "0.01";
// deKay - @deKay01 andyk@lofi-gaming.org.uk

// Original version by Duncan McDonald

#include <SPI.h>
#include <Gamebuino.h>

Gamebuino gb;

extern const byte font3x3[]; //a really tiny font
extern const byte font3x5[]; //a small but efficient font (default)
extern const byte font5x7[]; //a large, comfy font

extern const byte PROGMEM mowerman[];
extern const byte PROGMEM cutgrass[];
extern const byte PROGMEM grass[];
extern const byte PROGMEM logo[];
extern const byte PROGMEM shed[];

int px;
int py;
boolean finished;

void setup() {
  gb.begin();
  gb.titleScreen(logo);
  px = 72;
  py = 40;
  finished = false;
}

void loop() {
  while (finished == false) {
    if (gb.update()) {

      boolean moved = false;
      if (gb.buttons.repeat(BTN_A, 1)) {
        moved = true;
      }

      if (moved) {
        movePlayer(px, py);
      }

      int pdx = px + 16;
      drawGrass(px, py, pdx);
      gb.display.drawBitmap(0, 0, shed);
      gb.display.drawBitmap(px, py, mowerman);

    }
  }
  while (true) {
    if (gb.update()) {
    }
  }
}

void movePlayer(int &x, int &y) {
  x--;
  if (x < (-16)) {
    y = y - 8;
    x = 72;
  }
  if (y < 16){
    gb.popup(F("Well Mown!"), 60);
    finished = true;
  }
}

void drawGrass(int &x, int &y, int &z) {
  
  // fill all the unmown rows
  for (int yi = 2; yi < (y/8); yi++) {
    for (int i = 0; i < 10; i++) {
      gb.display.drawBitmap(i * 8, yi * 8, grass);
    }
  }
  
  // fill unmown bits of current row
  for (int xi = 0; xi < x / 8 + 1; xi++) {
    gb.display.drawBitmap(xi * 8, y, grass);
  }
  
  // fill mown bits of current row
  
  for (int xi = x/8 + 2; xi < 10; xi++) {
    gb.display.drawBitmap(xi * 8, y, cutgrass);
  }
  
  // fill mown bits of mown rows
  for (int yi = y/8 + 1; yi < 6; yi++) {
    for (int i = 0; i < 10; i++) {
      gb.display.drawBitmap(i * 8, yi * 8, cutgrass);
    }
  }
}

