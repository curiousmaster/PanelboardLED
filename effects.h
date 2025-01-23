#ifndef EFFECTS_H
#define EFFECTS_H

#include <Adafruit_NeoPixel.h>

// Function declarations for effects
void solidColorStep(Adafruit_NeoPixel& strip, uint32_t color);
void rainbowStep(Adafruit_NeoPixel& strip);
void knightRiderStep(Adafruit_NeoPixel& strip, uint32_t color);
void theaterChaseStep(Adafruit_NeoPixel& strip, uint32_t color);
void meteorEffectStep(Adafruit_NeoPixel& strip, uint32_t color, int decay);
void fireFlickerStep(Adafruit_NeoPixel& strip);
void cometTrailStep(Adafruit_NeoPixel& strip, uint32_t color);
void sparkleStep(Adafruit_NeoPixel& strip, uint32_t color);
void twinkleEffect(Adafruit_NeoPixel& strip, uint32_t color);
void waveEffect(Adafruit_NeoPixel& strip, uint32_t color);
void colorPulseEffect(Adafruit_NeoPixel& strip, uint32_t color);
void fireworksEffect(Adafruit_NeoPixel& strip, uint32_t color);
void rainbowChaseEffect(Adafruit_NeoPixel& strip);

#endif // EFFECTS_H