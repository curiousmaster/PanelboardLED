#include "effects.h"
#include "utils.h"

void waveEffect(Adafruit_NeoPixel& strip, uint32_t color) {
    static unsigned long lastUpdate = 0;
    const unsigned long interval = 30;  // Speed of the wave
    static float waveOffset = 0;

    if (millis() - lastUpdate >= interval) {
        lastUpdate = millis();

        for (int i = 0; i < strip.numPixels(); i++) {
            float brightness = (sin((i + waveOffset) * 0.2) + 1.0) * 127.5; // Sine wave from 0 to 255
            strip.setPixelColor(i, strip.Color((brightness * ((color >> 16) & 0xFF)) / 255,
                                               (brightness * ((color >> 8) & 0xFF)) / 255,
                                               (brightness * (color & 0xFF)) / 255));
        }
        waveOffset += 1; // Move the wave
        if (waveOffset > 1000) waveOffset = 0; // Prevent overflow
        strip.show();
    }
}
