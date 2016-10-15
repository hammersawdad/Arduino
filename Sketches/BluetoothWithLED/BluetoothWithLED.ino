//Controlling Led By Button
//Turns on and off a LED ,when pressings button attach to pin12
//Email:support@sunfounder.com
//Website:www.sunfounder.com
//2015.5.7
/**********************************/
char incomingByte;         // variable to receive data from the serial port
const int ledPin = 13;//the number of the led pin
/**********************************/
void setup()
{
  pinMode(ledPin,OUTPUT);     //initialize the led pin as output
  Serial.begin(9600);       // start serial communication at 115200bps
}
/**********************************/
void loop()
{
  if( Serial.available() > 0 )       // if data is available to read
  {
    incomingByte = Serial.read();         // read it and store it in the char variable
    Serial.println(incomingByte);
 
    if( incomingByte == '0' )               // if '0' was received led 13 is switched off
    {
        digitalWrite(ledPin, LOW);    // turn the LED off
        delay(100);                  // waits for a second   
        //Serial.println("13 off");
    }
  
    if( incomingByte == '1' )               // if '1' was received led 13 on
     {
        digitalWrite(ledPin, HIGH);  // turn the LED on
        delay(100);                  // waits for a second
        //Serial.println("13 on");
     }
  }
}
/************************************/



