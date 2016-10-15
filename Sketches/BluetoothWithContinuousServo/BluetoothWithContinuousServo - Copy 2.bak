#include <Servo.h>
/**********************************/
Servo mServoA;  // create servo object to control a servo
Servo mServoB;  // create servo object to control a servo

String mIncomingMessageText = "";


const int PIN_LED = 13;//the number of the led pin
const int PIN_SERVO_A = 9;     // the number of the pushbutton pin
const int PIN_SERVO_B = 10;     // the number of the pushbutton pin


// Speeds:  0 = Full Left;   180 = Full Right;  90 = Stop;


int mServoAForwardFast;
int mServoAForwardSlow;
int mServoAStop;
int mServoABackwardSlow;
int mServoABackwardFast;
  
int mServoBForwardFast;
int mServoBForwardSlow;
int mServoBStop;
int mServoBBackwardSlow;
int mServoBBackwardFast;

const int CLOCKWISE_FAST = 30;
const int CLOCKWISE_SLOW = 70;
const int STOP = 90;    
const int COUNTER_SLOW = 110;
const int COUNTER_FAST = 150;  


const char MESSAGE_START = '*';
const char MESSAGE_END = '#';
const char MESSAGE_DELIMITER = '|';
/**********************************/
void setup()
{
  Serial.begin(9600);       // start serial communication at 115200bps
  pinMode(PIN_LED,OUTPUT);     //initialize the led pin as output

  initializeServos();
}

void initializeServos()
{
  mServoA.attach(PIN_SERVO_A);  // attaches the servo on pin 9 to the servo object
  mServoB.attach(PIN_SERVO_B);  // attaches the servo on pin 9 to the servo object

  // Servo A speed settings
  int servoAOffset = 0;
  mServoAForwardFast = CLOCKWISE_FAST + servoAOffset;
  mServoAForwardSlow = CLOCKWISE_SLOW + servoAOffset;
  mServoAStop = STOP + servoAOffset;
  mServoABackwardSlow = COUNTER_SLOW + servoAOffset;
  mServoABackwardFast = COUNTER_FAST + servoAOffset;

  // Servo B speed settings
  int servoBOffset = 2;
  mServoBForwardFast = COUNTER_FAST + servoBOffset;
  mServoBForwardSlow = COUNTER_SLOW + servoBOffset;
  mServoBStop = STOP + servoBOffset;
  mServoBBackwardSlow = CLOCKWISE_SLOW + servoBOffset;
  mServoBBackwardFast = CLOCKWISE_FAST + servoBOffset;
}

/**********************************/
void loop()
{
  char incomingByte;
  String messageAction;
  String messageValue;

  
  if( Serial.available() > 0 )       // if data is available to read
  {
    incomingByte = Serial.read();         // read it and store it in the char variable
    Serial.println(incomingByte);

    // Append the latest character
    mIncomingMessageText += incomingByte;

      Serial.println("Incoming Text:" + mIncomingMessageText);

    if (incomingByte == MESSAGE_END)
    {
      Serial.println("Full Incoming Text:" + mIncomingMessageText);

      
      // Parse the full message text
      parseMessage(mIncomingMessageText, messageAction, messageValue);

      handleMessage(messageAction, messageValue);

      // Clear the message text variable
      mIncomingMessageText = "";
    }
 
  }
}
/************************************/

void parseMessage(String fullMessage, String &messageAction, String &messageValue)
{
  // TODO: this needs much better validation
  Serial.println("FULL:" + fullMessage);

  String parsedMessage = fullMessage;
   
  // Remove the first character
  parsedMessage.remove(0,1);
  // Remove the last character
  parsedMessage.remove(parsedMessage.length() - 1);
  // Split the message by the delimiter
  int delimiterPos = parsedMessage.indexOf(MESSAGE_DELIMITER);
  
  messageAction = parsedMessage.substring(0,delimiterPos);
  messageValue = parsedMessage.substring(delimiterPos + 1);

  Serial.println("A:" + messageAction);
  Serial.println("V:" + messageValue);
}

void handleMessage(String messageAction, String messageValue)
{
      // Hand off the Message Value to the appropriate handler
       if (messageAction == "0")
       {
          handleAdjustSpeedMessage(messageValue);
       }
       if (messageAction == "1")
       {
          handleMoveMessage(messageValue);
       }
       if (messageAction == "2")
       {
          handleLedMessage(messageValue);
       }
}
void handleMoveMessage(String message)
{
  /*
   * The message has two parts: Direction and Speed
   * The two parts are deliminated with a space character
   * Direction options:
   * S = Stop
   * F = Forward (straight)
   * B = Backward (straight)
   * R = Right
   * L = Left
   * 
   * Speed options:
   * S = slow
   * F = fast
   * 
   *  TODO: Implement Fast/Slow
   * 
   */
    int delimiterPos = message.indexOf(' ');
  
    String directionValue = message.substring(0,delimiterPos);
    String speedValue = message.substring(delimiterPos + 1);

//    int xPos = xPosString.toInt();
//    int yPos = yPosString.toInt();

    if (directionValue == "S") {moveStop();}
    if (directionValue == "F") {moveForward();}
    if (directionValue == "B") {moveBackward();}
    if (directionValue == "R") {moveRight();}
    if (directionValue == "L") {moveLeft();}

}

void handleAdjustSpeedMessage(String message)
{
  /*
   * There are two values being sent
   * 1. Servo indentifier : A,B
   * 2. Increase or Decrease:  +,-
   */
    int delimiterPos = message.indexOf(' ');
  
    String servoIdentifier = message.substring(0,delimiterPos);
    String increaseIdentifier = message.substring(delimiterPos + 1);

    // Determine the increment value
    int increment = 1;
    if (increaseIdentifier == "-")
    {
      increment = -1;
    }

    // Adjust the values for the specified servo
    if (servoIdentifier == "A")
    {
      mServoAForwardFast += increment;
      mServoAForwardSlow += increment;
      mServoAStop += increment;
      mServoABackwardSlow += increment;
      mServoABackwardFast += increment;
    }
    if (servoIdentifier == "B")
    {
      mServoBForwardFast += increment;
      mServoBForwardSlow += increment;
      mServoBStop += increment;
      mServoBBackwardSlow += increment;
      mServoBBackwardFast += increment;
    }

}

void handleLedMessage(String message)
{
    if( message == "OFF" )
    {
        digitalWrite(PIN_LED, LOW);    // turn the LED off
        delay(100);                  // waits for a second   
    }
  
    if( message == "ON" )
     {
        digitalWrite(PIN_LED, HIGH);  // turn the LED on
        delay(100);                  // waits for a second
     }
}

void moveStop()
{
    mServoA.write(mServoAStop);
    mServoB.write(mServoBStop);
}
void moveLeft()
{
    mServoA.write(mServoAForwardSlow);
    mServoB.write(mServoBForwardFast);
}
void moveRight()
{
    mServoA.write(mServoAForwardFast);
    mServoB.write(mServoBForwardSlow);
}
void moveForward()
{
    mServoA.write(mServoAForwardFast);
    mServoB.write(mServoBForwardFast);
}
void moveBackward()
{
    mServoA.write(mServoABackwardFast);
    mServoB.write(mServoBBackwardFast);
}



