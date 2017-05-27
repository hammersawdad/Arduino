#include <Servo.h>

#define PIN_LASERBUZZER 2
#define PIN_LASERLED 3
#define PIN_SONICECHO 4
#define PIN_SONICTRIGGER 5

#define PIN_EYES 7
#define PIN_WHEEL_LEFT 9
#define PIN_WHEEL_RIGHT 10
#define PIN_HEAD 13
#define PIN_SHOULDER 8
#define PIN_WRIST 11
#define PIN_GRIPPER 12

#define HEAD_MIN 0
#define HEAD_MAX 180
#define HEAD_ADJUSTMENT 2
#define SHOULDER_MIN 0
#define SHOULDER_MAX 180
#define SHOULDER_ADJUSTMENT 2
#define WRIST_MIN 0
#define WRIST_MAX 180
#define WRIST_ADJUSTMENT 2
#define GRIPPER_NETURAL 90    
#define GRIPPER_MAX 90
#define GRIPPER_MIN 30
#define GRIPPER_ADJUSTMENT 2
#define GRIPPER_DELAY_TIME 10

#define LASER_TRIGGER_CENTIMETERS 50

/**********************************/
// Servos
/**********************************/
Servo mServoLeft;
Servo mServoRight;
Servo mServoHead;
Servo mServoShoulder;
Servo mServoWrist;
Servo mServoGripper;


const int MAX_INPUT_VALUES = 20;
const char MESSAGE_START = '{';
const char MESSAGE_END = '}';
const char MESSAGE_DELIMITER = ':';

// Continuous Rotation Speeds:  0 = Full Left;   180 = Full Right;  90 = Stop;
int mWristPos = 90;
int mGripperPos = 90;
int mShoulderPos = 90;
int mHeadPos = 90;

// Laser gun settings
bool mSonicActive = false;
bool _ledFlashOn = false;

/**********************************/
void setup()
{
  Serial.begin(9600);       // start serial communication at 9600bps

  // Wheels
  mServoLeft.attach(PIN_WHEEL_LEFT);
  mServoRight.attach(PIN_WHEEL_RIGHT);

  // Head
  pinMode(PIN_EYES,OUTPUT);
  mServoHead.attach(PIN_HEAD);

  // Arm
  mServoShoulder.attach(PIN_SHOULDER);
  mServoWrist.attach(PIN_WRIST);
  mServoGripper.attach(PIN_GRIPPER);

  // Laser gun
  pinMode(PIN_LASERBUZZER,OUTPUT);
  pinMode(PIN_SONICTRIGGER, OUTPUT);
  pinMode(PIN_SONICECHO, INPUT);
  pinMode(PIN_LASERLED, OUTPUT);
}

/**********************************/
void loop()
{

  // Read data from the Serial/Bluetooth input
  if( Serial.available() > 0 )       // if data is available to read
  {
      ReadBluetoothMessage();
  }

  // Check data from the Laser sensor
  ReadUltrasonicLaser();
}

void ReadBluetoothMessage()
{
    // Serial input
    char incomingByte;
    String messageText = "";
    String messageAction;
    String messageValue;
    int loopCounter = 0;

    while(true)
    {
        // Protect against an infinite loop
        loopCounter++;
        if(loopCounter > 100)
        {
          break;
        }

        // Read from the Serial/Bluetooth input
        incomingByte = Serial.read();
    
        // Append the latest character
        messageText += incomingByte;
    
        if (incomingByte == MESSAGE_END)
        {
          // Parse the full message text
          parseMessage(messageText, messageAction, messageValue);
    
          // Pass the message off to the appropriate handler method
          handleMessage(messageAction, messageValue);
          
          // End the loop
          break;
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

    mServoLeft.write(steerValues[0].toInt());
    mServoRight.write(steerValues[1].toInt());
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

void ReadUltrasonicLaser()
{
  long duration, distance;

  // Send an ultrasonic signal
  digitalWrite(PIN_SONICTRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_SONICTRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_SONICTRIGGER, LOW);

  // Get the time it took for the signal to echo back
  duration = pulseIn(PIN_SONICECHO, HIGH);

  // Convert the time into centimeters
  distance = (duration/2) / 29.1;

  Serial.print("Sonic: ");
  Serial.print(distance);
  Serial.print(" cm");

  // Determine whether the obsticle is too close
  if (distance > 0 && distance < LASER_TRIGGER_CENTIMETERS) 
  {
    mSonicActive = true;
    LaserOn();
  }
  else 
  {
    Serial.print(" - Out of range.");
    mSonicActive = false;
    LaserOff();
  }
  Serial.println("");

  playSound();
}

void LaserOn()
{
    if (_ledFlashOn)
    {
      _ledFlashOn = false;
      digitalWrite(PIN_LASERLED,LOW);
    }
    else
    {
      _ledFlashOn = true;
      digitalWrite(PIN_LASERLED,HIGH);
    }
}

void LaserOff()
{
    digitalWrite(PIN_LASERLED,LOW);
}

void playSound()
{
  unsigned char i;
  if(mSonicActive)
  {
    //output an frequency
    for(i=0;i<80;i++)
    {
      digitalWrite(PIN_LASERBUZZER,HIGH);
      delay(1);//wait for 1ms
      digitalWrite(PIN_LASERBUZZER,LOW);
      delay(1);//wait for 1ms
    }
    //output another frequency
    for(i=0;i<40;i++)
    {
      digitalWrite(PIN_LASERBUZZER,HIGH);
      delay(2);//wait for 2ms
      digitalWrite(PIN_LASERBUZZER,LOW);
      delay(2);//wait for 2ms
    }
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


