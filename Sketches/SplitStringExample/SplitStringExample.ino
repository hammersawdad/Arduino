/**********************************/
bool mStop = false;
int MAX_INPUT_VALUES = 20;

void setup()
{
  Serial.begin(9600);       // start serial communication at 115200bps
}

/**********************************/
void loop()
{
  if (!mStop)
  {
    String parsedValues[MAX_INPUT_VALUES];
    char delimiter = ' ';
    String inputValue = "12 34 56 78 90 as df gj kl";

    parseString(inputValue, delimiter, parsedValues); 

    mStop = true;

    for (int i=0; i < MAX_INPUT_VALUES; i++)
    {
      Serial.println(parsedValues[i]);
    } 
  }

  
}
/************************************/
void parseString(String input, char delimiter, String *outputArray)
{
    int delimiterPos;
    String patialText;

    for (int i=0; i < MAX_INPUT_VALUES; i++)
    {
        if (input.length() > 0)
        {
          delimiterPos = input.indexOf(' ');
          outputArray[i] = input.substring(0,delimiterPos);
          input = input.substring(delimiterPos + 1);

          if(delimiterPos < 0)
          {
            input = "";
          }
        }
        else
        {
          outputArray[i] = "";
        }
    } 
}


