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

const int buttonLeft = 8;
const int buttonRight = 9;

const int pauseMilis = 3;

int counter = 0;

/**********************************/
void setup()
{
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);

  pinMode(buttonLeft,INPUT);
  pinMode(buttonRight,INPUT);

  Serial.begin(9600);
  Serial.println(HIGH);
  Serial.println(LOW);
}
/**********************************/
void loop()
{
  int buttonLeftValue = digitalRead(buttonLeft);
  int buttonRightValue = digitalRead(buttonRight);

  // If the LEFT button is pressed, then rotate left
  if (buttonLeftValue == HIGH)
  {
    RotateLeft_2();
  }
  else
  {
    // If the RIGHT button is pressed, then rotate right
    if (buttonRightValue == HIGH)
    {
      RotateRight_2();
    }
  }

  // NOTE: Don't respone to both buttons in the same loop 
  
}

// Rotate right - Cycle from pin 4 to 1
void RotateRight()
{
    digitalWrite(pin4,HIGH);
    delay(pauseMilis);
    digitalWrite(pin4,LOW);
    delay(pauseMilis);
    digitalWrite(pin3,HIGH);
    delay(pauseMilis);
    digitalWrite(pin3,LOW);
    delay(pauseMilis);
    digitalWrite(pin2,HIGH);
    delay(pauseMilis);
    digitalWrite(pin2,LOW);
    delay(pauseMilis);
    digitalWrite(pin1,HIGH);
    delay(pauseMilis);
    digitalWrite(pin1,LOW);
    delay(pauseMilis);
}

// Rotate left - Cycle from pin 1 to 4
void RotateLeft()
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

// *********************************************************

// Rotate right - Cycle from pin 4 to 1
void RotateRight_2()
{
    digitalWrite(pin4,HIGH);
    delay(pauseMilis);
    digitalWrite(pin1,LOW);
    delay(pauseMilis);
    digitalWrite(pin3,HIGH);
    delay(pauseMilis);
    digitalWrite(pin4,LOW);
    delay(pauseMilis);    
    digitalWrite(pin2,HIGH);
    delay(pauseMilis);
    digitalWrite(pin3,LOW);
    delay(pauseMilis);
    digitalWrite(pin1,HIGH);
    delay(pauseMilis);
    digitalWrite(pin2,LOW);
    delay(pauseMilis);
    digitalWrite(pin4,HIGH);
    delay(pauseMilis);
    digitalWrite(pin1,LOW);
    delay(pauseMilis);
    digitalWrite(pin3,HIGH);
    delay(pauseMilis);
    digitalWrite(pin4,LOW);
    delay(pauseMilis);    
    digitalWrite(pin2,HIGH);
    delay(pauseMilis);
    digitalWrite(pin3,LOW);
    delay(pauseMilis);
    digitalWrite(pin1,HIGH);
    delay(pauseMilis);
    digitalWrite(pin2,LOW);
    delay(pauseMilis);
}

// Rotate left - Cycle from pin 1 to 4
void RotateLeft_2()
{
    digitalWrite(pin1,HIGH);
    delay(pauseMilis);
    digitalWrite(pin4,LOW);
    delay(pauseMilis);
    digitalWrite(pin2,HIGH);
    delay(pauseMilis);
    digitalWrite(pin1,LOW);
    delay(pauseMilis);    
    digitalWrite(pin3,HIGH);
    delay(pauseMilis);
    digitalWrite(pin2,LOW);
    delay(pauseMilis);
    digitalWrite(pin4,HIGH);
    delay(pauseMilis);
    digitalWrite(pin3,LOW);
    delay(pauseMilis);
    digitalWrite(pin1,HIGH);
    delay(pauseMilis);
    digitalWrite(pin4,LOW);
    delay(pauseMilis);
    digitalWrite(pin2,HIGH);
    delay(pauseMilis);
    digitalWrite(pin1,LOW);
    delay(pauseMilis);    
    digitalWrite(pin3,HIGH);
    delay(pauseMilis);
    digitalWrite(pin2,LOW);
    delay(pauseMilis);
    digitalWrite(pin4,HIGH);
    delay(pauseMilis);
    digitalWrite(pin3,LOW);
    delay(pauseMilis);
}

/************************************/
// Rotate right - Cycle from pin 4 to 1
void RotateRight_3()
{
    digitalWrite(pin4,HIGH);
    delay(pauseMilis);
    digitalWrite(pin2,LOW);
    delay(pauseMilis);
    digitalWrite(pin3,HIGH);
    delay(pauseMilis);
    digitalWrite(pin1,LOW);
    delay(pauseMilis);
    digitalWrite(pin2,HIGH);
    delay(pauseMilis);
    digitalWrite(pin4,LOW);
    delay(pauseMilis);    
    digitalWrite(pin1,HIGH);
    delay(pauseMilis);
    digitalWrite(pin3,LOW);
    delay(pauseMilis);
}

// Rotate left - Cycle from pin 1 to 4
void RotateLeft_3()
{
    digitalWrite(pin1,HIGH);
    delay(pauseMilis);
    digitalWrite(pin3,LOW);
    delay(pauseMilis);
    digitalWrite(pin2,HIGH);
    delay(pauseMilis);
    digitalWrite(pin4,LOW);
    delay(pauseMilis);    
    digitalWrite(pin3,HIGH);
    delay(pauseMilis);
    digitalWrite(pin1,LOW);
    delay(pauseMilis);
    digitalWrite(pin4,HIGH);
    delay(pauseMilis);
    digitalWrite(pin2,LOW);
    delay(pauseMilis);

}

/************************************/

