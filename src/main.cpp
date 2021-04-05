#include <Arduino.h>

#define LED D1
#define INTERUPT_PIN 15

#define MULTIPLEXER_BITS 4

const uint8_t MULTIPLEXER_PINS_MAJOR [MULTIPLEXER_BITS] = {D0, D1, D2, D3};
const uint8_t MULTIPLEXER_PINS_MINOR [MULTIPLEXER_BITS] = {D7, D6, D5, D4};

bool led_state = false;
byte current_major_state = 0;
byte current_minor_state = 0;

void multiplexerWriteByte( const uint8_t PINS [4] , byte byte_to_write) {
  for (int i = 0; i < MULTIPLEXER_BITS; i++) {
    digitalWrite(PINS[i],bitRead(byte_to_write,i));
  }
}

// ICACHE_RAM_ATTR is intertup shit, don't worry about it
ICACHE_RAM_ATTR void clock_interupt() {
  current_minor_state++;
  if (current_minor_state >= 16) {
    current_minor_state = 0;
    current_major_state++;
    if (current_major_state >= 16) {
      current_major_state = 0;
    }
  }
  multiplexerWriteByte(MULTIPLEXER_PINS_MINOR,current_minor_state);
  multiplexerWriteByte(MULTIPLEXER_PINS_MAJOR,current_major_state);
  Serial.println("\n");
  Serial.println(current_major_state);
  Serial.println(current_minor_state);
}

void setup() {
  Serial.begin(74880);
  Serial.println("Booting");
  // Declare Pin Modes
  for (int i = 0; i < 4; i++) {
    pinMode(MULTIPLEXER_PINS_MAJOR[i], OUTPUT);
    pinMode(MULTIPLEXER_PINS_MINOR[i], OUTPUT);
    digitalWrite(MULTIPLEXER_PINS_MAJOR[i],LOW);
    digitalWrite(MULTIPLEXER_PINS_MINOR[i],LOW);
  }
  pinMode(INTERUPT_PIN, INPUT);

  // Setup Clock Interupt
  attachInterrupt(digitalPinToInterrupt(INTERUPT_PIN), clock_interupt, RISING);
  Serial.println("Boot Complete");
}

void loop() {
}

