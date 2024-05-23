#include <Adafruit_NeoPixel.h>
#include <Keyboard.h>
#include "Button.h"


const int buttonDelay = 2000;
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

Adafruit_NeoPixel pixel(PIXEL_COUNT, LED_PIN, NEO_GRB);
Button kindButton(4);

int pulseLEDs(int timeIn);

void setup() {
  Keyboard.begin();
  pixel.begin();
  pixel.setBrightness(brightness);
}

void loop() {
  currentMillis = millis();
  pixel.setBrightness(brightness);
  Serial.println(brightness);


  if (kindButton.isClicked()) {
    lastClicked = currentMillis;
  }

  if (kindButton.isPressed()) {
    pressedTime = currentMillis - lastClicked;
    lastLitLED = map(pressedTime, 0, fullCircleTime, 0, PIXEL_COUNT);
    for (int i = 0; i < PIXEL_COUNT; i++) {
      if (i < lastLitLED) {
        pixel.setPixelColor(i, 0xFF0000);
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

  // LED loop test
  // for (int i = 0; i < PIXEL_COUNT; i++) {
  //   pixel.clear();
  //   pixel.setPixelColor(i, 0xFF0000);
  //   pixel.show();
  //   delay(50);
  // }



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
  timeIn -= fullCircleTime;
  t = timeIn / 1000.0;
  Serial.print("Time in:");
  Serial.println(timeIn);
  return 40 * sin((PI * t / 2.0) + (PI/2)) + 60;
}
