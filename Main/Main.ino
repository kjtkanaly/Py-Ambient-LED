#include <FastLED.h>

# define numLEDS 25
# define LED_Pin 2

int row           = 0;
int col           = 0;
int delta         = 1;
int brightness    = 25;
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

  // Debug: Send back the HSV code
  Serial.println(HueCode + ", " + SatCode + ", " + ValCode);

  /* // Update the LEDs with the HSV code
  for(int i = 0; i < numLEDS; i++)
  {
    leds[i] = CHSV(HueCode.toInt(), SatCode.toInt(), ValCode.toInt());
  }

  // Push the LED values to the matrix
  FastLED.show(); */
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
  
}

/*Test*/