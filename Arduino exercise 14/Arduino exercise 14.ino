int btn = A5;

void setup() {
  Serial.begin(9600);
  pinMode(btn, INPUT_PULLUP);
}

void loop() {
  if(digitalRead(btn) == LOW) {
    while(digitalRead(btn) == LOW) {}
    delay(100);
    Serial.println("Button pressed");
  }
}