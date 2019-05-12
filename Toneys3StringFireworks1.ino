/*
 * I'm simulating fireworks on 3 addressable LED strips. 
 * The code works and it's a nice effect. 
 * I have a Mosfet on pin 12 that goes high causing a solenoid 
 * to bang up against some metal so the explosion makes noise. 
 * I'm having issues with it crashing due to line #110 going below zero 
 * That causes the random color to never change
 * If I set line 110 to zero instead of -8, random colors work but 
 * the firework nover compleats it's trip to the ground.
Comments more than welcome. 
*/

#include <FastLED.h>
#define NUM_LEDS_PER_STRIP 38  // the strips only 30 each but I had to set this to 38 to get trails.
CRGB LedStrip1[NUM_LEDS_PER_STRIP+8];
CRGB LedStrip2[NUM_LEDS_PER_STRIP+8];
CRGB LedStrip3[NUM_LEDS_PER_STRIP+8];
void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, 16>(LedStrip1, NUM_LEDS_PER_STRIP+8); // Sets Pin 16 as a data pin
  FastLED.addLeds<NEOPIXEL, 17>(LedStrip2, NUM_LEDS_PER_STRIP+8);
  FastLED.addLeds<NEOPIXEL, 18>(LedStrip3, NUM_LEDS_PER_STRIP+8);
  delay(20);
  Serial.println ("3 Line Firework Display Starting Now");
  pinMode (12, OUTPUT); // output to solenoid to make sound
  pinMode (2, OUTPUT); // Onboard LED
}
void loop() {
     //Lite
    Serial.println("");
    Serial.print("Lite: ");
    for (int Lite = 3; Lite != 0; Lite--) {  // counts down from 3
      Serial.print(Lite);
      Serial.print (" ");
      int Color = 60; // 60 is a Yellow
      LedStrip1[0] = CHSV(Color, 255, 110);
      LedStrip2[0] = CHSV(Color, 255, 110);
      LedStrip3[0] = CHSV(Color, 255, 110);
      FastLED.show();
      delay (1000);
    }
    //Launch
    Serial.println ("");
    Serial.print("Launch: ");
    for (int LaunchCount = 0; LaunchCount < 38; LaunchCount++)  {
      Serial.print (LaunchCount);
      Serial.print (" ");
      int Color = 60; // 60 is a Yellow
      LedStrip1[LaunchCount - 1] = CHSV(Color, 255, 255);
      LedStrip1[LaunchCount - 2] = CHSV(Color, 255, 220);
      LedStrip1[LaunchCount - 3] = CHSV(Color, 255, 175);
      LedStrip1[LaunchCount - 4] = CHSV(Color, 255, 110);
      LedStrip1[LaunchCount - 5] = CHSV(Color, 255, 60);
      LedStrip1[LaunchCount - 6] = CHSV(Color, 255, 25);
      LedStrip1[LaunchCount - 7] = CHSV(Color, 255, 0);

      LedStrip2[LaunchCount] = CRGB::Orange;
      
      LedStrip3[LaunchCount] = CRGB::Orange;
      delay(20);
      FastLED.show();

      // clear our current dot before we move on
      LedStrip1[LaunchCount] = CRGB::Black;
      LedStrip2[LaunchCount] = CRGB::Black;
      LedStrip3[LaunchCount] = CRGB::Black;
      delay(1);
      FastLED.show();
    }
    // explode
    Serial.println ("");
    Serial.print("Explode: ");
    int randColorExplode = (rand() % 255) + 1;
    for (int ExplodeValue = 0; ExplodeValue < 10; ExplodeValue++) {
      Serial.print (ExplodeValue);
      Serial.print (" ");
      LedStrip1[29] = CRGB::White;
      digitalWrite (12, HIGH); // output to solenoid to make sound
      digitalWrite (2, 1); // Onboard LED
      LedStrip2[29] = CRGB::Black;
      LedStrip3[29] = CRGB::White;
      delay(20);
      digitalWrite (12, LOW);// output to solenoid to make sound
      digitalWrite(2, 0);// Turns Off onboard LED
      FastLED.show();
      LedStrip1[29] = CRGB::Black;
      LedStrip2[29] = CRGB::White;
      LedStrip3[29] = CRGB::Black;
      delay(50);
      FastLED.show();
      LedStrip1[29] =  CHSV(randColorExplode, 255, 255);
      LedStrip2[29] = CRGB::Black;
      LedStrip3[29] = CRGB::Red;
      delay(50);
      FastLED.show();
      LedStrip1[29] = CRGB::Black;
      LedStrip2[29] = CRGB::Blue;
      LedStrip3[29] = CRGB::Black;
      delay(50);
      FastLED.show();
    }
    
    // fall back
    int randColor1 = (rand() % 255) + 1;
    int randColor2 = (rand() % 255) + 1;
    int randColor3 = (rand() % 255) + 1;
    int fallValue = 29;
    Serial.println ("");
    Serial.print("Fall Back: ");
    for (int FallBackValue = fallValue; FallBackValue != -8; FallBackValue--) {
      Serial.print (FallBackValue);
      Serial.print (" ");
      
      LedStrip1[FallBackValue] = CHSV(randColor1, 255, 255);
      LedStrip1[FallBackValue + 1] = CHSV(randColor1, 255, 240);
      LedStrip1[FallBackValue + 2] = CHSV(randColor1, 255, 220);
      LedStrip1[FallBackValue + 3] = CHSV(randColor1, 255, 175);
      LedStrip1[FallBackValue + 4] = CHSV(randColor1, 255, 110);
      LedStrip1[FallBackValue + 5] = CHSV(randColor1, 255, 60);
      LedStrip1[FallBackValue + 6] = CHSV(randColor1, 255, 0);
    
      LedStrip2[FallBackValue] = CHSV(randColor2, 255, 255);
      LedStrip2[FallBackValue + 1] = CHSV(randColor2, 255, 240);
      LedStrip2[FallBackValue + 2] = CHSV(randColor2, 255, 220);
      LedStrip2[FallBackValue + 3] = CHSV(randColor2, 255, 175);
      LedStrip2[FallBackValue + 4] = CHSV(randColor2, 255, 110);
      LedStrip2[FallBackValue + 5] = CHSV(randColor2, 255, 60);
      LedStrip2[FallBackValue + 6] = CHSV(randColor2, 255, 0);
   
      LedStrip3[FallBackValue] = CHSV(randColor3, 255, 255);
      LedStrip3[FallBackValue + 1] = CHSV(randColor3, 255, 240);
      LedStrip3[FallBackValue + 2] = CHSV(randColor3, 255, 220);
      LedStrip3[FallBackValue + 3] = CHSV(randColor3, 255, 175);
      LedStrip3[FallBackValue + 4] = CHSV(randColor3, 255, 110);
      LedStrip3[FallBackValue + 5] = CHSV(randColor3, 255, 60);
      LedStrip3[FallBackValue + 6] = CHSV(randColor3, 255, 0);
      
      FastLED.show();
      // clear our current dot before we move on
      LedStrip1[0] = CRGB::Black;
      LedStrip2[0] = CRGB::Black;
      LedStrip3[0] = CRGB::Black;
      delay(250);
      FastLED.show();
    }
    Serial.println ("");
    Serial.println ("");
    Serial.print ("Starting Loop Over In: ");
    for (int DelayValue = 2; DelayValue > -1; DelayValue --) {
      Serial.print(DelayValue);
      Serial.print (" ");
      delay (1000);
    }
  }
