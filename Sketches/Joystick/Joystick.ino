//Controlling Led By Button
//Turns on and off a LED ,when pressings button attach to pin12
//Email:support@sunfounder.com
//Website:www.sunfounder.com
//2015.5.7
/**********************************/
/**********************************/

const int pinLR = A0;
const int pinUD = A1;

const int pin0 = 2;
const int pin1 = 3;
const int pin2 = 4;
const int pin3 = 5;
const int pin4 = 6;
const int pin5 = 7;


void setup()
{
  Serial.begin(9600);  
  pinMode(pinLR, INPUT);
  pinMode(pinUD, INPUT);

  pinMode(pin0, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
}
/**********************************/
void loop()
{
  int valueLR = analogRead(pinLR);
  int valueUD = analogRead(pinUD);



  Serial.print(valueLR);
  Serial.print("  ");
  Serial.print(valueUD);
  Serial.print("  ");
  Serial.println(" ");

  // UP threshhold
  if (valueUD > 800)
  {
    digitalWrite(pin1,HIGH);
    digitalWrite(pin2,HIGH);
  }
  else
  {
    digitalWrite(pin1,LOW);
    digitalWrite(pin2,LOW);
  }

  // DOWN threshhold
  if (valueUD < 200)
  {
    digitalWrite(pin4,HIGH);
    digitalWrite(pin5,HIGH);
  }
  else
  {
    digitalWrite(pin4,LOW);
    digitalWrite(pin5,LOW);
  }

  // LEFT threshhold
  if (valueLR > 800)
  {
    digitalWrite(pin3,HIGH);
  }
  else
  {
    digitalWrite(pin3,LOW);
  }

  // RIGHT threshhold
  if (valueLR < 200)
  {
    digitalWrite(pin0,HIGH);
  }
  else
  {
    digitalWrite(pin0,LOW);
  }

  
}
/************************************/
