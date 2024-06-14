/* 
 * Kindness Challenge Printer Button
 * Author: Daniel Stromberg
 * Date: 5/23/24
*/

#include "Particle.h"
#include "Button.h"
#include <neopixel.h>
#include <math.h>
#include "credentials.h"
#include <Adafruit_MQTT.h>
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h"
#include "Adafruit_MQTT/Adafruit_MQTT.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);


const int BUTTON_DELAY = 4000;   //time to hold button before sending print command
const int PRINTER_DELAY = 1000; //How long it takes to print after signal is sent
int fullCircleTime = BUTTON_DELAY + PRINTER_DELAY;
const int PIXEL_COUNT = 192;  //192 pixels on neon-style strip
unsigned long currentMillis;
unsigned long lastMillis;
int brightness = 100;
unsigned int pressedTime = 0;
unsigned int lastClicked = 0;

int lastLitLED = 0;
float t;
bool isFirstButtonHold = true;
int printCount = 0;
bool isDashButtonPressed = false;

Adafruit_NeoPixel pixel(PIXEL_COUNT, SPI1, WS2812);
Button kindButton(4);

int pulseLEDs(int timeIn);
void MQTT_connect();
bool MQTT_ping();

TCPClient TheClient;
Adafruit_MQTT_SPARK mqtt(&TheClient, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe printSub = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/pressprint");
Adafruit_MQTT_Publish printPub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/printercount");

STARTUP(Keyboard.begin());


void setup() {
  Serial.begin(9600);
  pixel.begin();
  pixel.setBrightness(brightness);
  mqtt.subscribe(&printSub);
}

void loop() { 
  currentMillis = millis();
  pixel.setBrightness(brightness);

  Adafruit_MQTT_Subscribe *subscription;
  // while((subscription = mqtt.readSubscription(100))){
  //   if(subscription == &printSub){
  //     isDashButtonPressed = true;
  //     // Serial.printf("Dash Button Pressed!\n");
  //   }
  // }

  if (kindButton.isClicked()) {
    lastClicked = currentMillis;
    isFirstButtonHold = true;
    // Serial.printf("CLICKED\n");     
  }

  if (kindButton.isPressed()) {
    pressedTime = currentMillis - lastClicked;
    lastLitLED = map(pressedTime, 0, fullCircleTime, 0, PIXEL_COUNT);

    if(isFirstButtonHold){ 
      if((pressedTime > BUTTON_DELAY)){
        // Serial.println("SEND TO PRINTER!!!");
        Keyboard.click(KEY_RETURN);
        printCount++;
        // if(mqtt.Update()){
        //   printPub.publish(printCount);
        // }
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


  // if ((currentMillis - lastMillis) > BUTTON_DELAY) {
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

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care of connecting.
void MQTT_connect(){
    int8_t ret;

    // Return if already connected.
    if (mqtt.connected()){
        return;
    }

    Serial.print("Connecting to MQTT... ");

    while((ret = mqtt.connect()) != 0){
        Serial.printf("Error Code %s\n", mqtt.connectErrorString(ret));
        Serial.printf("Retrying MQTT connection in 5 seconds...\n");
        mqtt.disconnect();
        delay(5000);
    }
    Serial.printf("MQTT Connected!\n");
}

//Keeps the connection open to Adafruit
bool MQTT_ping() {
    static unsigned int last;
    bool pingStatus;

    if ((millis()-last)>120000) {
        Serial.printf("Pinging MQTT \n");
        pingStatus = mqtt.ping();
        if(!pingStatus) {
        Serial.printf("Disconnecting \n");
        mqtt.disconnect();
        }
        last = millis();
    }
    return pingStatus;
}