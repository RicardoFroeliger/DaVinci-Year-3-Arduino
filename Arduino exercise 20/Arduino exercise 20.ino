
/*
  NOTE: This exercise has not been completely finished yet.
  Instead of the safe locking after 3 failed tries within 2 minutes, 
  the safe locks after just 3 tries without looking how many time has passed in between.
*/

const int redLed = 11;
const int greenLed = 10;
const int button1 = 5;
const int button2 = 4;
const int button3 = 3;

// This are the correct numbers of the combination
const int correctCombinationNumber1 = 2;
const int correctCombinationNumber2 = 1;
const int correctCombinationNumber3 = 3;

// These are the numbers the user enters & more
int combinationNumber1 = NULL;
int combinationNumber2 = NULL;
int combinationNumber3 = NULL;
bool correctCombinationInserted = false;
int combinationFailedTries = 0;
bool safeLocked = false;

/* 
These are the settings for if the safe is locked
- safeLockedTime is the total time the safe is locked 
- safeLockedBlinkTime is the time the led goes off/on (500ms means 1 blink every 1s) 
*/
const int safeLockedTime = 3000; // 300_000
const int safeLockedBlinkTime = 250;
int safeLockedCurrentTime = 0;
unsigned long safeLockedBlinkPreviousTime = 0;


void insertCombinationNumber (int number) {

  // Inserts the combination numbers of the user in variables 
  // When all 3 numbers have been inserted it tests the combination and resets it for next try
  if(!safeLocked) {
    if(combinationNumber1 == NULL) combinationNumber1 = number;
    else if(combinationNumber2 == NULL) combinationNumber2 = number;
    else if(combinationNumber3 == NULL) {
      combinationNumber3 = number;
      insertCombination(combinationNumber1, combinationNumber2, combinationNumber3);
      resetCombination();
    }
  } else {
    Serial.println("Cannot enter combination while safe is temporarily locked!");
  }
}

void insertCombination (int number1, int number2, int number3) {
  Serial.print("Combination inserted: ");
  Serial.print(number1);
  Serial.print(number2);
  Serial.print(number3);

  // Checks the combination, prints if it's valid & locks the safe after 3 tries
  if(
    number1 == correctCombinationNumber1 
    && number2 == correctCombinationNumber2
    && number3 == correctCombinationNumber3
  ) {
    correctCombinationInserted = true;
    combinationFailedTries = 0;
    Serial.println(" | Correct combination, safe opened!");
  } else {
    correctCombinationInserted = false;
    combinationFailedTries++;
    
    Serial.print(" | Incorrect combination, ");
    Serial.print(3 - combinationFailedTries);
    if(3 - combinationFailedTries == 1) Serial.println(" try left!");
    else Serial.println(" tries left!");

    if(combinationFailedTries == 3) {
      combinationFailedTries = 0;
      safeLocked = true;
      Serial.println("Safe locked!");
    }
  }
}

void resetCombination() {
  combinationNumber1 = NULL;
  combinationNumber2 = NULL;
  combinationNumber3 = NULL;
}

void setup() {
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
}

void loop() {
  if(safeLocked) {

    // Unlocks safe & stops the blinking of the red LED when enough time has passed
    unsigned long safeLockedBlinkCurrentTime = millis();
    if(safeLockedCurrentTime < safeLockedTime) {
      // Blinks red LED without blocking code
      if(safeLockedBlinkCurrentTime - safeLockedBlinkPreviousTime >= safeLockedBlinkTime) {
        digitalWrite(redLed, digitalRead(redLed)^1);
        safeLockedBlinkPreviousTime = safeLockedBlinkCurrentTime;
        safeLockedCurrentTime += safeLockedBlinkTime;
      }
    } else {
      safeLockedCurrentTime = 0;
      safeLocked = false;
      Serial.println("Safe unlocked!");
    }
  } else {

    // Toggles LED's between green and red
    if(correctCombinationInserted) {
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, LOW);
    } else {
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, LOW);
    }
  }

  // Creates button functionalities
  if(digitalRead(button1) == LOW) {
    while(digitalRead(button1) == LOW) {}
    delay(100);
    insertCombinationNumber(1);
  }

  if(digitalRead(button2) == LOW) {
    while(digitalRead(button2) == LOW) {}
    delay(100);
    insertCombinationNumber(2);
  }

  if(digitalRead(button3) == LOW) {
    while(digitalRead(button3) == LOW) {}
    delay(100);
    insertCombinationNumber(3);
  }
}