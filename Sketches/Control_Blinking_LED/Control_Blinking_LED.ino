//Controlling Led By Button
//Turns on and off a LED ,when pressings button attach to pin12
//Email:support@sunfounder.com
//Website:www.sunfounder.com
//2015.5.7
/**********************************/
const int ledPin = 9;//the number of the led pin
/**********************************/
void setup()
{
  pinMode(ledPin,OUTPUT);//initialize the led pin as output
}
/**********************************/
void loop()
{
    digitalWrite(ledPin,HIGH);//turn on the led
    delay(2000);
    digitalWrite(ledPin,LOW);//turn off the led
    delay(2000);

}
/************************************/
