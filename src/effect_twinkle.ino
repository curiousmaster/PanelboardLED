#include "effects.h"
#include "utils.h"

void twinkleEffect(Adafruit_NeoPixel& strip, uint32_t color) {
    static unsigned long lastUpdate = 0;
    const unsigned long interval = 50;  // Speed of twinkling
    static int twinkleStates[NUM_LEDS] = {0}; // Brightness states for each LED

    if (millis() - lastUpdate >= interval) {
        lastUpdate = millis();

        for (int i = 0; i < strip.numPixels(); i++) {
            if (random(0, 100) < 10) { // 10% chance to start twinkling
                twinkleStates[i] = random(50, 255); // Random brightness
            }

            uint8_t brightness = twinkleStates[i];
            strip.setPixelColor(i, strip.Color((brightness * ((color >> 16) & 0xFF)) / 255,
                                               (brightness * ((color >> 8) & 0xFF)) / 255,
                                               (brightness * (color & 0xFF)) / 255));
            twinkleStates[i] = max(0, twinkleStates[i] - 10); // Dim gradually
        }
        strip.show();
    }
}
