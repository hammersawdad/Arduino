int motor[] = {2, 3};
int buttonPin = 7;

void setup() 
{
  pinMode(motor[0], OUTPUT);
  pinMode(motor[1], OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() 
{ 
  int buttonValue;
  buttonValue = digitalRead(buttonPin);

  if (buttonValue == HIGH)
  {
    drive_forward();    
  }
  else
  {
    motor_stop();    
  }
  
  delay(50);
}

// --------------------------------------------------------------------------- Drive

void motor_stop()
{
  digitalWrite(motor[0], LOW); 
  digitalWrite(motor[1], LOW); 
  delay(25);
}

void drive_forward()
{
  digitalWrite(motor[0], HIGH); 
  digitalWrite(motor[1], LOW); 
}

void drive_backward()
{
  digitalWrite(motor[0], LOW); 
  digitalWrite(motor[1], HIGH); 
}

