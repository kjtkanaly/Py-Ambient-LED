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

CRGB leds[numLEDS];

uint8_t hue;

void setup() {
  
  Serial.begin(9600);

  FastLED.addLeds<WS2812B, LED_Pin, GRB>(leds,numLEDS);
  FastLED.setBrightness(25);

  hue = 0;

  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  while (Serial.available())
  {
    serialData = Serial.read();
  }

  if (serialData == '1')
  {
    for(int i = 0; i < numLEDS; i++)
    {
      leds[i] = CHSV(127, 255, 255);
    }

    digitalWrite(LED_BUILTIN, HIGH);

    Serial.println("Matrix Online!");
  }

  else if (serialData == '0')
  {
    for(int i = 0; i < numLEDS; i++)
    {
      leds[i] = CHSV(0, 0, 0);
    }

    digitalWrite(LED_BUILTIN, LOW);

    Serial.println("Matrix Offline!");
  }

  FastLED.show();
}

/*Test*/