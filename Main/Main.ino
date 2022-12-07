#include <FastLED.h>

# define numLEDS 25
# define LED_Pin 2

bool debug = false;

int row = 0;
int col = 0;
int delta = 1;
int brightness = 25;
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

String ParseString(String Input, char delim)
{
  String Output = "";

  for (int i = 0; i < Input.length(); i++)
  {
    if (Input[i] == delim)
    {
      break;
    }

    Output += Input[i];
  }

  return Output;
}

void UpdateLEDs(String HSV_Code)
{
  // Example Codes - c125,250,200

  // Finding the starting index of Hue,Sat,Val
  int hueIndex = HSV_Code.indexOf(',');
  int satIndex = HSV_Code.indexOf(',', hueIndex + 1);
  int valIndex = HSV_Code.indexOf(',', satIndex + 1);

  String HueCode = ParseString(HSV_Code.substring(1,hueIndex), ',');
  String SatCode = ParseString(HSV_Code.substring(hueIndex+1, satIndex), ',');
  String ValCode = ParseString(HSV_Code.substring(satIndex+1, valIndex), ',');

  if (debug == true) {
    Serial.println(HueCode + ", " + SatCode + ", " + ValCode);
  }

  // Update the LEDs with the HSV code
  fill_solid(leds, numLEDS, CRGB(HueCode.toInt(), SatCode.toInt(), ValCode.toInt()));
  // fill_solid(leds, numLEDS, CHSV(HueCode.toInt(), SatCode.toInt(), ValCode.toInt()));

  // Push the LED values to the matrix
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
      if (debug == true)
      {
        Serial.println(serialOutput);
      }

      if (serialOutput[0] == 'c')
      {
        UpdateLEDs(serialOutput);
      }

      serialOutput = "";
    }
  }
  
}

/*Test*/