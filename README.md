# Getting Started with Bare Conductive
A brief tutorial in getting up and running with the now sunsetted Bare Conductive capacitance touch development boards.

Since Bare Conductive has closed its doors, this guide uses the archived board definitions and libraries included as Git submodules in this repository.

This guide uses Arduino CLI to compile and upload the HID Keyboard example. The board definitions stay in this repository instead of being copied into your normal Arduino Sketchbook.

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

Install Arduino's Keyboard library for the example:
```bash
arduino-cli lib install Keyboard
```
Because the CLI user directory is set to this checkout, the library is installed in its `libraries` directory, not your usual Sketchbook. Run the user-directory command above before installing it and whenever compiling.

## Step 3: Compile and upload the HID Keyboard example

The MPR121 library's Arduino library root is the inner `MPR121` directory, not the parent `mpr121` repository. Pass that directory to Arduino CLI; this does not copy or install the library into a Sketchbook.

List connected ports and note the Touch Board's port:
```bash
arduino-cli board list
```

Compile and upload (replace `PORT` with the port shown above, such as `/dev/cu.usbmodem...` on macOS, `/dev/ttyACM0` on Linux, or `COM3` on Windows):
```bash
arduino-cli compile --upload --port PORT --fqbn bareconductive:avr:baretouch --library "$PWD/mpr121/MPR121" hid-keyboard/HID_Keyboard
```

The compile command works in PowerShell too; `$PWD` expands to the current repository directory.

### Customizing Keystrokes

If you want to modify the code to change which keys are pressed, you can adjust the mapping and sensitivity within the sketch. Here is an example of how you might declare the key mapping and threshold variables cleanly:

```cpp
// Example of mapping electrodes to keys
int key_map[12] = {
  KEY_UP_ARROW,
  KEY_DOWN_ARROW,
  KEY_LEFT_ARROW,
  KEY_RIGHT_ARROW,
  'w',
  'a',
  's',
  'd',
  ' ', // spacebar
  KEY_RETURN,
  KEY_ESC,
  'z'
};

// Adjust these values to change touch sensitivity
int touch_threshold = 40;
int release_threshold = 20;
```

Once uploaded, touching the twelve electrode pads on the edge of the board will send the corresponding mapped keystrokes directly to your computer.
