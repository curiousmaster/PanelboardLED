#ifndef UTILS_H
#define UTILS_H

#include <Adafruit_NeoPixel.h>
#include "config.h"

extern int effectStep;

// Effect function declarations
void solidColorStep(Adafruit_NeoPixel& strip, uint32_t color);
void rainbowStep(Adafruit_NeoPixel& strip);
void knightRiderStep(Adafruit_NeoPixel& strip, uint32_t color);
void theaterChaseStep(Adafruit_NeoPixel& strip, uint32_t color);
void meteorEffectStep(Adafruit_NeoPixel& strip, uint32_t color, int decay);
void fireFlickerStep(Adafruit_NeoPixel& strip);
void cometTrailStep(Adafruit_NeoPixel& strip, uint32_t color);
void sparkleStep(Adafruit_NeoPixel& strip, uint32_t color);

// Utility function declarations
void clearStrip(Adafruit_NeoPixel& strip);
void setBrightness(Adafruit_NeoPixel& strip, uint8_t brightness);

// Main control function declarations
void handleButton();
void handleSerialInput();
void showStatus();
void runEffect();
void saveDefaultEffect();
void nextEffect();
void prevEffect();
void showEffect(int effectIndex);

#endif // UTILS_H
