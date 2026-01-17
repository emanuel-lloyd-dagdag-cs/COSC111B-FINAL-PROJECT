int ledPin[] = {12,11,10,9,8};
int numLeds = 5;
void setup() {


  for(int i = 0; i<numLeds; i++){
    pinMode(ledPin[i], OUTPUT);
  }

}

void loop() {

  for(int i = 0; i < numLeds;i++){
    digitalWrite(ledPin[i], HIGH);
    delay(1000);
  }
  for(int i = 0; i < numLeds;i++){
    digitalWrite(ledPin[i], LOW);
    delay(1000);
  }               
}