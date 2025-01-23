#include "config.h"
#include "utils.h"
#include <EEPROM.h>

// External global variables
extern Adafruit_NeoPixel strip;
extern int currentEffect;
extern int effectStep;

void clearStrip(Adafruit_NeoPixel& strip) {
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 0);
    }
    strip.show();
}

void setBrightness(Adafruit_NeoPixel& strip, uint8_t brightness) {
    strip.setBrightness(brightness);
    strip.show();
}

void handleButton() {
    static unsigned long buttonPressTime = 0; // Time when the button was pressed
    static bool buttonPressed = false;       // Tracks if the button is currently pressed
    const unsigned long debounceDelay = 50;  // Debounce time in milliseconds
    const unsigned long longPressDuration = 1000; // Threshold for a long press (ms)

    int buttonState = digitalRead(BUTTON_PIN);
    
    if (buttonState == LOW) { // Button is pressed
        if (!buttonPressed) {
            buttonPressed = true;                  // Mark the button as pressed
            buttonPressTime = millis();            // Record the press time
        }
    } else { // Button is released
        if (buttonPressed) {
            buttonPressed = false; // Reset the button state
            unsigned long pressDuration = millis() - buttonPressTime;

            if (pressDuration < longPressDuration) {
                // Short press: Switch to the next effect
                Serial.println("Short press detected: Switching to the next effect.");
                nextEffect();
            } else {
                // Long press: Save the current effect as default
                Serial.println("Long press detected: Saving current effect as default.");
                saveDefaultEffect();
            }
        }
    }
}


void handleSerialInput() {
    static String inputString = ""; // Holds the incoming command
    while (Serial.available() > 0) {
        char inChar = (char)Serial.read(); // Read the next character
        if (inChar == '\n') { // End of command
            inputString.trim(); // Remove leading/trailing whitespace
            Serial.print("Received command: ");
            Serial.println(inputString);

            if (inputString == "next") {
                nextEffect();
            } else if (inputString == "prev") {
                prevEffect();
            } else if (inputString.startsWith("set")) {
                int index = inputString.substring(4).toInt();
                if (index >= 0 && index < NUM_EFFECTS) {
                    currentEffect = index;
                    showEffect(currentEffect);
                } else {
                    Serial.println("Invalid effect index.");
                }
            } else if (inputString == "save") {
                saveDefaultEffect();
            } else if (inputString == "help") {
                showStatus();
            } else {
                Serial.println("Unknown command.");
            }

            inputString = ""; // Clear the command buffer
        } else {
            inputString += inChar; // Append the character to the command
        }
    }
}


void showStatus() {
    Serial.println("=====================================");
    Serial.println("PanelboardLED Status:");
    Serial.print("  Current Effect: ");
    Serial.println(currentEffect);
    Serial.print("  Effect Name: ");
    switch (currentEffect) {
        case 0: Serial.println("  Solid Color"); break;
        case 1: Serial.println("  Rainbow"); break;
        case 2: Serial.println("  Knight Rider"); break;
        case 3: Serial.println("  Theater Chase"); break;
        case 4: Serial.println("  Meteor Effect"); break;
        case 5: Serial.println("  Fire Flicker"); break;
        case 6: Serial.println("  Comet Trail"); break;
        case 7: Serial.println("  Sparkle"); break;
        case 8: Serial.println("  Twinkle"); break;
        case 9: Serial.println("  Wave"); break;
        case 10: Serial.println(" Color Pulse"); break;
        case 11: Serial.println(" Fireworks"); break;
        case 12: Serial.println(" Rainbow Chase"); break;
        default: Serial.println("  Unknown Effect"); break;
    }
    Serial.println("Commands Available:");
    Serial.println("  next        - Switch to the next effect");
    Serial.println("  prev        - Switch to the previous effect");
    Serial.println("  set [index] - Switch to a specific effect");
    Serial.println("  save        - Save the current effect as default");
    Serial.println("  help        - Display this help message");
    Serial.println("=====================================");
}

void runEffect() {
    switch (currentEffect) {
        case 0: solidColorStep(strip, strip.Color(255, 0, 0)); break;
        case 1: rainbowStep(strip); break;
        case 2: knightRiderStep(strip, strip.Color(255, 0, 0)); break;
        case 3: theaterChaseStep(strip, strip.Color(255, 255, 0)); break;
        case 4: meteorEffectStep(strip, strip.Color(0, 0, 255), 20); break;
        case 5: fireFlickerStep(strip); break;
        case 6: cometTrailStep(strip, strip.Color(0, 255, 255)); break;
        case 7: sparkleStep(strip, strip.Color(255, 255, 255)); break;
        case 8: twinkleEffect(strip, strip.Color(0, 0, 255)); break;
        case 9: waveEffect(strip, strip.Color(0, 0, 255)); break;
        case 10: colorPulseEffect(strip, strip.Color(0, 0, 255)); break;
        case 11: fireworksEffect(strip); break;
        case 12: rainbowChaseEffect(strip); break;
    }
}

void saveDefaultEffect() {
    if (EEPROM.read(0) != currentEffect) {
        EEPROM.write(0, currentEffect);
    }
}

void nextEffect() {
    currentEffect = (currentEffect + 1) % NUM_EFFECTS;
    Serial.print("Switched to next effect: ");
    Serial.println(currentEffect);
    showEffect(currentEffect);
    //showStatus();
}

void prevEffect() {
    currentEffect = (currentEffect - 1 + NUM_EFFECTS) % NUM_EFFECTS;
    Serial.print("Switched to previous effect: ");
    Serial.println(currentEffect);
    showEffect(currentEffect);
}

void showEffect(int effectIndex) {
    effectStep = 0;

    switch (effectIndex) {
        case 0: solidColorStep(strip, strip.Color(255, 0, 0)); break;
        case 1: rainbowStep(strip); break;
        case 2: knightRiderStep(strip, strip.Color(255, 0, 0)); break;
        case 3: theaterChaseStep(strip, strip.Color(255, 255, 0)); break;
        case 4: meteorEffectStep(strip, strip.Color(0, 0, 255), 20); break;
        case 5: fireFlickerStep(strip); break;
        case 6: cometTrailStep(strip, strip.Color(0, 255, 255)); break;
        case 7: sparkleStep(strip, strip.Color(255, 255, 255)); break;
        case 8: twinkleEffect(strip, strip.Color(0, 0, 255)); break;
        case 9: waveEffect(strip, strip.Color(0, 0, 255)); break;
        case 10: colorPulseEffect(strip, strip.Color(0, 0, 255)); break;
        case 11: fireworksEffect(strip); break;
        case 12: rainbowChaseEffect(strip); break;
    }
    //showStatus();
}
