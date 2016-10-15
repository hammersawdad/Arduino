int ledNum = 8;
int ledPin[] = {2, 3, 4, 5, 6, 7, 8, 9};    // Create array for LED pins
int potPin = A0;    // select the input pin for the potentiometer

void setup() 
{
  // set all pins to output
  for (int x = 0; x < ledNum; x++)
  { 
     pinMode(ledPin[x], OUTPUT); 
  }
}

void loop() 
{
  int volume = analogRead(potPin); // read the value from the pot 

  setLED(volume, 0, 0);
  setLED(volume, 1, 100);
  setLED(volume, 2, 200);
  setLED(volume, 3, 300);
  setLED(volume, 4, 400);
  setLED(volume, 5, 500);
  setLED(volume, 6, 600);
  setLED(volume, 7, 700);

  delay(100);
}

void setLED(int volume, int index, int threshhold)
{
  if (volume > threshhold)
  {
    digitalWrite(ledPin[index], HIGH);
  }
  else
  {
    digitalWrite(ledPin[index], LOW);  
  }
}



