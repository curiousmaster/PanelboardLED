#ifndef CONFIG_H
#define CONFIG_H

// Pin definitions
#define LED_PIN 6       // Data pin for WS2812B LED strip
#define BUTTON_PIN 2    // Pin connected to the push button
#define ONBOARD_LED 13  // Onboard LED pin

// LED configuration
#define NUM_LEDS 114    // Number of LEDs in the strip

// Effect intervals (in milliseconds)
#define INTERVAL_SOLIDCOLOR   500  // Interval for solid color effect
#define INTERVAL_KNIGHTRIDER   75  // Interval for Knight Rider effect
#define INTERVAL_RAINBOW       20  // Interval for Rainbow effect
#define INTERVAL_METEOR        50  // Interval for Meteor effect
#define INTERVAL_COMET         75  // Interval for Comet effect
#define INTERVAL_SPARKLE      100  // Interval for Sparkle effect
#define INTERVAL_THEATERCHASE 100  // Interval for Theater Chase effect
#define INTERVAL_FLICKER       50  // Interval for Fire Flicker effect

// Other configurations
#define NUM_EFFECTS 13   // Total number of effects available

#endif // CONFIG_H
