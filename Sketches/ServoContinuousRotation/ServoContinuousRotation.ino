#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

// variable to store the servo position
// 90 degrees is the netural point
int stopPos = 90;    
int turnRightPos = 200;
int turnLeftPos = 80;
int turnLeftSlowPos = 86;
int turnLeftFastPos = 0;

int currentPos;

int delaytime = 10;

const int buttonRightPin = 2;     // the number of the pushbutton pin
const int buttonLeftPin = 3;     // the number of the pushbutton pin
const int servoPin = 9;     // the number of the pushbutton pin

int buttonRightState;
int buttonLeftState;

void setup()
{
    Serial.begin(9600);

// attaches the servo on pin 9 to the servo object
  myservo.attach(servoPin);  
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonRightPin, INPUT);
  pinMode(buttonLeftPin, INPUT);

  // Set the servo to "stopped"
}

void loop() {
  // read the state of the pushbutton value:
  buttonRightState = digitalRead(buttonRightPin);
  buttonLeftState = digitalRead(buttonLeftPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonRightState == HIGH) {
    //turnRight();
    turnLeftSlow();
  } 

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonLeftState == HIGH) {
    //turnLeft();
    turnLeftFast();
  } 

  // If no button is pushed, then stop the servo
  if (buttonRightState == LOW && buttonLeftState == LOW) {
    stopTurning();
  } 
  
  delay(delaytime);
  
}

void stopTurning()
{
    myservo.write(stopPos);
    Serial.println(stopPos);
}


void turnRight()
{
    myservo.write(turnRightPos);
    Serial.println(turnRightPos);
}

void turnLeft()
{
    myservo.write(turnLeftPos);
    Serial.println(turnLeftPos); 
}

void turnLeftSlow()
{
    myservo.write(turnLeftSlowPos);
    Serial.println(turnLeftSlowPos); 
}
void turnLeftFast()
{
    myservo.write(turnLeftFastPos);
    Serial.println(turnLeftFastPos); 
}

