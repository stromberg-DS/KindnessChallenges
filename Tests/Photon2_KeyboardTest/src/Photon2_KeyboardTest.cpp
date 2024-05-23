/* 
 * Photon 2 Keyboard Test
 * Author: Daniel Stromberg
 * Date: 5/23/24
*/

#include "Particle.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

STARTUP(Keyboard.begin());

void setup() {
  delay(10000);
  Keyboard.click(KEY_ENTER);
}

void loop() {

}
