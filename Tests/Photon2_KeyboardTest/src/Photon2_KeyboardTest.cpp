/* 
 * Photon 2 Keyboard Test
 * Author: Daniel Stromberg
 * Date: 5/23/24
*/

#include "Particle.h"
#include <neopixel.h>
#include "Button.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

STARTUP(Keyboard.begin());

const int buttonDelay = 2000;   //time to hold button before sending print command
const int PIXEL_COUNT = 16;
const int LED_PIN = 3;
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

void setup() {
  delay(10000);
  Keyboard.click(KEY_ENTER);
}

void loop() {

}
