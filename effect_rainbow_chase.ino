#include "effects.h"
#include "utils.h"

void rainbowChaseEffect(Adafruit_NeoPixel& strip) {
    static unsigned long lastUpdate = 0;
    const unsigned long interval = 50;
    static int chaseOffset = 0;

    if (millis() - lastUpdate >= interval) {
        lastUpdate = millis();

        for (uint16_t i = 0; i < strip.numPixels(); i++) {
            int hue = (i * 65536L / strip.numPixels()) + chaseOffset * 256;
            strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(hue)));
        }
        strip.show();
        chaseOffset = (chaseOffset + 1) % 256; // Move the chase
    }
}