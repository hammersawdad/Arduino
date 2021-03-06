#include <Servo.h>
/**********************************/
Servo mServoA;  // create servo object to control a servo
Servo mServoB;  // create servo object to control a servo
Servo mServoHead;
Servo mServoShoulder;
Servo mServoWrist;
Servo mServoGripper;

String mIncomingMessageText = "";

const int PIN_LED = 7;          //the number of the led pin
const int PIN_SERVO_A = 9;      // the number of the pushbutton pin
const int PIN_SERVO_B = 10;     // the number of the pushbutton pin
const int PIN_HEAD = 13;
const int PIN_SHOULDER = 8;
const int PIN_WRIST = 11;
const int PIN_GRIPPER = 12;

const int HEAD_MIN = 0;
const int HEAD_MAX = 180;
const int HEAD_ADJUSTMENT = 2;
const int SHOULDER_MIN = 0;
const int SHOULDER_MAX = 180;
const int SHOULDER_ADJUSTMENT = 2;
const int WRIST_MIN = 0;
const int WRIST_MAX = 180;
const int WRIST_ADJUSTMENT = 2;
const int GRIPPER_NETURAL = 90;    
const int GRIPPER_MAX = 90;
const int GRIPPER_MIN = 30;
const int GRIPPER_ADJUSTMENT = 2;
const int GRIPPER_DELAY_TIME = 10;

const int MAX_INPUT_VALUES = 20;
const char MESSAGE_START = '{';
const char MESSAGE_END = '}';
const char MESSAGE_DELIMITER = ':';

// Continuous Rotation Speeds:  0 = Full Left;   180 = Full Right;  90 = Stop;


int mWristPos = 90;
int mGripperPos = 90;
int mShoulderPos = 90;
int mHeadPos = 90;

/**********************************/
void setup()
{
  Serial.begin(9600);       // start serial communication at 9600bps
  pinMode(PIN_LED,OUTPUT);     //initialize the led pin as output

  mServoA.attach(PIN_SERVO_A);
  mServoB.attach(PIN_SERVO_B);
  mServoHead.attach(PIN_HEAD);
  mServoShoulder.attach(PIN_SHOULDER);
  mServoWrist.attach(PIN_WRIST);
  mServoGripper.attach(PIN_GRIPPER);
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
    //Serial.println(incomingByte);

    // Append the latest character
    mIncomingMessageText += incomingByte;

    //Serial.println("Incoming Text:" + mIncomingMessageText);

    if (incomingByte == MESSAGE_END)
    {
      //Serial.println("Full Incoming Text:" + mIncomingMessageText);

      // Parse the full message text
      parseMessage(mIncomingMessageText, messageAction, messageValue);

      // Pass the message off to the appropriate handler method
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
       if (messageAction == "1")
       {
          handleSteerMessage(messageValue);
       }
       if (messageAction == "2")
       {
          handleLedMessage(messageValue);
       }
       if (messageAction == "3")
       {
          handleShoulderMessage(messageValue);
       }
       if (messageAction == "4")
       {
          handleWristMessage(messageValue);
       }
       if (messageAction == "5")
       {
          handleGripperMessage(messageValue);
       }
       if (messageAction == "6")
       {
          handleHeadMessage(messageValue);
       }
}

void handleSteerMessage(String message)
{
  /*
   * There should be two numbers, separated by a space
   * The first number is the speed for Servo A
   * The second number is the speed for Servo B
   */
    char delimiter = ' ';
    String steerValues[MAX_INPUT_VALUES];

    parseString(message, delimiter, steerValues);

    mServoA.write(steerValues[0].toInt());
    mServoB.write(steerValues[1].toInt());
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

void handleHeadMessage(String message)
{
    if( message == "OPEN" )
    {
        headRight();   
    }
    if( message == "CLOSE" )
     {
        headLeft();   
     }
}

void headLeft()
{
  if (mHeadPos <= HEAD_MAX)
  {
    mHeadPos+=HEAD_ADJUSTMENT;
    mServoHead.write(mHeadPos);              
    Serial.println(mHeadPos);
  }
}

void headRight()
{
  if (mHeadPos >= HEAD_MIN)
  {
    mHeadPos-=HEAD_ADJUSTMENT;
    mServoHead.write(mHeadPos);
    Serial.println(mHeadPos);
  }
}

void handleShoulderMessage(String message)
{
    if( message == "OPEN" )
    {
        shoulderRight();   
    }
    if( message == "CLOSE" )
     {
        shoulderLeft();   
     }
}

void shoulderLeft()
{
  if (mShoulderPos <= SHOULDER_MAX)
  {
    mShoulderPos+=SHOULDER_ADJUSTMENT;
    mServoShoulder.write(mShoulderPos);              
    Serial.println(mShoulderPos);
  }
}

void shoulderRight()
{
  if (mShoulderPos >= SHOULDER_MIN)
  {
    mShoulderPos-=SHOULDER_ADJUSTMENT;
    mServoShoulder.write(mShoulderPos);
    Serial.println(mShoulderPos);
  }
}

void handleWristMessage(String message)
{
    if( message == "OPEN" )
    {
        wristRight();
    }
    if( message == "CLOSE" )
    {
        wristLeft();
    }
}

void wristLeft()
{
  if (mWristPos <= WRIST_MAX)
  {
    mWristPos+=WRIST_ADJUSTMENT;
    mServoWrist.write(mWristPos);              
    Serial.println(mWristPos);
  }
}

void wristRight()
{
  if (mWristPos >= WRIST_MIN)
  {
    mWristPos-=WRIST_ADJUSTMENT;
    mServoWrist.write(mWristPos);
    Serial.println(mWristPos);
  }
}

void handleGripperMessage(String message)
{
    if( message == "OPEN" )
    {
        gripperOpen();
    }
    if( message == "CLOSE" )
     {
        gripperClose();
     }
}

void gripperOpen()
{
  if (mGripperPos <= GRIPPER_MAX)
  {
    mGripperPos+=GRIPPER_ADJUSTMENT;
    mServoGripper.write(mGripperPos);              
    Serial.println(mGripperPos);
  }
}

void gripperClose()
{
  if (mGripperPos >= GRIPPER_MIN)
  {
    mGripperPos-=GRIPPER_ADJUSTMENT;
    mServoGripper.write(mGripperPos);
    Serial.println(mGripperPos);
  }
}
/************************************/
void parseString(String input, char delimiter, String *outputArray)
{
    int delimiterPos;
    String patialText;

    for (int i=0; i < MAX_INPUT_VALUES; i++)
    {
        if (input.length() > 0)
        {
          delimiterPos = input.indexOf(' ');
          outputArray[i] = input.substring(0,delimiterPos);
          input = input.substring(delimiterPos + 1);

          if(delimiterPos < 0)
          {
            input = "";
          }
        }
        else
        {
          outputArray[i] = "";
        }
    } 
}


