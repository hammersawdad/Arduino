#include <Servo.h>
/**********************************/
Servo mServoA;  // create servo object to control a servo
Servo mServoB;  // create servo object to control a servo

String mIncomingMessageText = "";

const int PIN_LED = 13;//the number of the led pin
const int PIN_SERVO_A = 9;     // the number of the pushbutton pin
const int PIN_SERVO_B = 10;     // the number of the pushbutton pin

const int MAX_INPUT_VALUES = 20;
const char MESSAGE_START = '*';
const char MESSAGE_END = '#';
const char MESSAGE_DELIMITER = '|';

// Speeds:  0 = Full Left;   180 = Full Right;  90 = Stop;



/**********************************/
void setup()
{
  Serial.begin(9600);       // start serial communication at 115200bps
  pinMode(PIN_LED,OUTPUT);     //initialize the led pin as output

  mServoA.attach(PIN_SERVO_A);  // attaches the servo on pin 9 to the servo object
  mServoB.attach(PIN_SERVO_B);  // attaches the servo on pin 9 to the servo object
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
  //Serial.println("FULL:" + fullMessage);

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


