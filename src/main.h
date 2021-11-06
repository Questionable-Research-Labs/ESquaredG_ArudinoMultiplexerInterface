#include <Arduino.h>
#include <time.h>

#define MULTIPLEXER_BITS 4

#define MAJOR_COUNT_TO 4
#define MINOR_COUNT_TO 5

#ifdef ARDUINO_ESP8266_NODEMCU_ESP12E
    #define SYNC_PIN A0

    const uint8_t MULTIPLEXER_PINS_MAJOR[MULTIPLEXER_BITS] = {D0, D1, D2, D3};
    const uint8_t MULTIPLEXER_PINS_MINOR[MULTIPLEXER_BITS] = {D7, D6, D5, D4};
#endif

#ifdef ARDUINO_ARCH_SAM
    #define SYNC_PIN 23

    const uint8_t MULTIPLEXER_PINS_MAJOR[MULTIPLEXER_BITS] = {45, 43, 41, 39}; // Chainey Boi
    const uint8_t MULTIPLEXER_PINS_MINOR[MULTIPLEXER_BITS] = {53, 51, 49, 47}; // Groupey Boi
#endif

#ifdef ARDUINO_RASPBERRY_PI_PICO
    #define SYNC_PIN 16

    const uint8_t MULTIPLEXER_PINS_MAJOR[MULTIPLEXER_BITS] = {2, 3, 4, 5}; // Chainey Boi
    const uint8_t MULTIPLEXER_PINS_MINOR[MULTIPLEXER_BITS] = {6, 7, 8, 9}; // Groupey Boi
#endif