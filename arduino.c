// C++ code
//
#include <Servo.h>

Servo myservo;

int servoPin = 9;
int buttonPin = 8;

int lastButtonState = LOW;
int buttonState = LOW;

void setup()
{
	myservo.attach(servoPin);
  	pinMode(buttonPin, INPUT);
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  
  if (buttonState != lastButtonState) {
  	
    if (lastButtonState == LOW) {
    
      myservo.write(135); // medium speed
      // might need to edit this if we want to include the potentionmeter
      
    } else if (lastButtonState == HIGH) {
    
      myservo.write(90);
    }
    
  }

}