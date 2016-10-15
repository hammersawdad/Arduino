#include <Servo.h>
/**********************************/
Servo mServoA;  // create servo object to control a servo
Servo mServoB;  // create servo object to control a servo

String mIncomingMessageText = "";
bool mInitialized = false;

const int PIN_LED = 13;//the number of the led pin
const int PIN_SERVO_A = 9;     // the number of the pushbutton pin
const int PIN_SERVO_B = 10;     // the number of the pushbutton pin

const int MAX_INPUT_VALUES = 20;
const char MESSAGE_START = '*';
const char MESSAGE_END = '#';
const char MESSAGE_DELIMITER = '|';

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
       if (messageAction == "0")
       {
          handleInitializeMessage(messageValue);
       }

       if (mInitialized)
       {
         if (messageAction == "1")
         {
            handleMoveMessage(messageValue);
         }
         if (messageAction == "2")
         {
            handleLedMessage(messageValue);
         }
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

void handleInitializeMessage(String message)
{
  /*
   * There should be 12 values
   * 'A' followed by the five speed values for the first servo
   * 'B' followed by the five speed values for the second servo
   */
    char delimiter = ' ';
    String initializationValues[MAX_INPUT_VALUES];

    parseString(message, delimiter, initializationValues);

    mServoAForwardFast = initializationValues[1].toInt();
    mServoAForwardSlow = initializationValues[2].toInt();
    mServoAStop = initializationValues[3].toInt();
    mServoABackwardSlow = initializationValues[4].toInt();
    mServoABackwardFast = initializationValues[5].toInt();

    mServoBForwardFast = initializationValues[7].toInt();
    mServoBForwardSlow = initializationValues[8].toInt();
    mServoBStop = initializationValues[9].toInt();
    mServoBBackwardSlow = initializationValues[10].toInt();
    mServoBBackwardFast = initializationValues[11].toInt();

    handleLedMessage("ON");
    mInitialized = true;


    Serial.print("A ");
    Serial.print(mServoAForwardFast);
    Serial.print(" ");
    Serial.print(mServoAForwardSlow);
    Serial.print(" ");
    Serial.print(mServoAStop);
    Serial.print(" ");
    Serial.print(mServoABackwardSlow);
    Serial.print(" ");
    Serial.print(mServoABackwardFast);
    Serial.println(" ");

    Serial.print("B ");
    Serial.print(mServoBForwardFast);
    Serial.print(" ");
    Serial.print(mServoBForwardSlow);
    Serial.print(" ");
    Serial.print(mServoBStop);
    Serial.print(" ");
    Serial.print(mServoBBackwardSlow);
    Serial.print(" ");
    Serial.print(mServoBBackwardFast);
    Serial.println(" ");

    Serial.println("-------------------------------");
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


