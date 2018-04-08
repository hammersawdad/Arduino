#include <Servo.h>

Servo servo1; 
int servoPos = 0;

void setup() {
  servo1.attach(9);
  
  Serial.begin(9600);
  Serial.println("Ready");

}

void loop() {

  int v = 0;

  if ( Serial.available()) {
    char ch = Serial.read();
    Serial.println(ch);

    switch(ch) {
      case '0'...'9':
        v = 10 * ch;
        Serial.println(v);
        servo1.write(v);
        break;
      case 's':
        servo1.write(v);
        v = 0;
        break;
    }
  }
  else
  {
    switch(servoPos) {
      case 0:
        servoPos = 90;
        break;
      case 90:
        servoPos = 180;
        break;
      case 180:
        servoPos = 0;
        break;
    }
    servo1.write(servoPos);
    
    //Serial.println("Not Available");
  }

  delay(1000);

} 
