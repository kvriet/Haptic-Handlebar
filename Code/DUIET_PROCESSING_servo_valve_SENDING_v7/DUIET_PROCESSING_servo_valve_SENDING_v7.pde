/*
 Code by Katrien van Riet - Jan 2022
 */

import processing.serial.*;

Serial myPort;

int cols = 4;
int rows = 3;

Button[] buttons;

void setup() {  
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[1], 9600);
  myPort.buffer(1);
  size(650, 500);
  background(255);
  
  buttons = new Button[cols*rows];

  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      int index = y*cols+x;
      buttons[index] = new Button(x*150+100, y*150+100, index);
    }
  }
}

void draw() {
  for (int i = 0; i < buttons.length; i++) {
    buttons[i].show();
  }
}
