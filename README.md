# Getting-Started-with-Bare-Conductive
A brief tutorial in getting up and running with the now sunsetted Bare Conductive capacitance touch development boards.

Since Bare Conductive has closed its doors, the official Arduino Boards Manager URLs and automated installers may no longer function. However, thanks to the open-source nature of their tools, you can still easily set up and program your Touch Board using manual installation methods directly from their GitHub archives.

This guide will walk you through setting up the hardware definitions, installing the required MPR121 library, and running the HID Keyboard example.

## Prerequisites
* Arduino IDE installed (v1.8.x or v2.x)
* Bare Conductive Touch Board
* Micro USB cable
* Git (optional, if using command-line installation methods)

## Step 1: Install the Hardware Definitions

Because the official package index is offline, we must install the board definitions manually. Locate your Arduino Sketchbook folder (found in the Arduino IDE under **File > Preferences** next to "Sketchbook location", commonly `Documents/Arduino`). Inside the Sketchbook folder, look for a folder named `hardware` (create it if it doesn't exist).

**Option A: Git Clone (Recommended)**
Open your terminal or command prompt, navigate to your Sketchbook's `hardware` folder, and run the following commands:
```bash
mkdir -p bareconductive
cd bareconductive
git clone https://github.com/BareConductive/bare-conductive-arduino.git avr
```
*Note: The Arduino IDE expects the architecture folder, so cloning directly into a directory named `avr` ensures the path correctly ends up as `hardware/bareconductive/avr/boards.txt`.*

**Option B: ZIP Download**
1. Download the repository: [Bare Conductive Arduino Core](https://github.com/BareConductive/bare-conductive-arduino) (Click the green **Code** button and select **Download ZIP**).
2. Inside your `hardware` folder, create a new folder named `bareconductive`.
3. Extract the downloaded ZIP into this folder and rename the extracted folder from `bare-conductive-arduino-master` to `avr`.

Restart the Arduino IDE. You should now see **Bare Conductive Touch Board** listed under **Tools > Board**.

## Step 2: Install the MPR121 Library

The Touch Board relies on the MPR121 chip for capacitive sensing. 

**Option A: Git Clone**
Open your terminal, navigate to your Sketchbook's `libraries` folder, and clone the main branch:
```bash
git clone https://github.com/BareConductive/mpr121.git
```

**Option B: ZIP Download**
1. Download the library: [MPR121 Library](https://github.com/BareConductive/mpr121) (Click **Code > Download ZIP**).
2. In the Arduino IDE, go to **Sketch > Include Library > Add .ZIP Library...**
3. Select the downloaded ZIP file. The IDE will automatically unpack and install it.

## Step 3: Run the HID Keyboard Example

This example turns your Touch Board into a USB keyboard, allowing you to trigger native keystrokes on your computer by touching the physical electrodes.

1. Get the HID Keyboard project to your local machine:
   * **Via Git:** Run `git clone https://github.com/BareConductive/hid-keyboard.git` in your preferred project directory.
   * **Via ZIP:** Download from the [HID Keyboard GitHub Page](https://github.com/BareConductive/hid-keyboard) and extract the folder.
2. Open the `.ino` sketch file in the Arduino IDE.
3. Go to **Tools > Board** and select **Bare Conductive Touch Board**.
4. Go to **Tools > Port** and select the USB port your board is connected to.
5. Click the **Upload** button (the right-pointing arrow at the top left).

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

Once uploaded, touching the twelve electrodes on the board will send the corresponding mapped keystrokes directly to your computer.
