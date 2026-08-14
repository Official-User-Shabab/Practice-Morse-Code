# Arduino Morse Code Practice Trainer

A small Arduino Uno project that turns Morse-code messages into **audio and visual signals** for listening practice.

The Arduino randomly selects a message, converts each letter into Morse code, and transmits it using a buzzer and the built-in LED. The message is then revealed through the Serial Monitor so that I can check whether I decoded it correctly.

This is one of my first projects using **C++ and embedded hardware**, coming primarily from a Python programming background.

## Linux Setup

I developed this project on Linux and encountered a couple of issues when setting up the Arduino IDE and accessing the board over USB.

### 1. Remove `brltty`

On some Debian/Ubuntu-based systems, `brltty` can interfere with Arduino serial-port access. If the Arduino is not appearing correctly in the IDE, removing it may resolve the issue:

```bash
sudo apt remove brltty
```

2. Add the user to dialout

To allow the current user to access serial devices:

```
sudo usermod -aG dialout $USER
```

Log out and back in afterwards for the group change to take effect.

The Arduino can then be checked with:

```
lsusb
```

and the available serial ports can be inspected with:

```
ls /dev/tty*
```

## Demo

The Arduino:

1. Selects a random practice message.
2. Converts each character into Morse code.
3. Plays dots and dashes through a buzzer.
4. Flashes the LED alongside the audio.
5. Reveals the original message through the Serial Monitor.

For example:

```text
HELLO WORLD

.... . .-.. .-.. ---   .-- --- .-. .-.. -..
```

The goal is to listen to the transmission and try to decode the message before looking at the answer.

## Hardware

* Arduino Uno
* Buzzer connected to digital pin 3
* LED using digital pin 13
* USB connection to a computer for the Serial Monitor

## Software

* C++
* Arduino IDE
* Arduino Uno libraries/functions such as `tone()`, `digitalWrite()`, `delay()` and `Serial`

## How It Works

The project uses a lookup table containing the Morse representation of the letters A–Z:

```cpp
const char* morseTable[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};
```

Because the table starts at `A`, the position of a letter can be calculated using:

```cpp
c - 'A'
```

For example:

```text
'A' - 'A' = 0
'B' - 'A' = 1
'C' - 'A' = 2
```

This allows the program to find the Morse representation without needing a long sequence of `if` statements.

### Timing

Morse code relies heavily on timing, so the project defines the duration of each signal:

```cpp
const int dotDuration = 140;
const int dashDuration = 420;
const int symbolPause = 140;
const int letterPause = 420;
const int wordPause = 980;
```

A dash is three times as long as a dot, following the basic timing convention used by Morse code.

The program therefore follows roughly:

```text
DOT
 ↓
pause
 ↓
DOT / DASH
 ↓
pause
 ↓
next letter
 ↓
longer pause
 ↓
next word
```

## Random Message Selection

The program contains ten practice messages:

```text
HELLO WORLD
NEED MORE SPEED
SIGNAL RECEIVED
OVER AND OUT
MISSION COMPLETE
RADIO SILENCE
GOOD MORNING
KEEP IT SECRET
ALL SYSTEMS GO
ROGER THAT
```

A random number is generated when the Arduino starts, and that number is used to select one of the messages.

The program attempts to seed the random-number generator using an analogue reading from an unconnected pin:

```cpp
randomSeed(analogRead(A0));
```

This gives different results between resets rather than repeatedly selecting the same sequence.

## Program Structure

The main flow of the program is:

```text
setup()
  │
  ├── Configure LED and buzzer
  ├── Start Serial communication
  ├── Seed random number generator
  ├── Select random message
  │
  └── playString()
          │
          ├── Read character
          ├── Find Morse representation
          │
          ├── "." → playDot()
          │
          └── "-" → playDash()
```

The `loop()` function is currently empty because the program performs one transmission during `setup()` and waits for the Arduino to be reset before selecting another message.

## What I Learned

This project is particularly useful to me because I have mainly programmed in **Python**, so it gave me an opportunity to start working with C++ and physical hardware.

Concepts I have encountered and am currently learning include

* C++ arrays and pointers
* `const char*` strings
* character manipulation
* indexing arrays
* functions
* `for` loops
* conditional statements
* Arduino digital I/O
* analogue input
* serial communication
* timing and delays
* generating tones
* basic embedded-programming concepts
* debugging behaviour on physical hardware

One thing I found interesting was that the same basic programming concepts I have used in Python behave quite differently when interacting directly with hardware.

## AI-Assisted Development

AI tools were used during the initial development of this project. As I am primarily a Python programmer and relatively new to C++, I have used the project as an opportunity to understand the generated implementation, test it on physical hardware, debug it and extend it myself.

This includes learning concepts such as C-style strings, pointers, arrays, character arithmetic and Arduino-specific hardware functions.

## Future Improvements

There are several directions I would like to take the project.

### Input and interaction

*  Add a physical Morse key/button for entering Morse code
*  Allow the user to answer directly on the Arduino
*  Add LED/buzzer feedback for correct and incorrect answers
*  Add a score system

### Practice modes

*  Add adjustable difficulty
*  Practise individual letters before moving to words
*  Add numbers and punctuation
*  Add random words rather than predefined messages
*  Add timed challenges

### Software improvements

*  Replace blocking `delay()` calls with non-blocking timing using `millis()`
*  Improve the random-message system
*  Separate Morse encoding, transmission and user interaction into clearer components
*  Add unit tests for the Morse encoding logic where practical

### Hardware

*  Add a proper Morse key
*  Add an LCD/OLED display
*  Add buttons for selecting practice modes
*  Make the device portable using a battery

## Why I Built It

I have a long-standing interest in the relationship between software and the underlying hardware that executes it. This project is a small practical step in exploring that relationship.

Morse code is particularly interesting because it reduces communication to a simple encoding system based on timing. Implementing that system on a microcontroller provides a straightforward way to see software controlling a physical device in real time.

This project also gives me a chance to move beyond Python and start developing my understanding of **C++, embedded systems and hardware-software interaction**.

## Status

**Current status:** Working prototype

The current version successfully selects and transmits a random Morse-code message using the Arduino's LED and buzzer.

The next major step is to turn it from a one-way demonstration into an actual **interactive Morse-code trainer**.
