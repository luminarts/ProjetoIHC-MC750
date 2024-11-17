#include <Servo.h>
#define SPEED_OF_SOUND 0.034 // micrometers/second
#define STOP_SERVO 90 // Neutral position to stop the servo
#define MAX_SPEED 96

Servo myServo;

const int servoPin = 9;
const int trigPin = 4;  // HC-SR04 trigger pin
const int echoPin = 3;  // HC-SR04 echo pin

long duration;
int distance;
const int distanceThreshold = 100; // centimeters

int currentSpeed = STOP_SERVO;
const int speedStep = 1;  // Step size for smooth speed adjustment
const int speedChangeDelay = 200; // Delay between speed changes (adjust for smoothness)

void setup()
{
  Serial.begin(9600); // debugging purposes

	myServo.attach(servoPin);
  myServo.write(STOP_SERVO);  // Neutral position to stop. Check if this is the correct value for the servo used.

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  calculateDistanceSensor();

  if (distance > 0 && distance <= distanceThreshold) { 
    for (int speed = currentSpeed + 1; speed <= MAX_SPEED; speed++) {
      myServo.write(speed);
      currentSpeed = speed;
      delay(speedChangeDelay);
    }
  } else {
    for (int speed = currentSpeed - 1; speed >= STOP_SERVO; speed--) {
      myServo.write(speed);
      currentSpeed = speed;
      delay(speedChangeDelay);
    }
  }

    delay(500);  // Delay for stability
}

void calculateDistanceSensor() {
  if (duration == 0) {
    Serial.println("No echo detected");
    distance = -1;
  } else {
    distance = duration * SPEED_OF_SOUND / 2; // divide by 2 to cutoff the return distance of echo
	  Serial.println(distance);  
  }
}