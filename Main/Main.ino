#include <FastLED.h>

# define numLEDS 25
# define LED_Pin 2

int row           = 0;
int col           = 0;
int delta         = 1;
int brightness    = 25;
int hueLedPin     = 4;
int satLedPin     = 5;
int valLedPin     = 6;
int serialData;

String serialOutput = "";

CRGB leds[numLEDS];

void setup() {
  
  // Begin the serial comms
  Serial.begin(9600);

  // Initialize the LED matrix
  FastLED.addLeds<WS2812B, LED_Pin, GRB>(leds,numLEDS);
  FastLED.setBrightness(brightness);

  // Turn the LEDs off
  for(int i = 0; i < numLEDS; i++)
  {
    leds[i] = CHSV(0, 0, 0);
  }
  FastLED.show();

  // Initialize my logic check LEDs
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(hueLedPin, OUTPUT);
  pinMode(satLedPin, OUTPUT);
  pinMode(valLedPin, OUTPUT);
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