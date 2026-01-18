#include "lab_act6_functions.h"

// ================= STATES =================
bool RED_LED_STATE = false;
bool GREEN_LED_STATE = false;
bool BLUE_LED_STATE = false;

bool BUTTON1_LAST = HIGH;
bool BUTTON2_LAST = HIGH;
bool BUTTON3_LAST = HIGH;

// for timer
unsigned long lastButtonTime = 0;
unsigned long menuTimer = 0;
bool waitForMenu = false;

// pin setup
void setup() {
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);

    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);
    pinMode(BUTTON3_PIN, INPUT_PULLUP);

    Serial.begin(9600);

    // Print menu at startup
    PRINT_MENU();
}

// loop
void loop() {
    READ_BUTTONS();
    READ_SERIAL();
    MENU_HANDLER();
}
