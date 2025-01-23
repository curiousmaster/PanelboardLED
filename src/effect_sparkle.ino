#include "effects.h"
#include "utils.h"

/**
 * sparkleStep()
 * Creates a sparkle effect where random LEDs light up briefly.
 *
 * @param strip The NeoPixel strip object.
 * @param color The color of the sparkles.
 */
void sparkleStep(Adafruit_NeoPixel& strip, uint32_t color) {
    static unsigned long lastUpdate = 0;
    const unsigned long interval = 100;  // Speed of the sparkle effect

    if (millis() - lastUpdate >= interval) {
        lastUpdate = millis();

        // Turn off all LEDs
        strip.clear();

        // Randomly light up a few LEDs
        for (int i = 0; i < strip.numPixels() / 5; i++) { // Light up 20% of LEDs
            int randomLED = random(0, strip.numPixels());
            strip.setPixelColor(randomLED, color);
        }

        strip.show();
    }
}