#include <Adafruit_NeoPixel.h>
#include "config.h"
#include "effects.h"
#include "utils.h"
#include <EEPROM.h>

int currentEffect = 0;

// Global variables
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
//int currentEffect = 0;
int effectStep = 0;  // Initialize effectStep

void setup() {
    Serial.begin(9600);

    pinMode(BUTTON_PIN, INPUT_PULLUP); // Enable internal pull-up resistor on pin 2
    
    strip.begin();
    strip.show();
    currentEffect = EEPROM.read(0);
    Serial.println("Initiating...");

    delay(2000);

    showStatus();
}

void loop() {
    handleButton();
    handleSerialInput();
    runEffect();
}