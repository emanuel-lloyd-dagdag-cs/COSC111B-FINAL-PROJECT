#define THERMISTOR_PIN A0  // Thermistor pin
#define LED_PIN 8          // LED pin for blinking

const float TEMP_THRESHOLD = 50.0;  
const float BETA = 3950.0;              // Beta value of thermistor
const float RESISTANCE = 10.0;          // Value of pull-up resistor kΩ

float temperatureC;
bool isBlinking = false;            // Flag to control blinking state
unsigned long previousMillis = 0;   // Store last time LED was updated
const long blinkInterval = 100;     // Blink delay in milliseconds
bool ledState = LOW;                // Current LED state

void setup() {
  pinMode(LED_PIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Serial communication initialized");
  Serial.println("Temperature Monitoring System");
  Serial.println("Type 'stop' to stop LED blinking");
  Serial.println("----------------------------------");
}

// Function to read temperature using Steinhart-Hart Equation
float readTemperature() {
  int analogValue = analogRead(THERMISTOR_PIN);
  
  // Calculating temp in Celsius using Steinhart-Hart Equation
  float tempC = BETA / (log((1025.0 * RESISTANCE / analogValue - RESISTANCE) / RESISTANCE) + BETA / 298.0) - 273.0;
  return tempC;
}

void loop() {
  // Read temperature
  temperatureC = readTemperature();
  
  // Display temperature reading
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  
  // Check if threshold is met
  if (temperatureC >= TEMP_THRESHOLD && !isBlinking) {
    isBlinking = true;
    Serial.println("ALERT: Temperature threshold exceeded!");
    Serial.println("Type 'stop' to stop.");
  }
  
  // // LED blinking code
  if (isBlinking) {
    unsigned long currentMillis = millis();
    
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      
      // toggle led state
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    }
  }
  
  // Check for serial input
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');  // read until newline
    input.trim();                                  // remove whitespace
    input.toLowerCase();                           // convert to lowercase 
    
    if (input == "stop") {
      isBlinking = false;
      digitalWrite(LED_PIN, LOW);  // Turn off LED
      ledState = LOW;
      Serial.println("Blinking stopped!");
    }
  }
  
  delay(1000);  // Delay for temperature reading display
}
















