#include <Servo.h>

#define PIN_EYES 2
#define PIN_HEAD 13
#define PIN_SHOULDER 10
#define PIN_WRIST 11
#define PIN_GRIPPER 12

#define PIN_WHEEL_LEFT_EN 5
#define PIN_WHEEL_LEFT_I1 4
#define PIN_WHEEL_LEFT_I2 3

#define PIN_WHEEL_RIGHT_EN 6
#define PIN_WHEEL_RIGHT_I1 7
#define PIN_WHEEL_RIGHT_I2 8

#define HEAD_MIN 0
#define HEAD_MAX 180
#define HEAD_ADJUSTMENT 2
#define SHOULDER_MIN 0
#define SHOULDER_MAX 180
#define SHOULDER_ADJUSTMENT 2
#define WRIST_MIN 0
#define WRIST_MAX 180
#define WRIST_ADJUSTMENT 2
#define GRIPPER_MAX 90
#define GRIPPER_MIN 30
#define GRIPPER_ADJUSTMENT 2
#define GRIPPER_DELAY_TIME 10

/**********************************/
// Servos
/**********************************/
Servo mServoLeft;
Servo mServoRight;
Servo mServoHead;
Servo mServoShoulder;
Servo mServoWrist;
Servo mServoGripper;

// Bluetooth messages
String mIncomingMessageText;
const int MAX_INPUT_VALUES = 20;
const char MESSAGE_START = '{';
const char MESSAGE_END = '}';
const char MESSAGE_DELIMITER = ':';

// Continuous Rotation Speeds:  0 = Full Left;   180 = Full Right;  90 = Stop;
int mWristPos = 90;
int mGripperPos = 60;
int mShoulderPos = 90;
int mHeadPos = 90;

// Laser gun settings
bool mSonicActive = false;
bool mLaserFlashOn = false;

// Servo switches
bool mServoMessageHead = false;
bool mServoMessageShoulder = false;
bool mServoMessageWrist = false;
bool mServoMessageGripper = false;

/**********************************/
void setup()
{
  // start serial communication at 9600bps
  Serial.begin(9600);       

  // Wheels
  pinMode(PIN_WHEEL_LEFT_EN, OUTPUT);
  pinMode(PIN_WHEEL_LEFT_I1, OUTPUT);
  pinMode(PIN_WHEEL_LEFT_I2, OUTPUT);
  pinMode(PIN_WHEEL_RIGHT_EN, OUTPUT);
  pinMode(PIN_WHEEL_RIGHT_I1, OUTPUT);
  pinMode(PIN_WHEEL_RIGHT_I2, OUTPUT);

  // Head
  pinMode(PIN_EYES,OUTPUT);
  mServoHead.attach(PIN_HEAD);

  // Arm
  mServoShoulder.attach(PIN_SHOULDER);
  mServoWrist.attach(PIN_WRIST);
  mServoGripper.attach(PIN_GRIPPER);
}

/**********************************/

void loop()
{
  // Read data from the Serial/Bluetooth input
  if( Serial.available() > 0 )
  {
    ReadBluetoothMessage();
  }
  else
  {
    // TODO: Add a timer to reset servos.  
    // If no message has been sent for a servo, then reset it.
    // Only check for this every few seconds
    //SetServoDefaults();
  }
}

void SetServoDefaults()
{
    // Center all servos that haven't had a message sent to them, yet

    if (mServoMessageHead == false)
    {
        mServoHead.write(mHeadPos);              
    }
    if (mServoMessageShoulder == false)
    {
        mServoShoulder.write(mShoulderPos);                    
    }
    if (mServoMessageWrist == false)
    {
        mServoWrist.write(mWristPos);
    }
    if (mServoMessageGripper == false)
    {
        mServoGripper.write(mGripperPos);              
    }
}

void ReadBluetoothMessage()
{
    char incomingByte;
    String messageAction;
    String messageValue;

    // read it and store it in the char variable
    incomingByte = Serial.read();         

    // Append the latest character
    mIncomingMessageText += incomingByte;

    if (incomingByte == MESSAGE_END)
    {
      // Parse the full message text
      parseMessage(mIncomingMessageText, messageAction, messageValue);

      // Pass the message off to the appropriate handler method
      handleMessage(messageAction, messageValue);

      // Clear the message text variable
      mIncomingMessageText = "";
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
   * The first number is the speed for Motor A
   * The second number is the speed for Motor B
   */
    char delimiter = ' ';
    String steerValues[MAX_INPUT_VALUES];

    parseString(message, delimiter, steerValues);

    int leftValue = steerValues[0].toInt();
    int rightValue = steerValues[1].toInt();

    // Set the LEFT wheel
    if (leftValue >= 0)
    {
      analogWrite(PIN_WHEEL_LEFT_EN, leftValue);
      digitalWrite(PIN_WHEEL_LEFT_I1, HIGH);
      digitalWrite(PIN_WHEEL_LEFT_I2, LOW);
    }
    else
    {
      analogWrite(PIN_WHEEL_LEFT_EN, leftValue * -1);
      digitalWrite(PIN_WHEEL_LEFT_I1, LOW);
      digitalWrite(PIN_WHEEL_LEFT_I2, HIGH);
    }

    // Set the RIGHT wheel
    if (rightValue >= 0)
    {
      analogWrite(PIN_WHEEL_RIGHT_EN, rightValue);
      digitalWrite(PIN_WHEEL_RIGHT_I1, HIGH);
      digitalWrite(PIN_WHEEL_RIGHT_I2, LOW);
    }
    else
    {
      analogWrite(PIN_WHEEL_RIGHT_EN, rightValue * -1);
      digitalWrite(PIN_WHEEL_RIGHT_I1, LOW);
      digitalWrite(PIN_WHEEL_RIGHT_I2, HIGH);
    }
}

void handleLedMessage(String message)
{
    if( message == "OFF" )
    {
        digitalWrite(PIN_EYES, LOW);    // turn the LED off
        delay(100);                  // waits for a second   
    }
  
    if( message == "ON" )
     {
        digitalWrite(PIN_EYES, HIGH);  // turn the LED on
        delay(100);                  // waits for a second
     }
}

void handleHeadMessage(String message)
{
    mServoMessageHead = true;

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
    mServoMessageShoulder = true;
    
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
    mServoMessageWrist = true;

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
    mServoMessageGripper = true;

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


