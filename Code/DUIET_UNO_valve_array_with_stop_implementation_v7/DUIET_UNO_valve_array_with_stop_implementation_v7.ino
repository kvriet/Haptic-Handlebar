/* Code by Katrien van Riet - Jan 2022 */

#include <Servo.h>
#include <Wire.h>

// VARIABLES TO BE CHANGED //
int cols = 3; // Number of balloons
int rows = 12; // Number of values per balloon
int initialIntervalTime = 250;
int intervalDecrease = 50;
int timeIntervalInMilliseconds = initialIntervalTime;
int loopRepeat = 3;

int values[8][3][12] = {
  {{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1,}, {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0,}, {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,}}
  ,
  {{1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,}, {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0,}, {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1,}}
  ,
  {{1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0,}, {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0,}, {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0,}}
  ,
  {{1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0,}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}
  ,
  {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}, {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0,}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}
  ,
  {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}, {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0,}}
  ,
  {{1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0,}, {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}, {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}
  ,
  {{1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0,}, {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,}, {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0,}}
};

// VARIABLES TO LEAVE ALONE //
long currentTime;
long prevTime;
int index = 0;
int angleOpen = 0;
int angleClosed = 90;
int loopIncrementer = 0;
int wireValue;
boolean isStopped = true;
boolean isLoopFinished = false;

Servo servos[3];

void setup() {
  servos[0].attach(9);
  servos[1].attach(10);
  servos[2].attach(11);
  Serial.begin(9600);
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
}

void loop() {
  if (!isStopped) {
    if (!isLoopFinished) {
      currentTime = millis();
      if (currentTime - prevTime > timeIntervalInMilliseconds) {
        // Per time interval, loop through valves
        for (int i = 0; i < cols; i++) {
          if (values[wireValue - 1][i][index] == 0) {
            servos[i].write(angleClosed);
          } else if (values[wireValue - 1][i][index] == 1) {
            servos[i].write(angleOpen);
          }
          delay(5); // For stability
        }
        prevTime = currentTime;
        index++;
        if (index >= rows) {
          // If program is at end of row, loop back to front
          index = 0;
          loopIncrementer++;
          timeIntervalInMilliseconds -= intervalDecrease; // Every time the loop repeats, it is 25ms quicker per interval
        }
      }

      if (loopIncrementer >= loopRepeat) {
        loopIncrementer = 0;
        timeIntervalInMilliseconds = initialIntervalTime;
        isLoopFinished = true;
        closeAllServos();
      }
    }
  }
}

void closeAllServos() {
  for (int i = 0; i <= cols; i++) {
    servos[i].write(angleClosed);
    Serial.println("Close all servos");
  }
}

void receiveEvent(int bytes) {
  wireValue = Wire.read();    // read one character from the I2C
  isLoopFinished = false;
  if (wireValue == 0) {
    isStopped = true;
    closeAllServos();
    index = 0;
  }
  else {
    isStopped = false;
  }
}
