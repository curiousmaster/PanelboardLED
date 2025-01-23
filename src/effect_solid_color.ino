#include "effects.h"
#include "utils.h"

/**
 * solidColorStep()
 * Displays a static solid color across all LEDs on the strip.
 *
 * @param strip The NeoPixel strip object.
 * @param color The color to display.
 */
void solidColorStep(Adafruit_NeoPixel& strip, uint32_t color) {
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color);
    }
    strip.show();
}
