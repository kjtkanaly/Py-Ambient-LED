#include <FastLED.h>

# define numLEDS 25
# define LED_Pin 2

bool debugSerialIn = false;

int row = 0;
int col = 0;
int delta = 1;
int brightness = 25;
int saturation = 255;
int value = 255;
int serialData;

float previousHue = 0;
float goalHue = 0;
float hueStepSize = 0.1;
float updateHue;

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


// Example Hue Value - h125
int UpdateGoalHueValue(String hueCode, bool debug=true)
{
  hueCode = hueCode.substring(1);

  if (debug == true) {
    Serial.println(hueCode + ", " + saturation + ", " + value);
  }

  return (hueCode.toInt());
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
      if (debugSerialIn == true)
      {
        Serial.println(serialOutput);
      }

      if (serialOutput[0] == 'h')
      {
        goalHue = float(UpdateGoalHueValue(serialOutput));
      }

      serialOutput = "";
    }
  }

  // Step the current hue value towards the goal
  if (previousHue != goalHue)
  {
    if (previousHue < goalHue)
    {
      if (previousHue < goalHue - hueStepSize)
      {
        updateHue = previousHue + hueStepSize;
      }
      else
      {
        updateHue = goalHue;
      }
    }
    else
    {
      if (previousHue > goalHue + hueStepSize)
      {
        updateHue = previousHue - hueStepSize;
      }
      else
      {
        updateHue = goalHue;
      }
    }

    // Update the LEDs
    fill_solid(leds, numLEDS, CHSV(updateHue, saturation, value));
    FastLED.show();

    previousHue = updateHue;
  }
  
}