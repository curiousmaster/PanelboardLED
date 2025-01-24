#include "effects.h"
#include "utils.h"

/**
 * rainbowStep()
 * Displays a smooth rainbow effect that transitions over time.
 *
 * @param strip The NeoPixel strip object.
 */
void rainbowStep(Adafruit_NeoPixel& strip) {
    static unsigned long lastUpdate = 0;
    static int firstPixelHue = 0; // Starting hue for the rainbow
    const unsigned long interval = 20;  // Speed of the rainbow effect

    if (millis() - lastUpdate >= interval) {
        lastUpdate = millis();

        // Iterate through all pixels to apply a rainbow gradient
        for (uint16_t i = 0; i < strip.numPixels(); i++) {
            int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
            strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
        }
        strip.show();

        // Increment the starting hue for the next frame
        firstPixelHue = (firstPixelHue + 256) % 65536;
    }
}
