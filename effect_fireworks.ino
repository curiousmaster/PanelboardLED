#include "effects.h"
#include "utils.h"

void fireworksEffect(Adafruit_NeoPixel& strip) {
    static unsigned long lastUpdate = 0;
    const unsigned long interval = 30;
    static int fireworks[NUM_LEDS] = {0};

    if (millis() - lastUpdate >= interval) {
        lastUpdate = millis();

        for (uint16_t i = 0; i < strip.numPixels(); i++) {
            if (random(0, 100) < 5) { // 5% chance of a new firework
                fireworks[i] = 255;
            }

            uint8_t brightness = fireworks[i];
            strip.setPixelColor(i, strip.Color(brightness, brightness / 2, 0)); // Firework color (yellowish)
            fireworks[i] = max(0, fireworks[i] - 15); // Fade out
        }
        strip.show();
    }
}

