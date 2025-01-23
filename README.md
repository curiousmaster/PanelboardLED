# PanelboardLED

A program to control a WS2812B LED strip and mimic the effects on the Arduino's onboard LED. It features multiple customizable effects and supports both button control and serial commands for dynamic effect switching.

---

## Features

- **Non-blocking Execution:** Ensures smooth operation using `millis()`.
- **Effect Control:**
  - Short button press to switch to the next effect.
  - Long button press to save the current effect as default.
  - Serial commands for additional control.
- **Dynamic Effects:**
  - Solid Color
  - Rainbow
  - Knight Rider
  - Theater Chase
  - Meteor Effect
  - Fire Flicker
  - Comet Trail
  - Sparkle
  - ...and more

---

## File Structure

```
PanelboardLED/src
├── main.cpp             # Main program file (setup and loop logic)
├── config.h             # Configuration for pins, constants, etc.
├── utils.h              # Utility functions (e.g., brightness control)
├── effects.h            # Header file for effect declarations
├── effect_solid_color.ino   # Solid color effect implementation
├── effect_rainbow.ino       # Rainbow effect implementation
├── effect_knight_rider.ino  # Knight Rider effect implementation
├── effect_theatre_chase.ino # Theater Chase effect implementation
├── effect_meteor.ino        # Meteor effect implementation
├── effect_fire_flicker.ino  # Fire Flicker effect implementation
├── effect_comet_trail.ino   # Comet Trail effect implementation
├── effect_sparkle.ino       # Sparkle effect implementation
├── README.md                # Documentation
└── Makefile                 # Makefile for building and uploading
```

---

## Hardware Requirements

- **Arduino Uno**
- **WS2812B LED Strip**
- Push Button
- Optional: Resistors and capacitors for signal stability

---

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/your-repo-url/PanelboardLED.git
   ```
2. Install the Adafruit NeoPixel library if not already installed:
   ```bash
   arduino-cli lib install "Adafruit NeoPixel"
   ```
3. Build and upload the program:
   ```bash
   make upload
   ```

---

## Usage

### Button Controls
- **Short Press:** Switch to the next effect.
- **Long Press:** Save the current effect as the default.

### Serial Commands
- `next` - Switch to the next effect.
- `prev` - Switch to the previous effect.
- `save` - Save the current effect as the default.
- `set [index]` - Set a specific effect by index (0-9).
- `help` - Show pin setup.

---

## Effect Descriptions

1. **Solid Color:** Displays a single solid color on all LEDs.
2. **Rainbow:** Cycles through a smooth rainbow gradient.
3. **Knight Rider:** Simulates a bouncing light.
4. **Theater Chase:** Creates a "chasing lights" effect.
5. **Meteor Effect:** Simulates a moving light with a fading tail.
6. **Fire Flicker:** Mimics the flicker of a flame.
7. **Comet Trail:** A single bright light moves with a fading trail.
8. **Sparkle:** Random LEDs light up briefly to simulate sparkles.

---

## Contributing

1. Fork the repository.
2. Create a feature branch:
   ```bash
   git checkout -b feature-branch
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add a new feature"
   ```
4. Push to the branch:
   ```bash
   git push origin feature-branch
   ```
5. Open a pull request.

---

## License

This project is licensed under the MIT License. See `LICENSE` for details.

---

## Author

Curious Master
Date: 2025-01-22
