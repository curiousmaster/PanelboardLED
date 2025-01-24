#include "effects.h"
#include "utils.h"

void colorPulseEffect(Adafruit_NeoPixel& strip, uint32_t color) {
    static unsigned long lastUpdate = 0;
    const unsigned long interval = 20; // Speed of pulsing
    static float brightness = 0;
    static int direction = 1; // 1 = getting brighter, -1 = getting dimmer

    if (millis() - lastUpdate >= interval) {
        lastUpdate = millis();

        brightness += direction * 5;
        if (brightness >= 255 || brightness <= 0) direction *= -1; // Reverse direction

        for (uint16_t i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color((brightness * ((color >> 16) & 0xFF)) / 255,
                                               (brightness * ((color >> 8) & 0xFF)) / 255,
                                               (brightness * (color & 0xFF)) / 255));
        }
        strip.show();
    }
}
