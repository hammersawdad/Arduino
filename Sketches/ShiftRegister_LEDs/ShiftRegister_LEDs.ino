//set 595 state

int clockPin = 7;
int latchPin = 6;
int dataPin = 5;

byte numberToDisplay = 74;


void setup() {
  //all connections to 595 are outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
    //countUp();
    displayValue();
}

void displayValue() {
    //first set latch pin low so we can shift in data without disrupting the outputs
    digitalWrite(latchPin, LOW);
    // shift out bits of data
    shiftOut(dataPin, clockPin, LSBFIRST, numberToDisplay);  
    //set latch pin high to send data to output pins
    digitalWrite(latchPin, HIGH);
}

void countUp() {
  //count up routine
  for (int j = 0; j < 256; j++) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, j);   
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    delay(1000);
  }
}




