//set 595 state

int clockPin = 4;
int latchPin = 3;
int dataPin = 2;

int rowPins[] = {6,7,8,9,10,11,12,13};

byte numberToDisplay = 74;


void setup() {
  //all connections to 595 are outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // ROWS (LOW = on)
  //set row pins as outputs and initialize to HIGH (so all LEDs are off to start)
  for (int index =0; index<sizeof(rowPins); index++)
  {
    pinMode(rowPins[index], OUTPUT);
    digitalWrite(rowPins[index], HIGH);
  }
}

void loopXXX() {
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







void loop(){  
  for (int index =0; index<sizeof(rowPins); index++)
  {
    int pinNum = rowPins[index];

    clearColumns();
    
    if (index == 3)
    {
      setValue(numberToDisplay);   
    }
    else
    {
    clearColumns();      
    }

    
    digitalWrite(pinNum, LOW);
    digitalWrite(pinNum, HIGH);
  }
}

void clearColumns()
{
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, 0);   
    digitalWrite(latchPin, HIGH);
}
void setValue(int dataValue)
{
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, dataValue);   
    digitalWrite(latchPin, HIGH);
}



