#ifndef LAB_ACT5_H
#define LAB_ACT5_H

#include <Arduino.h>

// Pin definitions
constexpr int RED_PIN = 8;
constexpr int GREEN_PIN = 9;
constexpr int BLUE_PIN = 10;

// LED states (defined here but declared inline-safe)
static bool redState = false;
static bool greenState = false;
static bool blueState = false;

// Initialize LEDs
inline void initLEDs() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);

  Serial.println("LEDs initialized");
}

// Toggle red LED
inline void toggleRed() {
  redState = !redState;
  digitalWrite(RED_PIN, redState);

  Serial.println(redState ? "RED ON" : "RED OFF");
}

// Toggle green LED
inline void toggleGreen() {
  greenState = !greenState;
  digitalWrite(GREEN_PIN, greenState);

  Serial.println(greenState ? "GREEN ON" : "GREEN OFF");
}

// Toggle blue LED
inline void toggleBlue() {
  blueState = !blueState;
  digitalWrite(BLUE_PIN, blueState);

  Serial.println(blueState ? "BLUE ON" : "BLUE OFF");
}

// All on
inline void allOn() {
  redState = true;
  greenState = true;
  blueState = true;

  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);

  Serial.println("ALL LEDs ON");
}

// All off
inline void allOff() {
  redState = false;
  greenState = false;
  blueState = false;

  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);

  Serial.println("ALL LEDs OFF");
}

// Process command
inline void processCommand(char cmd) {
  cmd = toupper(cmd);

  switch (cmd) {
    case 'R': toggleRed(); break;
    case 'G': toggleGreen(); break;
    case 'B': toggleBlue(); break;
    case 'A': allOn(); break;
    case 'O': allOff(); break;
    default:
      Serial.print("Invalid command: ");
      Serial.println(cmd);
  }
}

#endif
