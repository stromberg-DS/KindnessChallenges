/* 
 * Kindness Challenge Printer Button
 * Author: Daniel Stromberg
 * Date: 5/23/24
*/

#include "Particle.h"
#include "Button.h"
#include <neopixel.h>
#include <math.h>

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);


const int buttonDelay = 2000;   //time to hold button before sending print command
const int PIXEL_COUNT = 16;
unsigned long currentMillis;
unsigned long lastMillis;
int brightness = 100;
unsigned int pressedTime = 0;
unsigned int lastClicked = 0;
int fullCircleTime = 5000;
int lastLitLED = 0;
float t;
bool isFirstButtonHold = true;

Adafruit_NeoPixel pixel(PIXEL_COUNT, SPI1, WS2812);
Button kindButton(4);

int pulseLEDs(int timeIn);

STARTUP(Keyboard.begin());


void setup() {
  Serial.begin(9600);
  pixel.begin();
  pixel.setBrightness(brightness);
}

void loop() { 
  currentMillis = millis();
  pixel.setBrightness(brightness);

  if (kindButton.isClicked()) {
    lastClicked = currentMillis;
    isFirstButtonHold = true;
    Serial.printf("CLICKED\n");     
  }

  if (kindButton.isPressed()) {
    pressedTime = currentMillis - lastClicked;
    lastLitLED = map(pressedTime, 0, fullCircleTime, 0, PIXEL_COUNT);

    if(isFirstButtonHold){
      if(pressedTime > buttonDelay){
        Serial.println("SEND TO PRINTER!!!");
        Keyboard.press(KEY_RETURN);
        Keyboard.releaseAll();
        isFirstButtonHold = false;
      }
    }

    for (int i = 0; i < PIXEL_COUNT; i++) {
      if (i < lastLitLED) {
        pixel.setPixelColor(i, 0xAA22AA);
      } else {
        pixel.setPixelColor(i, 0);
      }
    }

    if (pressedTime > fullCircleTime) {
      brightness = pulseLEDs(pressedTime);
    }
  } else {
    pixel.clear();
    brightness = 100;
  }


  // if ((currentMillis - lastMillis) > buttonDelay) {
  //   if (kindButton.isClicked()) {
  //     Keyboard.press(KEY_RETURN);
  //     Keyboard.releaseAll();
  //     Serial.println("Clicked");
  //     lastMillis = currentMillis;
  //   }
  // }

  pixel.show();
}

int pulseLEDs(int timeIn) {
  float pulseSpeed = 1.5;
  
  timeIn -= fullCircleTime;
  t = timeIn / 1000.0;
  return 40 * sin((M_PI * t *1.5) + M_PI_2) + 60;
}

