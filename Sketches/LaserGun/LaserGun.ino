#define trigPin 5
#define echoPin 4
#define redLedPin 3
#define buzzerPin 2

#define delayMilliseconds 200
#define triggerCentimeters 50

bool _active = false;
bool _ledFlashOn = false;

void setup()
{
  Serial.begin (9600);
  pinMode(buzzerPin,OUTPUT);//initialize the buzzer pin as an output
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLedPin, OUTPUT);
}

void loop()
{
  long duration, distance;

    // Send an ultrasonic signal
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Get the time it took for the signal to echo back
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into centimeters
  distance = (duration/2) / 29.1;

  // Determine whether the obsticle is too close
  if (distance < triggerCentimeters) 
  {
    LaserOn();
  }
  else 
  {
    LaserOff();
  }

  playSound();
  
  // Logging info
  if (distance >= triggerCentimeters || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  
  //delay(delayMilliseconds);

} 

void LaserOn()
{
    if (_ledFlashOn)
    {
      _ledFlashOn = false;
      digitalWrite(redLedPin,LOW);
    }
    else
    {
      _ledFlashOn = true;
      digitalWrite(redLedPin,HIGH);
    }
    _active = true;
}

void LaserOff()
{
    digitalWrite(redLedPin,LOW);
    _active = false;

}

void playSound()
{
  unsigned char i;
  if(_active)
  {
    //output an frequency
    for(i=0;i<80;i++)
    {
      digitalWrite(buzzerPin,HIGH);
      delay(1);//wait for 1ms
      digitalWrite(buzzerPin,LOW);
      delay(1);//wait for 1ms
    }
    //output another frequency
    for(i=0;i<40;i++)
    {
      digitalWrite(buzzerPin,HIGH);
      delay(2);//wait for 2ms
      digitalWrite(buzzerPin,LOW);
      delay(2);//wait for 2ms
    }
  }
}


