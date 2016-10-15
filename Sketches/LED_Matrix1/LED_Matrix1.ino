void setup(){
  // ROWS (LOW = on)
  //set pins 6-13 as outputs  and initialize HIGH (so all LEDs are off to start)
  for (int pinNum=6;pinNum<14;pinNum++){
    pinMode(pinNum, OUTPUT);
    digitalWrite(pinNum, HIGH);
  }

  // COLS (HIGH = on)
  // Note: these are automatically initialized to LOW)
  //set pins A0-A6 as outputs
  for (int pinNum=A0;pinNum<A6;pinNum++){
    pinMode(pinNum, OUTPUT);
  }
  //set pins 2 and 3 as outputs
  for (int pinNum=2;pinNum<4;pinNum++){
    pinMode(pinNum, OUTPUT);
  }
}

void loop(){  
  for (int pinNum=6;pinNum<14;pinNum++){
    
    if (pinNum==8){
      setStates(56);
    } else {
      setStates(0);
    }
    
    digitalWrite(pinNum, LOW);
    digitalWrite(pinNum, HIGH);
  }
}

void setStates(byte states){
  zeroStates();//first turn all pins off
  //look at each bit of binary number and set HIGH if needed
  if (states & 1) digitalWrite(A0, HIGH);//check the first bit (least significant bit)
  if (states & 2) digitalWrite(A1, HIGH);//check the second bit
  if (states & 4) digitalWrite(A2, HIGH);
  if (states & 8) digitalWrite(A3, HIGH);
  if (states & 16) digitalWrite(A4, HIGH);
  if (states & 32) digitalWrite(A5, HIGH);
  if (states & 64) digitalWrite(2, HIGH);
  if (states & 128) digitalWrite(3, HIGH);//check the most significant bit
}

void zeroStates(){
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}
