class Button {  
  float posX, posY;
  float radius = 100;
  int number;

  Button (float x_, float y_, int n_) {  
    posX = x_; 
    posY = y_;
    number = n_;
    textAlign(CENTER, CENTER);
    textSize(40);
    stroke(0);
  } 

  void show() {
    if (number > 0) {
      fill(230, 240, 255);    
      circle(posX, posY, radius);
      fill(0);
      text(number, posX, posY-3);
    } else {
      fill(230, 240, 255);    
      circle(posX, posY, radius);
      fill(0);
      text("STOP", posX, posY-3);
    }
  }

  void clicked(float x_, float y_) {
    float distance = dist(posX, posY, x_, y_);
    if (distance < radius/2) {     
      myPort.write(number);
      pressed();
    }
  }

  void pressed() {
    fill(100, 100, 255);    
    circle(posX, posY, radius);
    fill(0);
    text(number+1, posX, posY);
  }
}

void mousePressed() {
  for (int i = 0; i < buttons.length; i++) {
    buttons[i].clicked(mouseX, mouseY);
  }
}

void keyPressed() {
  switch(key) {
  case '1': 
    myPort.write(1);
    buttons[1].pressed();
    break;
  case '2': 
    myPort.write(2);
    buttons[2].pressed();
    break;
  case '3': 
    myPort.write(3);
    buttons[3].pressed();
    break;
  case '4': 
    myPort.write(4);
    buttons[4].pressed();
    break;
  case '5': 
    myPort.write(5);
    buttons[5].pressed();
    break;
  case '6': 
    myPort.write(6);
    buttons[6].pressed();
    break;
  case '7': 
    myPort.write(7);
    buttons[7].pressed();
    break;
  case '8': 
    myPort.write(8);
    buttons[8].pressed();
    break;
  //case '9': 
  //  myPort.write(9);
  //  buttons[9].pressed();
  //  break;
  case '0': 
    myPort.write(0);
    buttons[0].pressed();
    break;
  }
  if (key == ' ') {
    myPort.write(0);
    buttons[0].pressed();
  }
}
