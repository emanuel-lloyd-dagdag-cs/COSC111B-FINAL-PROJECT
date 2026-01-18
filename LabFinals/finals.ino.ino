// PIN DEFINITIONS
const int buttonPin = 2; // The Button

// VARIABLES
int buttonState = HIGH;      
int lastButtonState = HIGH;   
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;    

// Your Identifier
String groupNumber = "GROUP_4"; 

void setup() {
  // Use internal resistor (No external resistor needed)
  pinMode(buttonPin, INPUT_PULLUP); 
  Serial.begin(9600); 
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Debounce Logic (Filters out noise)
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // INPUT_PULLUP means LOW is "Pressed"
      if (buttonState == LOW) {
        Serial.println(groupNumber); 
      }
    }
  }
  lastButtonState = reading;
}