/*
 Code by Katrien van Riet - Jan 2022
 */

int cols = 3; // Number of balloons
long currentTime;
long prevTime; 
int index = 0;

/* EXAMPLE
 int[][][] values = 
 {  {  {1,100},{1,100},{1,100},{1,100}  },    // number 1
 {  {0,100},{1,100},{1,100},{1,100}  },    // number 2
 {  {0,100},{0,100},{0,100},{1,100}  }  }  // number 3
 ;    // index1, 2    ,  3    ,  4
 */

// Place your array and time interval here
int timeIntervalInMilliseconds = 250;

int[][] values = 
  {{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,},{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,},{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,}}                    
  ;


Valve[] valves;

void setup() {
  size(400, 400);
  fill(255);
  noStroke();
  valves = new Valve[cols];
  for (int x = 0; x < cols; x++) {
    valves[x] = new Valve(100+100*x, 150+100, x);
  }
}

void draw() {  
  currentTime = millis(); 
  if (currentTime - prevTime > timeIntervalInMilliseconds) {
    background(255);
    for (int i = 0; i < cols; i++) {
      valves[i].run();
    }
    prevTime = currentTime;
    index++;
    if (index >= values[0].length) { 
      // If program is at end of row, loop back to front
      index = 0;
      background(255);
    }
  }
}
