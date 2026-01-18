Laboratory Activity #7

This activity builds a web-controlled lighting system using a FastAPI Python server to communicate with an Arduino over USB. Users can toggle Red, Green, and Blue LEDs by visiting specific web URLs (API endpoints), which the server translates into serial commands for the hardware. Additionally, pressing physical buttons on the breadboard instantly changes the LED states locally and sends a "BUTTON_PRESSED" message back to the server, allowing the web application to monitor manual inputs.
