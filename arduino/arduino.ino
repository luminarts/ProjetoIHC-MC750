#include <Servo.h>
#define SPEED_OF_SOUND 0.034 // meters/microsecond
#define STOP_SERVO 90 // Neutral position to stop the servo
#define MAX_SPEED 110
#define MAX_DISTANCE 100

// Pins
const int servoPin = 2;
const int trigPin = 3;  // HC-SR04 trigger pin
const int echoPin = 4;  // HC-SR04 echo pin
const int buttonEarthPin = 5;
const int buttonMoonPin = 6;
const int buttonSunPin = 7;
const int ledEarthPin = 8;
const int ledMoonPin = 9;
const int ledSunPin = 10;

Servo myServo;

long duration;
int distance;
const int distanceThreshold = MAX_DISTANCE; // centimeters

// Button and LED states
bool earthSelected = false;
bool moonSelected = false;
bool sunSelected = false;
bool lastEarthButtonState = HIGH;
bool lastMoonButtonState = HIGH;
bool lastSunButtonState = HIGH;
int lastPressedButton = -1;

// Timing variables
unsigned long previousMillisSensor = 0;
const long sensorInterval = 100; // Time between sensor readings in milliseconds
unsigned long previousMillisServo = 0;
const long servoInterval = 50; // Time between servo speed adjustments

int currentSpeed = STOP_SERVO;
const int speedStep = 1;  // Step size for smooth speed adjustment

void setup()
{
  Serial.begin(9600); // debugging purposes

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonEarthPin, INPUT_PULLUP); // internal pull-up resistors
  pinMode(buttonMoonPin, INPUT_PULLUP);
  pinMode(buttonSunPin, INPUT_PULLUP);
  pinMode(ledEarthPin, OUTPUT);
  pinMode(ledMoonPin, OUTPUT);
  pinMode(ledSunPin, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(STOP_SERVO);  // Neutral position to stop. Check if this is the correct value for the servo used.
  
  digitalWrite(ledEarthPin, LOW);
  digitalWrite(ledMoonPin, LOW);
  digitalWrite(ledSunPin, LOW);
}

void loop()
{
  handleButtons();

  unsigned long currentMillis = millis();

  // non-blocking delay
  if (currentMillis - previousMillisSensor >= sensorInterval) {
    previousMillisSensor = currentMillis;
    handleSensor();
    adjustServoSpeed();
  }
}

void handleButtons() {
  // Earth
  bool currentEarthButtonState = digitalRead(buttonEarthPin);
  if (currentEarthButtonState == LOW && lastEarthButtonState == HIGH) {
    earthSelected = !earthSelected; // Toggle Earth LED state
    moonSelected = false;
    sunSelected = false;
    updateLEDs();
    logButtonPress(buttonEarthPin);
  }

  lastEarthButtonState = currentEarthButtonState;

  // Moon
  bool currentMoonButtonState = digitalRead(buttonMoonPin);
  if (currentMoonButtonState == LOW && lastMoonButtonState == HIGH) {
    moonSelected = !moonSelected; // Toggle Moon LED state
    earthSelected = false;
    sunSelected = false;
    updateLEDs();
    logButtonPress(buttonMoonPin);
  }

  lastMoonButtonState = currentMoonButtonState;

  // Sun
  bool currentSunButtonState = digitalRead(buttonSunPin);
  if (currentSunButtonState == LOW && lastSunButtonState == HIGH) {
    sunSelected = !sunSelected; // Toggle Sun LED state
    earthSelected = false;
    moonSelected = false;
    updateLEDs();
    logButtonPress(buttonSunPin);
  }

  lastSunButtonState = currentSunButtonState;
}

void updateLEDs() {
  digitalWrite(ledEarthPin, earthSelected ? HIGH : LOW);
  digitalWrite(ledMoonPin, moonSelected ? HIGH : LOW);
  digitalWrite(ledSunPin, sunSelected ? HIGH : LOW);
}

void logButtonPress(int buttonPin) {
  if (lastPressedButton != buttonPin) {
    Serial.println(buttonPinMask(buttonPin));
    lastPressedButton = buttonPin;
  }
}

int buttonPinMask(int buttonPin) {
  switch(buttonPin) {
    case buttonSunPin:
      return 1;
    case buttonEarthPin:
      return 2;
    case buttonMoonPin:
      return 3;
    default:
      Serial.println("An error occurred");
      return -1;
  }
}

void handleSensor() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000); // Timeout after 30ms (30,000 microseconds)

  if (duration == 0) {
    distance = -1;
  } else {
    distance = duration * SPEED_OF_SOUND / 2; // divide by 2 to cutoff the return distance of echo
  }
}

void adjustServoSpeed() {
  if (distance > 0 && distance < distanceThreshold) {
    if (currentSpeed < MAX_SPEED) {
      currentSpeed += speedStep; // Gradually increase speed
    }
  } else {
    if (currentSpeed > STOP_SERVO) {
      currentSpeed -= speedStep; // Gradually decrease speed to neutral
    }
  }
  
  // Ensure speed stays within bounds
  currentSpeed = constrain(currentSpeed, STOP_SERVO, MAX_SPEED);
  myServo.write(currentSpeed);
}