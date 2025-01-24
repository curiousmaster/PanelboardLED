#include "effects.h"
#include "utils.h"

/**
 * theaterChaseStep()
 * Creates a theater chase effect where groups of LEDs turn on and off in sequence.
 *
 * @param strip The NeoPixel strip object.
 * @param color The color of the chase.
 */
void theaterChaseStep(Adafruit_NeoPixel& strip, uint32_t color) {
    static int step = 0; // Current step in the chase sequence
    static unsigned long lastUpdate = 0;
    const unsigned long interval = 100;  // Speed of the chase effect

    if (millis() - lastUpdate >= interval) {
        lastUpdate = millis();

        // Clear all LEDs
        strip.clear();

        // Light up every third LED based on the step
        for (uint16_t i = step; i < strip.numPixels(); i += 3) {
            strip.setPixelColor(i, color);
        }

        strip.show();

        // Move to the next step
        step = (step + 1) % 3;
    }
}