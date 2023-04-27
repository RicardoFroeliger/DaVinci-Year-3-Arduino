const int btn = 12;
const int led = 11;

void setup() {
  pinMode(btn, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  if(digitalRead(btn) == LOW) {
    while(digitalRead(btn) == LOW);
    delay(100);
    digitalWrite(led, digitalRead(led)^1);
  }
}