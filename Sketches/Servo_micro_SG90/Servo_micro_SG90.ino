#include <Servo.h>

Servo servo1; Servo servo2; 


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
    Serial.println("Not Available");
  }

  delay(1000);

} 
