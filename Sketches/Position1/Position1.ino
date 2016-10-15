//Controlling Led By Button
//Turns on and off a LED ,when pressings button attach to pin12
//Email:support@sunfounder.com
//Website:www.sunfounder.com
//2015.5.7
/**********************************/
/**********************************/

const int pinX = A0;
const int pinY = A1;
const int pinZ = A2;

void setup()
{
  Serial.begin(9600);  
//  pinMode(pinX, INPUT);
//  pinMode(pinY, INPUT);
//  pinMode(pinZ, INPUT);
}
/**********************************/
void loop()
{
  int valueX = analogRead(pinX);
  int valueY = analogRead(pinY);
  int valueZ = analogRead(pinZ);

  int ovX = map(valueX, 0, 1023, 0, 255);  
  int ovY = map(valueY, 0, 1023, 0, 255);  
  int ovZ = map(valueZ, 0, 1023, 0, 255);  

  Serial.print(valueX);
  Serial.print("  ");
  Serial.print(valueY);
  Serial.print("  ");
  Serial.print(valueZ);
  Serial.print("  ");
  Serial.print(ovX);
  Serial.print("  ");
  Serial.print(ovY);
  Serial.print("  ");
  Serial.println(ovZ);

  delay(1000);
}
/************************************/
