int sensorVal;
int sensorMaxVal = 1000; // 1023

int led1 = 12;
int led2 = 11;
int led3 = 10;
int led4 = 9;

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  delay(250);

  int sensorVal = analogRead(A0);
  Serial.println(sensorVal);
  
  for(int i = 1; i <= 4; i++) {
    if(sensorVal >= (sensorMaxVal / 4) * i) {
      digitalWrite(13 - i, HIGH); // pins 12 to 9
    } else {
      digitalWrite(13 - i, LOW);
    }
  }
}