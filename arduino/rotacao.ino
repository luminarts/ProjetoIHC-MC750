#include <Servo.h>

// Parâmetros do sensor de ultrassom
const int MIN_DISTANCE = 80;
const int usSensorTrigPin = 3;
const int usSensorEchoPin = 4;
int lastReadings[5];
int index = 0;
bool isHigherThanMax = false;
float duration, distance;

// Parâmetros do motor
const int servoPin = 9;
Servo mainServo;
int servoSpeed = 90;
const int NO_SPEED = 90;
const int LOW_SPEED = 100;
const int MEDIUM_SPEED = 105;

// Parâmetros dos botões
const int earthButtonPin = 5;
const int moonButtonPin = 6;
const int sunButtonPin = 7;
const int ledSunPin = 16;
const int ledEarthPin = 15;
const int ledMoonPin = 10;

bool lastEarthButtonState = HIGH;
bool lastSunButtonState = HIGH;
bool lastMoonButtonState = HIGH;
bool earthSelected = false;
bool moonSelected = false;
bool sunSelected = false;
int lastPressedButton = -1;

void setup() {

  pinMode(usSensorTrigPin, OUTPUT);
  pinMode(usSensorEchoPin, INPUT);
  Serial.begin(9600);
  mainServo.attach(servoPin);
  mainServo.write(servoSpeed);

  for (int i = 0; i < 5; i++) {
    lastReadings[i] = 0;
  }

  pinMode(earthButtonPin, INPUT_PULLUP);
  pinMode(moonButtonPin, INPUT_PULLUP);
  pinMode(sunButtonPin, INPUT_PULLUP);

}

void loop() {

  // Ativar sensor de ultrassom
  digitalWrite(usSensorTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(usSensorTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(usSensorTrigPin, LOW);

  // Leitura do receptor (conectado em echo)
  duration = pulseIn(usSensorEchoPin, HIGH);
  distance = duration*0.0343/2;

  // Serial.print("Distance: ");
  // Serial.println(distance);

  // Armazenamento do valor em uma lista p/ controlar rotação
  index = (index + 1) % 5;
  lastReadings[index] = distance;

  // Serial.print("Last 5 readings: ");

  // Verifica se há algum valor menor que o valor permitido
  // (basicamente garante que não vai ficar rodando que nem maluco)
  for (int i = 0; i < 5; i++) {
    Serial.print(lastReadings[i]);
    Serial.print(" ");
    if (lastReadings[i] > 80) {
      isHigherThanMax = true;
    } else {
      isHigherThanMax = false;
    }
  }

  if (isHigherThanMax == false && arrayHasOnlyZero(lastReadings) == false) {
    servoSpeed = MEDIUM_SPEED;
    mainServo.write(servoSpeed);
  } else {
    servoSpeed = NO_SPEED;
    mainServo.write(servoSpeed);
  }

  // Lógica dos botões
  // Terra
  bool currentEarthButtonState = digitalRead(earthButtonPin);
  if (currentEarthButtonState == LOW && lastEarthButtonState == HIGH) {
    earthSelected = !earthSelected; // Toggle Earth LED state
    moonSelected = false;
    sunSelected = false;
    updateLEDs();
    logButtonPress(earthButtonPin);
  }

  // Lua
  bool currentMoonButtonState = digitalRead(moonButtonPin);
  if (currentMoonButtonState == LOW && lastMoonButtonState == HIGH) {
    moonSelected = !moonSelected;
    earthSelected = false;
    sunSelected = false;
    updateLEDs();
    logButtonPress(moonButtonPin);
  }
  
  // Sun
  bool currentSunButtonState = digitalRead(sunButtonPin);
  if (currentSunButtonState == LOW && lastSunButtonState == HIGH) {
    sunSelected = !sunSelected;
    earthSelected = false;
    moonSelected = false;
    updateLEDs();
    logButtonPress(sunButtonPin);
  }

  delay(50);

}

// Lógica dos botões:
  // Liga o led do planeta correspondente (vai ter um botão com uma indicação
    // física de qual é o astro de interesse)
  // Manda um serial com uma palavra específica

// Atualiza os leds 
void updateLEDs() {
  digitalWrite(ledEarthPin, earthSelected ? HIGH : LOW);
  digitalWrite(ledMoonPin, moonSelected ? HIGH : LOW);
  digitalWrite(ledSunPin, sunSelected ? HIGH : LOW);
}

void logButtonPress(int buttonPin) {
  int pinToSerial = 0;
  if (lastPressedButton != buttonPin) {
    switch(buttonPin) {
      case sunButtonPin:
        pinToSerial = 1;
      case earthButtonPin:
        pinToSerial = 2;
      case moonButtonPin:
        pinToSerial = 3;
      default:
        Serial.println("An error occurred");
        pinToSerial = -1;
    }
    Serial.println(pinToSerial);
    lastPressedButton = buttonPin;
  }
}

// Função que verifica se a lista de distâncias está no estado inicial
bool arrayHasOnlyZero(int distanceArray[]) {
  for (int i = 0; i < 5; i++) {
    if (distanceArray[i] != 0) {
      return false;
    }
  }
  return true;
}