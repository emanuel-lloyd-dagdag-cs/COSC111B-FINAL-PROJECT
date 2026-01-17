int ledPins[] = {8, 9, 10, 11, 12};
int numLeds = 5;

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < numLeds; i++) {
    for (int brightness = 0; brightness <= 255; brightness++) {
      analogWrite(ledPins[i], brightness);
      delay(5);
    }
  delay(1000);
  }

  for (int i = 0; i < numLeds; i++) {
    for (int brightness = 255; brightness >= 0; brightness--) {
      analogWrite(ledPins[i], brightness);
      delay(5);
    }
  }
  delay(1000);
}



