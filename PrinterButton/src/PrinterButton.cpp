/* 
 * Kindness Challenge Printer Button
 * Author: Daniel Stromberg
 * Date: 5/23/24
 * 
 * Names of Photons in use:
 * Easy: RndActs_EZ
 * Medium: RndActs_Med
 * Hard: RndActs_Hard
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


const int EZ_BUTTON_DELAY = 3000;   //time to hold button before sending print command
const int MED_BUTTON_DELAY = 6000;
const int HARD_BUTTON_DELAY = 9000;
const int PRINTER_DELAY = 1000; //How long it takes to print after signal is sent
const int PIXEL_COUNT = 314;  //314 pixels on neon-style strip
const int HARD_COLOR_RED = 0xFF1105;    //old DS red: 0xFF1105, brand red: 0xC56B29
const int MED_COLOR_YELLOW = 0xFF8805;  //old DS yellow: 0xFF8805, brand yellow:0xF1AA1E
const int EZ_COLOR_GREEN = 0x6AC2C4;    //old DS green: 0x33FF22

/////////////////// CHANGE BELOW DEPENDING ON DIFFICULTY ///////////////////
//
const int THIS_STRIP_COLOR = HARD_COLOR_RED;      //change color here depending on the difficulty
const int THIS_BUTTON_DELAY = HARD_BUTTON_DELAY;    //change delay here depending on the difficulty
//
////////////////////////////////////////////////////////////////////////////

int fullCircleTime = THIS_BUTTON_DELAY + PRINTER_DELAY;
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
  pinMode(D7, OUTPUT);

  for(int i =0; i<PIXEL_COUNT; i++){
    pixel.setPixelColor(i, THIS_STRIP_COLOR);
    pixel.show();
    delay(10);
  }
  delay(1000);
  // pixel.clear();
  // pixel.show();
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
      if((pressedTime > THIS_BUTTON_DELAY)){
        // Serial.println("SEND TO PRINTER!!!");
        Keyboard.click(KEY_RETURN);
        printCount++;
        // if(mqtt.Update()){
        //   printPub.publish(printCount);
        // }
        isFirstButtonHold = false;
        digitalWrite(D7, HIGH);
      }
    }

    for (int i = 0; i < PIXEL_COUNT; i++) {
      if (i < lastLitLED) {
        pixel.setPixelColor(i, THIS_STRIP_COLOR);

        // Use below to find last pixel on strip.
        //
        // if(i>= (PIXEL_COUNT-1)){
        //   pixel.setPixelColor(i, 0x00FF00);
        // }

      } else {
        pixel.setPixelColor(i, 0);
      }
    }

    if (pressedTime > fullCircleTime) {
      brightness = pulseLEDs(pressedTime);
    }
  } else {
    pixel.clear();
    digitalWrite(D7, LOW);
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