class Valve {
  boolean isOpen = false;
  float posX, posY;
  int number;

  Valve (float x_, float y_, int n_) {
    posX = x_; 
    posY = y_;
    number = n_;
  }

  void run() { 
    // Check whether to move to next time increment
    if (values[number][index] == 0) {
      // Check whether servo should be open/closed
      isOpen = false;
    } else {
      isOpen = true;
    }
    //println(index);

    switch(number) {
    case 0:
      fill(0, 255, 0);
      break;
    case 1:
      fill(0, 50, 255);
      break;
    case 2:
      fill(255, 50, 150);
      break;
    }

    if (isOpen) {    
      arc(posX, posY, 60, 60, PI, TWO_PI);
    } else if (!isOpen) {
      arc(posX, posY, 30, 30, PI, TWO_PI);
    }
  }
}
