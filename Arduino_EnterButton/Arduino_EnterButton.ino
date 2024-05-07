
#include <Keyboard.h>
#include "Button.h"

const int buttonDelay = 2000;
unsigned long currentMillis;
unsigned long lastMillis;

Button kindButton(4);

void setup() {
  Keyboard.begin();
}

void loop() {
  currentMillis = millis();

  if((currentMillis - lastMillis) > buttonDelay){
    if(kindButton.isClicked()){
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      Serial.println("Clicked");
      lastMillis = currentMillis;
    }
    
    // if(kindButton.isReleased()){
    //   Serial.println("Released");
    //   Serial.println(currentMillis);
    //   lastMillis = currentMillis;
    // }
  }
}
