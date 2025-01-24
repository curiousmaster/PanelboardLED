# PanelboardLED

## Overview
**PanelboardLED** is an Arduino-based project designed to control a WS2812B LED strip on a guitar pedalboard, and optionally display the current effect name on an FC-16 LED matrix display. It supports dynamic effect switching via a push button or serial commands. The project leverages advanced effects to create visually stunning LED animations while optimizing for memory usage.

## Features
- **Multiple LED Effects**:
  - Solid Color
  - Rainbow
  - Knight Rider
  - Theater Chase
  - Meteor Effect
  - Fire Flicker
  - Comet Trail
  - Sparkle
  - Twinkle, Wave, Color Pulse, Fireworks, and more (optional).
- **Effect Control**:
  - Short button press: Switch to the next effect.
  - Long button press: Save the current effect as the default.
  - Serial commands: Switch effects or query status.
- **Optional FC-16 LED Matrix Support** (not yet implemented):
  - Displays the current effect name.
  - Scrolling text for long names.
- **Non-blocking Execution**:
  - Smooth animations with minimal impact on other inputs.

## Hardware Requirements
1. **Arduino Board**:
   - Arduino Mega (recommended for larger memory capacity).
2. **WS2812B LED Strip**:
   - Up to 114 LEDs (configurable in `config.h`).
3. **Push Button**:
   - Connected to pin 2.
4. **Optional FC-16 LED Matrix Display**:
   - Controlled via MAX7219.

### Wiring Diagram
| Component         | Arduino Pin |
|-------------------|-------------|
| WS2812B Data Pin  | D6          |
| Push Button       | D2          |
| FC-16 DIN         | D11         |
| FC-16 CS          | D10         |
| FC-16 CLK         | D13         |

## Software Requirements
1. **Arduino IDE**
   - Version 1.8 or higher.
2. **Libraries**
   - [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
   - [LedControl](https://github.com/wayoda/LedControl) or [MD_MAX72XX](https://github.com/MajicDesigns/MD_MAX72XX) (for FC-16 support).

## Installation
1. Clone this repository or download the ZIP file.
   ```bash
   git clone https://github.com/your-repo-url/PanelboardLED.git
   ```
2. Open the `PanelboardLED.ino` file in the Arduino IDE.
3. Install the required libraries via the Arduino Library Manager.
   - Go to `Sketch > Include Library > Manage Libraries`.
   - Search for and install the libraries mentioned above.
4. Configure `config.h` to match your hardware setup:
   ```cpp
   #define NUM_LEDS 114
   #define LED_PIN 6
   #define BUTTON_PIN 2
   ```
5. Upload the code to your Arduino board.

## Usage
### Push Button
- **Short Press**: Switch to the next effect.
- **Long Press (1s or more)**: Save the current effect as default.

### Serial Commands
Open the Serial Monitor in the Arduino IDE and set the baud rate to `9600`. Use the following commands:
- `next`: Switch to the next effect.
- `prev`: Switch to the previous effect.
- `set [index]`: Switch to a specific effect (0-based index).
- `save`: Save the current effect as default in EEPROM.
- `show`: Show available effects.
- `help`: Display the list of valid commands.

### FC-16 LED Matrix Display (Optional)
- Displays the current effect name.
- Automatically updates when the effect changes.
- Long names are scrolled dynamically (when supported).

## Adding New Effects
To add a new effect:
1. Define the effect function in the appropriate file (e.g., `effects.h` or `effects.cpp`).
2. Add the effect name and function pointer to the `effects` array in `utils.cpp`:
   ```cpp
   effects[] = {
       {"New Effect", newEffectFunction},
   };
   ```
3. Ensure the total number of effects is updated dynamically with `NUM_EFFECTS`.

## Troubleshooting
### Common Issues
- **No Serial Output**:
  - Ensure `Serial.begin(9600)` is called in `setup()`.
  - Check the Serial Monitor baud rate is set to `9600`.
- **LEDs Not Lighting Up**:
  - Verify the `LED_PIN` matches your wiring.
  - Check power supply connections to the WS2812B strip.
- **Memory Overflow Errors**:
  - Use `F()` to store static strings in Flash memory.
  - Reduce the number of LEDs or optimize effect logic.

### Debugging Memory
Add the following function to monitor free memory:
```cpp
int freeMemory() {
    extern int __heap_start, *__brkval;
    int v;
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}
```
Print memory usage periodically:
```cpp
Serial.print(F("Free memory: "));
Serial.println(freeMemory());
```

## Contributing
Contributions are welcome! Feel free to submit a pull request or open an issue for suggestions, bug reports, or feature requests.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments
- [Adafruit](https://adafruit.com) for the NeoPixel library.
- [Wayoda](https://github.com/wayoda) for the LedControl library.
- [MajicDesigns](https://github.com/MajicDesigns) for the MD_MAX72XX library.

---
Enjoy your custom LED effects and bring your projects to life! 🚀

