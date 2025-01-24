#include "effects.h"
#include "utils.h"

/**
 * knightRiderStep()
 * Simulates the classic Knight Rider effect with a bouncing light.
 *
 * @param strip The NeoPixel strip object.
 * @param color The color of the bouncing light.
 */
void knightRiderStep(Adafruit_NeoPixel& strip, uint32_t color) {
    static uint16_t position = 0;       // Current position of the light
    static bool direction = true; // Direction of movement (true = forward, false = backward)
    static unsigned long lastUpdate = 0;
    const unsigned long interval = 75;  // Speed of the effect

    if (millis() - lastUpdate >= interval) {
        lastUpdate = millis();

        // Clear the previous LED
        strip.clear();

        // Set the current LED to the desired color
        strip.setPixelColor(position, color);
        strip.show();

        // Update position and direction
        if (direction) {
            position++;
            if (position >= strip.numPixels() - 1) {
                direction = false; // Reverse direction
            }
        } else {
            position--;
            if (position <= 0) {
                direction = true; // Reverse direction
            }
        }
    }
}