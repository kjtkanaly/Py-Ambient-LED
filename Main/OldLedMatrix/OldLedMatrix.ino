#include <FastLED.h>

# define NUM_LEDS 25
# define LED_PIN 2

CRGB leds[NUM_LEDS];

uint8_t hue;

int numOfCOLS = 5;
int numOfROWS = 5;
int row = 0;
int col = 0;
int delta = 1;

float freq = 0.5;
float pi = 3.14;

int dispMode = 3;

void setup(){
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds,NUM_LEDS);
  FastLED.setBrightness(25);

  hue = 0;
}

void loop(){
  
  EVERY_N_MILLISECONDS(50)
  {
    /////////////////////////////////////////////////////////////////////
    // Indexing through the Rows
    if(dispMode == 0)
    {
      for (int i = 0; i < NUM_LEDS; i++)
      {
          if(((i % numOfCOLS) == row) && ((i / numOfCOLS) == col))
          {
            leds[i] = CHSV(127, 255, 255);
          } 
          else
          {
            leds[i] = CHSV(0, 0, 0);
          }
      }
    
      col++;
      if(col == 5)
      {
        row++;
        col = 0;
      }
      if(row == 5)
      {
        row = 0;
      }
    }

    /////////////////////////////////////////////////////////////////////
    // Vertical Rainbow Bar Moving Back and Forth
    if(dispMode == 1)
    {      
      for(int i = 0; i < NUM_LEDS; i++)
      {
        if((i / numOfCOLS) == col){
          leds[i] = CHSV(hue,255,255);
        }
        else{
          leds[i] = CHSV(hue,255,0);
        }
      }

      col = col + delta;
      
      if(col == (numOfCOLS - 1)){
        delta = -1;
        //col = 0;
      }
      if(col == 0)
      {
        delta = 1;
      }

      hue += 10;
    }

    /////////////////////////////////////////////////////////////////////
    // Whole Array Displays a rainbow fade
    if(dispMode == 2)
    {
      for(int i = 0; i < NUM_LEDS; i++)
      {
        leds[i] = CHSV(hue, 255, 255);
      }
      hue++;
    }

    /////////////////////////////////////////////////////////////////////
    // Rainbow Pulse Emiting from the center
    if(dispMode == 3)
    {
      for(int i = 0; i < NUM_LEDS; i++)
      {
        if(((i / numOfCOLS) == 2) && ((i % numOfCOLS) == 2)){
          leds[i] = CHSV(hue,255,255);
        }
        
        if(((i / numOfCOLS) == 1) && ((i % numOfCOLS) >= 1) && ((i % numOfCOLS) <= 3)){
          leds[i] = CHSV(hue - 20,255,255);
        }
        if(((i / numOfCOLS) == 3) && ((i % numOfCOLS) >= 1) && ((i % numOfCOLS) <= 3)){
          leds[i] = CHSV(hue - 20,255,255);
        }
        if(((i / numOfCOLS) == 2) && ((i % numOfCOLS) == 1)){
          leds[i] = CHSV(hue - 20,255,255);
        }
        if(((i / numOfCOLS) == 2) && ((i % numOfCOLS) == 3)){
          leds[i] = CHSV(hue - 20,255,255);
        }

        if((i / numOfCOLS) == 0){
          leds[i] = CHSV(hue - 40,255,255);
        }
        if((i / numOfCOLS) == 4){
          leds[i] = CHSV(hue - 40,255,255);
        }
        if((i % numOfCOLS) == 0){
          leds[i] = CHSV(hue - 40,255,255);
        }
        if((i % numOfCOLS) == 4){
          leds[i] = CHSV(hue - 40,255,255);
        }
        
      }

      hue += 10;
    }

  FastLED.show();
  }
}

/*
uint8_t testFx(int numOfLEDS, int numOfROWS, int numOfCOLS){

  uint8_t hue[numOfLEDS];
  
  int row = 0;
  int col = 0;
  


  col++;
  if(col == 5)
  {
    row++;
    col = 0;
  }
  if(row == 5)
  {
    row = 0;
  }

  return hue;
}*/


