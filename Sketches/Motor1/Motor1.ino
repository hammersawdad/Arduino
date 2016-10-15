int motor[] = {2, 3};

void setup() 
{
  pinMode(motor[0], OUTPUT);
  pinMode(motor[1], OUTPUT);
}

void loop() 
{ 
  drive_forward();
  delay(2000);
  motor_stop();
  delay(2000);
  
  drive_backward();
  delay(2000);
  motor_stop();
  delay(2000);
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

