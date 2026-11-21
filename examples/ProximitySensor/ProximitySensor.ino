// Proximity Sensor
// Uses the raw capacitive signal from one electrode as a rough "how close is my hand?" sensor.
// Open the Serial Plotter or Serial Monitor at 115200 baud to see the values.

#include <MPR121.h>

const uint8_t MPR121_ADDRESS = 0x5C;  // the Touch Board's MPR121 address
const uint8_t MPR121_INTERRUPT_PIN = 4;

const uint8_t electrode = 0;  // try any electrode from 0 to 11

// Change these after watching the plotter:
// min_signal ignores small noise; max_signal is roughly the value when touching.
const int min_signal = -5;
const int max_signal = 10;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  if (!MPR121.begin(MPR121_ADDRESS)) {
    // Fast blinking means the touch sensor could not be started.
    while (true) {
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      delay(100);
    }
  }

  MPR121.setInterruptPin(MPR121_INTERRUPT_PIN);

  // Keep hands away while the LED is on so the sensor can calibrate.
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  MPR121.autoSetElectrodes();
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  MPR121.updateFilteredData();
  MPR121.updateBaselineData();

  int filtered = MPR121.getFilteredData(electrode);
  int baseline = MPR121.getBaselineData(electrode);

  // The filtered value drops as a hand gets closer, so a bigger signal means closer.
  int signal = baseline - filtered;
  int closeness = map(constrain(signal, min_signal, max_signal), min_signal, max_signal, 0, 100);

  analogWrite(LED_BUILTIN, map(closeness, 0, 100, 0, 255));

  Serial.print("signal:");
  Serial.print(signal);
  Serial.print(",closeness:");
  Serial.println(closeness);

  delay(20);
}
