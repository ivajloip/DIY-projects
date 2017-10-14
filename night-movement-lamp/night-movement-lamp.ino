#define ledPin 2
#define photocellPin A0
#define pirPin 3
#define lightNeededThreshold 25
#define second 1000

#define calibrationTime 10

//the time when the sensor outputs a low impulse
long unsigned int switchToLowTime;
long unsigned int pause = 10000;
boolean lockLow = true;

void setup() {
  pinMode(ledPin, OUTPUT); //set ledPin output
  digitalWrite(ledPin, LOW);

  pinMode(pirPin, INPUT);
  // sensor calibration
  for(int i = 0; i < calibrationTime; i++) {
    delay(second);
  }
  delay(50);
}

inline void handleMove() {
  int val = analogRead(photocellPin);
  if (val <= lightNeededThreshold) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void loop() {
  // movement was detected
  if (digitalRead(pirPin) == HIGH) {
    if (lockLow) {
      //makes sure we wait for a transition to LOW before any further output is made:
      lockLow = false;
      handleMove();
      delay(second);
    }
    switchToLowTime = millis();
    delay(100);
  } else {
    // if the sensor is low for more than the given pause,
    // we assume that no more motion is going to happen
    if (!lockLow && millis() - switchToLowTime > pause) {
      lockLow = true;
      digitalWrite(ledPin, LOW);
      delay(50);
    }
  }
}
