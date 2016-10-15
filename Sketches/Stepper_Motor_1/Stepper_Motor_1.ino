//Controlling Led By Button
//Turns on and off a LED ,when pressings button attach to pin12
//Email:support@sunfounder.com
//Website:www.sunfounder.com
//2015.5.7
/**********************************/
const int pin1 = 2;
const int pin2 = 3;
const int pin3 = 4;
const int pin4 = 5;

const int pauseMilis = 2;

int counter = 0;
/**********************************/
void setup()
{
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
}
/**********************************/
void loop()
{
  counter = counter + 1;

  if (counter < 2000)
  {
    digitalWrite(pin1,HIGH);
    delay(pauseMilis);
    digitalWrite(pin1,LOW);
    delay(pauseMilis);
    digitalWrite(pin2,HIGH);
    delay(pauseMilis);
    digitalWrite(pin2,LOW);
    delay(pauseMilis);
    digitalWrite(pin3,HIGH);
    delay(pauseMilis);
    digitalWrite(pin3,LOW);
    delay(pauseMilis);
    digitalWrite(pin4,HIGH);
    delay(pauseMilis);
    digitalWrite(pin4,LOW);
    delay(pauseMilis);
  }

  if (counter > 5000)
  {
    counter = 1;
  }
  
}
/************************************/
