#include "lab_act5.h"

void setup() {
  Serial.begin(9600);
  initLEDs();

  Serial.println("Arduino LED Control Ready");
  Serial.println("Commands: R, G, B, A, O");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command != '\n' && command != '\r') {
      processCommand(command);
    }
  }
}
