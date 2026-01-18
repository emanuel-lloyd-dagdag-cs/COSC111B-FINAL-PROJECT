// LAB ACTIVITY 7 - Arduino with Minimal Button Support

constexpr int RED_PIN = 7;
constexpr int GREEN_PIN = 6;
constexpr int BLUE_PIN = 5;

constexpr int BTN_RED = 12;
constexpr int BTN_GREEN = 11;
constexpr int BTN_BLUE = 10;

bool redState = false;
bool greenState = false;
bool blueState = false;

bool lastRedBtn = HIGH;
bool lastGreenBtn = HIGH;
bool lastBlueBtn = HIGH;

void setup() {
  Serial.begin(9600);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  pinMode(BTN_RED, INPUT_PULLUP);
  pinMode(BTN_GREEN, INPUT_PULLUP);
  pinMode(BTN_BLUE, INPUT_PULLUP);

  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
}

void loop() {
  // -------- SERIAL CONTROL (FastAPI → Arduino) --------
  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd == '1') {
      redState = !redState;
      digitalWrite(RED_PIN, redState);
    }
    else if (cmd == '2') {
      greenState = !greenState;
      digitalWrite(GREEN_PIN, greenState);
    }
    else if (cmd == '3') {
      blueState = !blueState;
      digitalWrite(BLUE_PIN, blueState);
    }
    else if (cmd == 'O') {
      redState = greenState = blueState = false;
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(BLUE_PIN, LOW);
    }
  }

  // -------- BUTTON CONTROL (Arduino → FastAPI) --------
  bool redBtn = digitalRead(BTN_RED);
  bool greenBtn = digitalRead(BTN_GREEN);
  bool blueBtn = digitalRead(BTN_BLUE);

  if (redBtn == LOW && lastRedBtn == HIGH) {
    redState = !redState;
    digitalWrite(RED_PIN, redState);
    Serial.println("BUTTON_RED");
    delay(200);
  }

  if (greenBtn == LOW && lastGreenBtn == HIGH) {
    greenState = !greenState;
    digitalWrite(GREEN_PIN, greenState);
    Serial.println("BUTTON_GREEN");
    delay(200);
  }

  if (blueBtn == LOW && lastBlueBtn == HIGH) {
    blueState = !blueState;
    digitalWrite(BLUE_PIN, blueState);
    Serial.println("BUTTON_BLUE");
    delay(200);
  }

  lastRedBtn = redBtn;
  lastGreenBtn = greenBtn;
  lastBlueBtn = blueBtn;
}
