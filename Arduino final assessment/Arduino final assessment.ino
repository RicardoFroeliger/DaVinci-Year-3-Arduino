const int led1 = 8;
const int led2 = 9;
const int led3 = 10;
const int ledRED = 11;
const int button = 12;

const int trigPin = 4;
const int echoPin = 3;
long duration;
int distance;
int maxMeasuredDistance = 0;

const int sensorOutputInterval = 500;
unsigned long sensorOutputPrevious = 0;

void measureSensorDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343)/2;

  if(distance > 200) distance = 200;

  if(distance > maxMeasuredDistance) {
    maxMeasuredDistance = distance;
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(ledRED, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  unsigned long sensorOutputCurrent = millis();
  if(sensorOutputCurrent - sensorOutputPrevious > sensorOutputInterval) {
    measureSensorDistance();
    Serial.print("Distance: ~");
    Serial.print(distance * 10);
    Serial.println("mm");
    sensorOutputPrevious = sensorOutputCurrent;
  }

  if(digitalRead(button) == LOW) {
    while(digitalRead(button) == LOW) {}
    delay(100);
    Serial.print("Max measured distance is: ");
    Serial.print(maxMeasuredDistance * 10);
    Serial.println("mm");
  } 

  if(distance >= 200) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(ledRED, HIGH);
  } 
  else if(distance > 50) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(ledRED, LOW);
  } 
  else if(distance > 20) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(ledRED, LOW);
  } else {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(ledRED, LOW);
  }
}