const int led = 12; // we use pin 12 for the LED

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  // initialize digital pin 12 as an output.
  pinMode(led, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println((String)"LED is now: " + !digitalRead(led));
  
  digitalWrite(led, !digitalRead(led));     // put the opposite value of the current value
  delay(1304);                              // wait for 304 milliseconds
}
