# Getting Started with Bare Conductive
A brief tutorial in getting up and running with the now sunsetted Bare Conductive capacitance touch development boards.

Since Bare Conductive has closed its doors, this guide uses the archived board definitions and libraries included as Git submodules in this repository.

This guide uses Arduino CLI to compile and upload the examples in [examples](examples). The board definitions stay in this repository instead of being copied into your normal Arduino Sketchbook.

## Prerequisites
* [Arduino CLI](https://arduino.github.io/arduino-cli/latest/installation/) installed
* Bare Conductive Touch Board
* Micro USB cable
* Git

## Step 1: Get the repository

Clone this repository and its submodules:
```bash
git clone --recurse-submodules https://github.com/ctlnorwich/Getting-Started-with-Bare-Conductive.git
cd Getting-Started-with-Bare-Conductive
```
If you already cloned without submodules, run `git submodule update --init --recursive` from the repository directory. The board platform is in `hardware/bareconductive/avr`.

## Step 2: Configure Arduino CLI and install the AVR core

Point Arduino CLI's user directory at this repository so it discovers the local board platform without adding it to your usual Sketchbook. The checkout acts as the CLI user directory for that terminal session; Arduino's downloaded cores and tools remain in their normal data directory. Run this in the repository root in each terminal session.

macOS / Linux:
```bash
export ARDUINO_DIRECTORIES_USER="$PWD"
```

Windows PowerShell:
```powershell
$env:ARDUINO_DIRECTORIES_USER = (Get-Location).Path
```

Install Arduino's AVR platform, which supplies the compiler and core used by the Touch Board definitions:
```bash
arduino-cli core update-index
arduino-cli core install arduino:avr
```

Install Arduino's Keyboard library for the Touch Keyboard example:
```bash
arduino-cli lib install Keyboard
```
Because the CLI user directory is set to this checkout, the library is installed in its `libraries` directory, not your usual Sketchbook. Run the user-directory command above before installing it and whenever compiling.

## Step 3: Upload an example

The MPR121 library's Arduino library root is the inner `MPR121` directory, not the parent `mpr121` repository. Pass that directory to Arduino CLI; this does not copy or install the library into a Sketchbook.

List connected ports and note the Touch Board's port:
```bash
arduino-cli board list
```

Compile and upload the Touch Keyboard example (replace `PORT` with the port shown above, such as `/dev/cu.usbmodem...` on macOS, `/dev/ttyACM0` on Linux, or `COM3` on Windows):
```bash
arduino-cli compile --upload --port PORT --fqbn bareconductive:avr:baretouch --library "$PWD/mpr121/MPR121" examples/TouchKeyboard
```

To upload a different example, replace `examples/TouchKeyboard` with its folder. The compile command works in PowerShell too; `$PWD` expands to the current repository directory.

When an example starts, keep your hands away from the electrodes while the LED is on; the board is calibrating. A fast-blinking LED means the touch sensor could not be started.

## Example 1: Touch Keyboard

[TouchKeyboard.ino](examples/TouchKeyboard/TouchKeyboard.ino) turns the Touch Board into a USB keyboard. Touching an electrode presses a key, and letting go releases it.

| Electrodes | Keys |
| --- | --- |
| E0-E3 | Up, Down, Left, Right arrows |
| E4-E7 | `w`, `a`, `s`, `d` |
| E8-E11 | Space, Return, Escape, `z` |

To try your own keys, edit `key_map` in the sketch. To change sensitivity, edit `touch_threshold` and `release_threshold`: lower values are more sensitive, and `release_threshold` must stay lower than `touch_threshold`. More special keys are listed in Arduino's [keyboard modifiers reference](https://docs.arduino.cc/language-reference/en/functions/usb/Keyboard/keyboardModifiers/).

## Example 2: Proximity Sensor

[ProximitySensor.ino](examples/ProximitySensor/ProximitySensor.ino) reads the raw capacitive signal from electrode E0 and uses its strength as a rough "distance to fingers" sensor. Upload it by replacing `examples/TouchKeyboard` with `examples/ProximitySensor` in the compile command.

To see the values, open the Serial Monitor:

```bash
arduino-cli monitor --port PORT --config baudrate=115200
```

For a live graph, open the sketch in the Arduino IDE and use **Tools > Serial Plotter** at 115200 baud. Move your hand towards and away from E0:

* `signal` is the MPR121's baseline minus its filtered reading. It increases as your hand gets closer.
* `closeness` maps `signal` to a value from 0 (far) to 100 (touching), and the board's LED gets brighter as it increases.

Things to try:

* Change `electrode` to use a different pad.
* Adjust `min_signal` and `max_signal` to match the values you see when your hand is far away and touching.
* Connect a larger piece of conductive material (such as foil or Electric Paint) to an electrode to sense from further away.

This is only a crude distance sensor. Readings vary with hand size, cable length, and the surface the board is on. If you hold your hand still, the MPR121 slowly adapts its baseline and the signal fades back towards zero.
