#define humidity_sensor_pin A1
#define humidity_sensor_vcc 13
#define relais_pin 2
#define second 1000 // 1000 ms
#define secondsInHour 3600
#define targetHumidity 600

void setup() {
  // Init the humidity sensor board
  pinMode(humidity_sensor_vcc, OUTPUT);
  digitalWrite(humidity_sensor_vcc, LOW);
  pinMode(relais_pin, OUTPUT);
  digitalWrite(relais_pin, LOW);
}

void water(int delta) {
  int sleepTime = 20;
  if (delta > 500) {
    sleepTime = 60;
  } else if (delta > 400) {
    sleepTime = 45;
  } else if (delta > 300) {
    sleepTime = 35;
  } else if (delta > 200) {
    sleepTime = 30;
  } else if (delta > 100) {
    sleepTime = 25;
  }
  digitalWrite(relais_pin, HIGH);
  for (int i = 0; i < sleepTime; i++) {
    delay(second);
  }
  digitalWrite(relais_pin, LOW);
}

inline int read_humidity_sensor() {
  int measuringDelay = 500;
  digitalWrite(humidity_sensor_vcc, HIGH);
  delay(measuringDelay);
  int value = analogRead(humidity_sensor_pin);
  digitalWrite(humidity_sensor_vcc, LOW);

  return 1023 - value;
}

void sleepHours(int hours) {
  for (int h = 0; h < hours; h++) {
    for (int i = 0; i < secondsInHour; i++) {
      delay(second); // 1s
    }
    // make sure that everything is off
    digitalWrite(humidity_sensor_vcc, LOW);
    digitalWrite(relais_pin, LOW);
  }
}

void loop() {
  int humidity = read_humidity_sensor();

  if (humidity < targetHumidity) {
    water(targetHumidity - humidity);
  }

  sleepHours(12);
}
