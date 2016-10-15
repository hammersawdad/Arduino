#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

// variable to store the servo position
// 90 degrees is the netural point
int pos = 90;    

int maxHighPos = 115;
int maxLowPos = 15;

int delaytime = 10;

const int buttonRightPin = 2;     // the number of the pushbutton pin
const int buttonLeftPin = 3;     // the number of the pushbutton pin
const int servoPin = 9;     // the number of the pushbutton pin

int buttonRightState;
int buttonLeftState;

void setup() {
    Serial.begin(9600);

// attaches the servo on pin 9 to the servo object
  myservo.attach(servoPin);  
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonRightPin, INPUT);
  pinMode(buttonLeftPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonRightState = digitalRead(buttonRightPin);
  buttonLeftState = digitalRead(buttonLeftPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonRightState == HIGH) {
    // turn LED on:
    turnRight();
  } 

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonLeftState == HIGH) {
    // turn LED on:
    turnLeft();
  } 

  //deactivate();
  
  delay(delaytime);
  
/*  
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //delay(delaytime);                       // waits 15ms for the servo to reach the position
  }
  delay(1000);
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //delay(delaytime);                       // waits 15ms for the servo to reach the position
  }

  delay(1000);
  */
}

void turnRight()
{
  if (pos < maxHighPos)
  {
    pos++;
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.println(pos);
  }
}

void turnLeft()
{
  if (pos > maxLowPos)
  {
    pos--;
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.println(pos);
  }
 
}
void deactivate()
{
  if (pos >= maxHighPos)
  {
    // Dial the position back slightly, so the servo will deactivate
    myservo.write(pos-10);              // tell servo to go to position in variable 'pos'
    Serial.println(pos);
    
  }
}



