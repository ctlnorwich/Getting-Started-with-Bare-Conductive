// Touch Keyboard
// Touch an electrode to press a key on your computer. Let go to release it.

#include <MPR121.h>
#include <Keyboard.h>

const uint8_t MPR121_ADDRESS = 0x5C;  // the Touch Board's MPR121 address
const uint8_t MPR121_INTERRUPT_PIN = 4;

// Key sent by each electrode, from E0 to E11
const uint8_t key_map[12] = {
  KEY_UP_ARROW,
  KEY_DOWN_ARROW,
  KEY_LEFT_ARROW,
  KEY_RIGHT_ARROW,
  'w',
  'a',
  's',
  'd',
  ' ',  // spacebar
  KEY_RETURN,
  KEY_ESC,
  'z'
};

// Lower values are more sensitive. release_threshold must be lower than touch_threshold.
const uint8_t touch_threshold = 40;
const uint8_t release_threshold = 20;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  if (!MPR121.begin(MPR121_ADDRESS)) {
    // Fast blinking means the touch sensor could not be started.
    while (true) {
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      delay(100);
    }
  }

  MPR121.setInterruptPin(MPR121_INTERRUPT_PIN);
  MPR121.setTouchThreshold(touch_threshold);
  MPR121.setReleaseThreshold(release_threshold);

  // Keep hands away while the LED is on so the sensor can calibrate.
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  MPR121.autoSetElectrodes();
  digitalWrite(LED_BUILTIN, LOW);

  Keyboard.begin();
}

void loop() {
  MPR121.updateTouchData();

  for (uint8_t electrode = 0; electrode < 12; electrode++) {
    if (MPR121.isNewTouch(electrode)) {
      Keyboard.press(key_map[electrode]);
    } else if (MPR121.isNewRelease(electrode)) {
      Keyboard.release(key_map[electrode]);
    }
  }

  digitalWrite(LED_BUILTIN, MPR121.getNumTouches() > 0);
}
