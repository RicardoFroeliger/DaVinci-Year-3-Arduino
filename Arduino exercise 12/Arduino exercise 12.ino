// the setup function runs once when you press reset or power the board
void setup() {
  for(int i = 10; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
}

// the loop function runs over and over again forever
void loop() {
  for(int i = 10; i <= 13; i++) { // turn all LED's off
    digitalWrite(i, LOW);
  }
  delay(1000); // wait 1 second

  for(int i = 10; i <= 13; i++) {
    digitalWrite(i, HIGH); // turn each LED on after waiting 1 second
    delay(1000);
  }
}
