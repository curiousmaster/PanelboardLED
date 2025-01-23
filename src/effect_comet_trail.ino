#include "effects.h"
#include "utils.h"

/**
 * cometTrailStep()
 * Simulates a comet with a fading trail.
 *
 * @param strip The NeoPixel strip object.
 * @param color The color of the comet.
 */
void cometTrailStep(Adafruit_NeoPixel& strip, uint32_t color) {
    static int head = 0; // Current position of the comet
    static unsigned long lastUpdate = 0;
    const unsigned long interval = 75;  // Speed of the comet

    if (millis() - lastUpdate >= interval) {
        lastUpdate = millis();

        // Fade all LEDs slightly
        for (int i = 0; i < strip.numPixels(); i++) {
            uint32_t currentColor = strip.getPixelColor(i);
            uint8_t r = (currentColor >> 16) & 0xFF;
            uint8_t g = (currentColor >> 8) & 0xFF;
            uint8_t b = currentColor & 0xFF;

            r = (r > 10) ? r - 10 : 0;
            g = (g > 10) ? g - 10 : 0;
            b = (b > 10) ? b - 10 : 0;

            strip.setPixelColor(i, r, g, b);
        }

        // Set the comet's head to full brightness
        strip.setPixelColor(head, color);
        strip.show();

        // Move the comet's head
        head = (head + 1) % strip.numPixels();
    }
}
