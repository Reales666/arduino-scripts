#include "Arduino_LED_Matrix.h"
#include "animation.h"

ArduinoLEDMatrix matrix;

void setup() {
  Serial.begin(115200);
  matrix.begin();
}

void loop() {
  matrix.loadFrame(frame1);
  delay(500);
  matrix.loadFrame(frame2);
  delay(500);
  matrix.loadFrame(frame3);
  delay(500);
  matrix.loadFrame(frame4);
  delay(500);
  matrix.loadFrame(frame5);
  delay(500);
  matrix.loadFrame(frame6);
  delay(500);
  matrix.loadFrame(frame7);
  delay(500);
  matrix.loadFrame(frame8);
  delay(500);
  matrix.loadFrame(frame9);
  delay(500);
  matrix.loadFrame(frame10);
  delay(500);
  matrix.loadFrame(frame11);
  delay(500);
  matrix.loadFrame(frame12);
  delay(500);
  matrix.loadFrame(frame13);
  delay(500);
  matrix.loadFrame(frame14);
  delay(500);
  matrix.loadFrame(frame15);
  delay(500);
  matrix.loadFrame(frame16);
  delay(500);
  matrix.loadFrame(frame17);
  delay(500);
  matrix.loadFrame(frame18);
  delay(500);
  matrix.loadFrame(frame19);
  delay(500);
  matrix.loadFrame(frame20);
  delay(500);
  matrix.loadFrame(frame21);
  delay(500);
  matrix.loadFrame(frame22);
  delay(500);
  matrix.loadFrame(frame23);
  delay(500);
  matrix.loadFrame(frame24);
  delay(500);
  matrix.loadFrame(frame25);
  delay(500);
}
