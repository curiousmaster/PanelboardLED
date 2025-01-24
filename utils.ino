#include "config.h"
#include "utils.h"
#include <EEPROM.h>

// External global variables
extern Adafruit_NeoPixel strip;
extern int currentEffect;
extern int effectStep;
static char* lineThick = "======================================================";
static char* lineThin  = "------------------------------------------------------";

struct Effect {
    const char* name; // Name of the effect
    void (*function)(Adafruit_NeoPixel&); // Function pointer for the effect
};

Effect effects[] = {
    {"Solid Color",   [](Adafruit_NeoPixel& strip) { solidColorStep(strip, strip.Color(255, 0, 0)); }},
    {"Rainbow",       rainbowStep},
    {"Knight Rider",  [](Adafruit_NeoPixel& strip) { knightRiderStep(strip, strip.Color(255, 0, 0)); }},
    {"Theater Chase", [](Adafruit_NeoPixel& strip) { theaterChaseStep(strip, strip.Color(255, 255, 0)); }},
    {"Meteor Effect", [](Adafruit_NeoPixel& strip) { meteorEffectStep(strip, strip.Color(0, 0, 255), 20); }},
    {"Fire Flicker",  [](Adafruit_NeoPixel& strip) { fireFlickerStep(strip); }},
    {"Comet Trail",   [](Adafruit_NeoPixel& strip) { cometTrailStep(strip, strip.Color(0, 255, 255)); }},
    {"Twinkle",       [](Adafruit_NeoPixel& strip) { sparkleStep(strip, strip.Color(255, 255, 255)); }},
    {"Wave",          [](Adafruit_NeoPixel& strip) { sparkleStep(strip, strip.Color(255, 255, 255)); }},
    {"Color Pulse",   [](Adafruit_NeoPixel& strip) { sparkleStep(strip, strip.Color(255, 255, 255)); }},
    {"Fireworks",     [](Adafruit_NeoPixel& strip) { sparkleStep(strip, strip.Color(255, 255, 255)); }},
    {"Rainbow Chase", [](Adafruit_NeoPixel& strip) { sparkleStep(strip, strip.Color(255, 255, 255)); }},
    {"Sparkle",       [](Adafruit_NeoPixel& strip) { sparkleStep(strip, strip.Color(255, 255, 255)); }}
};

const int NUM_EFFECTS = sizeof(effects) / sizeof(effects[0]); // Dynamically calculate the number of effects

void clearStrip(Adafruit_NeoPixel& strip) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) { // Use uint16_t for compatibility
        strip.setPixelColor(i, 0); // Set the pixel color to black
    }
    strip.show(); // Update the strip to turn off all LEDs
}

void setBrightness(Adafruit_NeoPixel& strip, uint8_t brightness) {
    strip.setBrightness(brightness);
    strip.show();
}

void handleButton() {
    static unsigned long buttonPressTime = 0; // Time when the button was pressed
    static bool buttonPressed = false;       // Tracks if the button is currently pressed
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
                Serial.print(F("Short press detected: Switching to the next effect: "));
                Serial.print(currentEffect + 1);
                nextEffect();
            } else {
                // Long press: Save the current effect as default
                Serial.println(F("Long press detected: Saving current effect as default."));
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
            } else if (inputString == "show") {
                showEffectList();
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
    Serial.println(lineThick);
    Serial.println(F("PanelboardLED Status:"));
    Serial.print(F("  Current Effect: "));
    Serial.println(currentEffect);

    Serial.print(F("  Effect Name: "));
    if (currentEffect >= 0 && currentEffect < NUM_EFFECTS) {
        Serial.println(effects[currentEffect].name); // Dynamically fetch the effect name
    } else {
        Serial.println(F("Unknown"));
    }

    Serial.println(F("Commands Available:"));
    Serial.println(F("  next        - Switch to the next effect"));
    Serial.println(F("  prev        - Switch to the previous effect"));

    // Handle dynamic range for set [index]
    Serial.print(F("  set [index] - Switch to a specific effect (0-"));
    Serial.print(NUM_EFFECTS - 1);
    Serial.println(F(")"));

    Serial.println(F("  save        - Save the current effect as default"));
    Serial.println(F("  show        - Show list of available effects"));
    Serial.println(F("  help        - Display this help message"));
    Serial.println(lineThick);
}


void showEffectList() {
    Serial.println(lineThick);
    Serial.print(F("  Current effect: "));
    Serial.print(effects[currentEffect].name); // Dynamically fetch the effect name
    Serial.print(F(" ("));
    Serial.print(currentEffect);
    Serial.println(F(")"));

    Serial.println(lineThin);

    Serial.println(F("Available Effects:"));
    for (int i = 0; i < NUM_EFFECTS; i++) {
        Serial.print(F("  "));
        if (i < 10) { // Add a leading space for single-digit numbers
            Serial.print(F(" "));
        }
        Serial.print(i);                // Print the index
        Serial.print(F(": "));
        Serial.println(effects[i].name); // Print the effect name
    }
    Serial.println(lineThick);
}


void runEffect(int effectIndex) {
    showEffect(effectIndex);
}

void saveDefaultEffect() {
    if (EEPROM.read(0) != currentEffect) {
        EEPROM.write(0, currentEffect);
    }
}

void nextEffect() {
    currentEffect = (currentEffect + 1) % NUM_EFFECTS;
    showEffect(currentEffect);
}

void prevEffect() {
    currentEffect = (currentEffect - 1 + NUM_EFFECTS) % NUM_EFFECTS;
    showEffect(currentEffect);
}

void showEffect(int effectIndex) {
    if (effectIndex < 0 || effectIndex >= NUM_EFFECTS) {
        Serial.println("Invalid effect index.");
        return;
    }

    effects[effectIndex].function(strip); // Call the corresponding effect function
}
