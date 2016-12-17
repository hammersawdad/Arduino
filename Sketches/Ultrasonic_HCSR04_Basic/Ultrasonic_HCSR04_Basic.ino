#define trigPin 13
#define echoPin 12
#define redLedPin 11
#define greenLedPin 10

#define delayMilliseconds 200
#define triggerCentimeters 50

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}

void loop() {
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
  if (distance < triggerCentimeters) {
    digitalWrite(redLedPin,HIGH);
    digitalWrite(greenLedPin,LOW);
  }
  else {
    digitalWrite(redLedPin,LOW);
    digitalWrite(greenLedPin,HIGH);
  }

  // Logging info
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  
  delay(delayMilliseconds);
}
