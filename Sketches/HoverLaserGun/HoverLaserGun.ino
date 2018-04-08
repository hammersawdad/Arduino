#include <Servo.h>

#define PIN_LASERBUZZER 2
#define PIN_LASERLED 3
#define PIN_SONICECHO 4
#define PIN_SONICTRIGGER 5
#define LASER_TRIGGER_CENTIMETERS 50

// Laser gun settings
bool mSonicActive = false;
bool mLaserFlashOn = false;

/**********************************/
void setup()
{
  Serial.begin(9600);       // start serial communication at 9600bps

  // Laser gun
  pinMode(PIN_LASERBUZZER,OUTPUT);
  pinMode(PIN_SONICTRIGGER, OUTPUT);
  pinMode(PIN_SONICECHO, INPUT);
  pinMode(PIN_LASERLED, OUTPUT);
}

/**********************************/

void loop()
{
   // Check data from the Laser sensor
   ReadUltrasonicLaser();    
}

void ReadUltrasonicLaser()
{
  long duration, distance;

  // Send an ultrasonic signal
  digitalWrite(PIN_SONICTRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_SONICTRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_SONICTRIGGER, LOW);

  // Get the time it took for the signal to echo back
  duration = pulseIn(PIN_SONICECHO, HIGH);

  // Convert the time into centimeters
  distance = (duration/2) / 29.1;

  Serial.print("Sonic: ");
  Serial.print(distance);
  Serial.print(" cm");

  // Determine whether the obsticle is too close
  if (distance > 0 && distance < LASER_TRIGGER_CENTIMETERS) 
  {
    mSonicActive = true;
    LaserOn();
  }
  else 
  {
    Serial.print(" - Out of range.");
    mSonicActive = false;
    LaserOff();
  }
  Serial.println("");

  playSound();
}

void LaserOn()
{
    if (mLaserFlashOn)
    {
      mLaserFlashOn = false;
      digitalWrite(PIN_LASERLED,LOW);
    }
    else
    {
      mLaserFlashOn = true;
      digitalWrite(PIN_LASERLED,HIGH);
    }
}

void LaserOff()
{
    digitalWrite(PIN_LASERLED,LOW);
}

void playSound()
{
  unsigned char i;
  if(mSonicActive)
  {
    //output an frequency
    for(i=0;i<80;i++)
    {
      digitalWrite(PIN_LASERBUZZER,HIGH);
      delay(1);//wait for 1ms
      digitalWrite(PIN_LASERBUZZER,LOW);
      delay(1);//wait for 1ms
    }
    //output another frequency
    for(i=0;i<40;i++)
    {
      digitalWrite(PIN_LASERBUZZER,HIGH);
      delay(2);//wait for 2ms
      digitalWrite(PIN_LASERBUZZER,LOW);
      delay(2);//wait for 2ms
    }
  }
}


