
#include <Keyboard.h>

int buttonPin = 4;
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  bool isPressed;

  isPressed = !digitalRead(buttonPin);

  if(isPressed){
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.releaseAll();
  }
  Serial.println(isPressed);
}
