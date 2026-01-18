#ifndef LAB_ACT6_FUNCTIONS_H
#define LAB_ACT6_FUNCTIONS_H

#include <Arduino.h>

// Pins
const int RED_LED_PIN   = 7;
const int GREEN_LED_PIN = 6;
const int BLUE_LED_PIN  = 5;

const int BUTTON1_PIN = 12;
const int BUTTON2_PIN = 11;
const int BUTTON3_PIN = 10;

// States
extern bool RED_LED_STATE;
extern bool GREEN_LED_STATE;
extern bool BLUE_LED_STATE;

extern bool BUTTON1_LAST;
extern bool BUTTON2_LAST;
extern bool BUTTON3_LAST;

// Timing
extern unsigned long lastButtonTime;
extern unsigned long menuTimer;
extern bool waitForMenu;

const unsigned long DEBOUNCE_DELAY = 150;
const unsigned long MENU_DELAY = 5000;

// Menu
inline void PRINT_MENU() {
    Serial.println("\nChoose an option:");
    Serial.println("button1 - Red");
    Serial.println("button2 - Green");
    Serial.println("button3 - Blue");
}

// Buttons
inline void READ_BUTTONS() {
    if (millis() - lastButtonTime < DEBOUNCE_DELAY) return;

    bool b1 = digitalRead(BUTTON1_PIN);
    bool b2 = digitalRead(BUTTON2_PIN);
    bool b3 = digitalRead(BUTTON3_PIN);

    if (BUTTON1_LAST == HIGH && b1 == LOW) {
        Serial.println("R");
        lastButtonTime = millis();
        menuTimer = millis();
        waitForMenu = true;
    }
    else if (BUTTON2_LAST == HIGH && b2 == LOW) {
        Serial.println("G");
        lastButtonTime = millis();
        menuTimer = millis();
        waitForMenu = true;
    }
    else if (BUTTON3_LAST == HIGH && b3 == LOW) {
        Serial.println("B");
        lastButtonTime = millis();
        menuTimer = millis();
        waitForMenu = true;
    }

    BUTTON1_LAST = b1;
    BUTTON2_LAST = b2;
    BUTTON3_LAST = b3;
}

// Menu timer
inline void MENU_HANDLER() {
    if (waitForMenu && millis() - menuTimer >= MENU_DELAY) {
        PRINT_MENU();
        waitForMenu = false;
    }
}

// Serial input
inline void READ_SERIAL() {
    while (Serial.available()) {
        char c = Serial.read();

        if (c == '\n' || c == '\r' || c == ' ') continue;

        if (c == '1') {
            RED_LED_STATE = !RED_LED_STATE;
            digitalWrite(RED_LED_PIN, RED_LED_STATE);
        }
        else if (c == '2') {
            GREEN_LED_STATE = !GREEN_LED_STATE;
            digitalWrite(GREEN_LED_PIN, GREEN_LED_STATE);
        }
        else if (c == '3') {
            BLUE_LED_STATE = !BLUE_LED_STATE;
            digitalWrite(BLUE_LED_PIN, BLUE_LED_STATE);
        }
    }
}

#endif
