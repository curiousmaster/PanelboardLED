#include "effects.h"
#include "utils.h"

/**
 * fireFlickerStep()
 * Simulates a fire flickering effect by randomly varying brightness and color.
 *
 * @param strip The NeoPixel strip object.
 */
void fireFlickerStep(Adafruit_NeoPixel& strip) {
    static unsigned long lastUpdate = 0;
    const unsigned long interval = 50;  // Speed of the flickering effect

    if (millis() - lastUpdate >= interval) {
        lastUpdate = millis();

        for (uint16_t i = 0; i < strip.numPixels(); i++) {
            // Generate random brightness values for red, green, and blue channels
            uint8_t r = 255; // Full intensity for red
            uint8_t g = random(50, 150); // Random intensity for green (simulate heat)
            uint8_t b = random(0, 50); // Random intensity for blue (low intensity to simulate flame)

            strip.setPixelColor(i, strip.Color(r, g, b));
        }
        strip.show();
    }
}
