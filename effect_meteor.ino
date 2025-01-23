#include "effects.h"
#include "utils.h"

/**
 * meteorEffectStep()
 * Creates a "meteor" effect with a moving bright head and a fading trail.
 *
 * @param strip The NeoPixel strip object.
 * @param color The color of the meteor.
 * @param decay The rate at which the trail fades (higher values = faster decay).
 */
void meteorEffectStep(Adafruit_NeoPixel& strip, uint32_t color, int decay) {
    static int head = 0; // Current position of the meteor
    static unsigned long lastUpdate = 0;
    const unsigned long interval = 50;  // Speed of the meteor movement

    if (millis() - lastUpdate >= interval) {
        lastUpdate = millis();

        // Fade all LEDs slightly
        for (int i = 0; i < strip.numPixels(); i++) {
            uint32_t currentColor = strip.getPixelColor(i);
            uint8_t r = (currentColor >> 16) & 0xFF;
            uint8_t g = (currentColor >> 8) & 0xFF;
            uint8_t b = currentColor & 0xFF;

            r = (r > decay) ? r - decay : 0;
            g = (g > decay) ? g - decay : 0;
            b = (b > decay) ? b - decay : 0;

            strip.setPixelColor(i, r, g, b);
        }

        // Set the meteor's head to the desired color
        strip.setPixelColor(head, color);
        strip.show();

        // Move the meteor's head
        head = (head + 1) % strip.numPixels();
    }
}
