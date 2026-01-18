const int PHOTO_PIN = A0;      
const int RED_LED_PIN = 13;    
const int YELLOW_LED_PIN = 12; 
const int GREEN_LED_PIN = 11;  

const int MODE_MANUAL = 0;
const int MODE_AUTOMATIC = 1;

int currentMode = MODE_MANUAL; // Default mode is Manual

int lowThreshold_manual = 40; // Default low threshold for Manual Mode
int highThreshold_manual = 70; // Default high threshold for Manual Mode

// Fixed thresholds for Automatic Mode
const int LOW_THRESHOLD_AUTO = 40;
const int HIGH_THRESHOLD_AUTO = 70;

unsigned long lastPrintTime = 0;
const long printInterval = 1000; // 1 second

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }

 
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);

  // Print startup messages
  Serial.println("--- Light Level Controller Initialized ---");
  Serial.println("Default mode: MANUAL");
  Serial.println("Type 'MODE AUTO' to switch to automatic mode.");
  Serial.println("In MANUAL mode, use 'SET LOW xx' or 'SET HIGH xx' to change thresholds.");
  Serial.println("------------------------------------------");
}

void loop() {
  // Check for user commands
  handleSerialCommands();

  // Run sensor reading and LED update every second
  unsigned long currentTime = millis();
  if (currentTime - lastPrintTime >= printInterval) {
    lastPrintTime = currentTime;
    
    int sensorValue = analogRead(PHOTO_PIN); // Read 0-1023
    // Use map() to convert the 0-1023 range to a 0-100% range
    int intensityPercent = map(sensorValue, 0, 1023, 0, 100); 

    String activeLED = "None";
    String environment = "N/A"; // Only used in AUTO mode

    if (currentMode == MODE_AUTOMATIC) {
      if (intensityPercent <= LOW_THRESHOLD_AUTO) {
        activeLED = "Green";
        environment = "Cloudy";
      } else if (intensityPercent <= HIGH_THRESHOLD_AUTO) {
        activeLED = "Yellow";
        environment = "Clear";
      } else {
        activeLED = "Red";
        environment = "Clear";
      }

    } else {
      if (intensityPercent <= lowThreshold_manual) {
        activeLED = "Green";
      } else if (intensityPercent <= highThreshold_manual) {
        activeLED = "Yellow";
      } else {
        activeLED = "Red";
      }
    }

    setLEDs(activeLED); // Update the LEDs
    printStatus(intensityPercent, activeLED, environment); // Print to serial
  }
}

// Checks for and processes incoming Serial commands
void handleSerialCommands() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();           // Remove whitespace
    command.toUpperCase();    // Make case-insensitive

    if (command == "MODE AUTO") {
      currentMode = MODE_AUTOMATIC;
      Serial.println(">>> Switched to AUTOMATIC Mode");

    } else if (command == "MODE MANUAL") {
      currentMode = MODE_MANUAL;
      Serial.println(">>> Switched to MANUAL Mode");

    } else if (command.startsWith("SET LOW ")) {
      if (currentMode == MODE_MANUAL) {
        int newLow = command.substring(8).toInt(); // Get number after "SET LOW "
        if (newLow >= 0 && newLow < highThreshold_manual) {
          lowThreshold_manual = newLow;
          Serial.print(">>> New LOW threshold set to: ");
          Serial.println(lowThreshold_manual);
        } else {
          Serial.println(">>> Error: Invalid value. LOW must be < HIGH threshold.");
        }
      } else {
        Serial.println(">>> Error: Thresholds can only be set in MANUAL mode.");
      }
      
    } else if (command.startsWith("SET HIGH ")) {
      if (currentMode == MODE_MANUAL) {
        int newHigh = command.substring(9).toInt(); // Get number after "SET HIGH "
        if (newHigh > lowThreshold_manual && newHigh <= 100) {
          highThreshold_manual = newHigh;
          Serial.print(">>> New HIGH threshold set to: ");
          Serial.println(highThreshold_manual);
        } else {
          Serial.println(">>> Error: Invalid value. HIGH must be > LOW threshold and <= 100.");
        }
      } else {
        Serial.println(">>> Error: Thresholds can only be set in MANUAL mode.");
      }

    } else {
      Serial.println(">>> Error: Wrong Command");
    }
  }
}

// Controls the LEDs, ensuring only one is on at a time
void setLEDs(String ledToActivate) {
  // Turn all LEDs off
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);

  // Turn the correct one on
  if (ledToActivate == "Green") {
    digitalWrite(GREEN_LED_PIN, HIGH);
  } else if (ledToActivate == "Yellow") {
    digitalWrite(YELLOW_LED_PIN, HIGH);
  } else if (ledToActivate == "Red") {
    digitalWrite(RED_LED_PIN, HIGH);
  }
}

// Prints the current system status to the Serial Monitor
void printStatus(int intensity, String led, String env) {
  Serial.print("Light Intensity: ");
  Serial.print(intensity); 
  Serial.println("%");

  Serial.print("Active LED: ");
  Serial.println(led);

  Serial.print("Current Mode: ");
  Serial.println(currentMode == MODE_AUTOMATIC ? "Automatic" : "Manual");

  Serial.print("Environment: ");
  Serial.println(env);
  
  Serial.println("--------------------");
}