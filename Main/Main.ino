#include <FastLED.h>

# define numLEDS 25
# define LED_Pin 2

int row         = 0;
int col         = 0;
int delta       = 1;
int brightness  = 25;
int serialData;

float freq = 0.5;
float pi = 3.14;

String serialOutput = "";
String HSV_Code = "";

CRGB leds[numLEDS];

uint8_t hue;

void setup() {
  
  Serial.begin(9600);

  FastLED.addLeds<WS2812B, LED_Pin, GRB>(leds,numLEDS);
  FastLED.setBrightness(25);

  hue = 0;

  pinMode(LED_BUILTIN, OUTPUT);

  for(int i = 0; i < numLEDS; i++)
  {
    leds[i] = CHSV(0, 0, 0);
  }

  FastLED.show();
}

void UpdateLEDs(String HSV_Code)
{
  // Example Code - H125S250V200

  String HueCode = "";
  String SatCode = "";
  String ValCode = "";

  int index = 1;
  while (HSV_Code.substring(index, index+1) != 'S')
  { 
    HueCode += HSV_Code.substring(index, index+1);
    index++;
  }

  index++;

  while (HSV_Code.substring(index, index+1) != 'V')
  {
    SatCode += HSV_Code.substring(index, index+1);
    index++;
  }

  index++;

  while (index < HSV_Code.length())
  {
    ValCode += HSV_Code.substring(index, index+1);
    index++;
  }

  for(int i = 0; i < numLEDS; i++)
  {
    leds[i] = CHSV(HueCode.toInt(), SatCode.toInt(), ValCode.toInt());
  }

  FastLED.show();
}

// the loop function runs over and over again forever
void loop() {

  while (Serial.available())
  {
    serialData = Serial.read();
    
    if (char(serialData) != '\n')
    {
      serialOutput += char(serialData);
    }

    else
    {
      Serial.println(serialOutput);
      UpdateLEDs(serialOutput);
      serialOutput = "";
    }
  }
  
  /*while (Serial.available())
  {
    serialData = Serial.read();

    if (serialData == '1')
    {
      for(int i = 0; i < numLEDS; i++)
      {
        leds[i] = CHSV(127, 255, 255);
      }

      digitalWrite(LED_BUILTIN, HIGH);

      Serial.print("Matrix Online!");
      Serial.print("\n");
    }

    else if (serialData == '0')
    {
      for(int i = 0; i < numLEDS; i++)
      {
        leds[i] = CHSV(0, 0, 0);
      }

      digitalWrite(LED_BUILTIN, LOW);

      Serial.print("Matrix Offline!");
      Serial.print("\n");
    }
    
    else if (serialData == 'c')
    {
      /*
      int hue = serialData.substring(0,3).toInt();
      int sat = serialData.substring(6,9).toInt();
      int val = serialData.substring(12,15).toInt();
      

      Serial.print(String(hue) + ", " + String(sat) + ", " + String(val));

    }

    FastLED.show();*/
}

/*Test*/