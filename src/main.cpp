#include <Arduino.h>
#include <time.h>

#define LED D1
#define SYNC_PIN A0

#define MULTIPLEXER_BITS 4

#define MAJOR_COUNT_TO 4
#define MINOR_COUNT_TO 5

const unsigned long default_min_time_switch = 100000000 / 12000;
unsigned long actual_min_time_switch = default_min_time_switch;

const uint8_t MULTIPLEXER_PINS_MAJOR[MULTIPLEXER_BITS] = {D0, D1, D2, D3};
const uint8_t MULTIPLEXER_PINS_MINOR[MULTIPLEXER_BITS] = {D7, D6, D5, D4};

bool led_state = false;

// Major is updated every cycle of minor.

byte current_major_state = 0;
byte current_minor_state = 0;

unsigned long prev_micros = 0;

void incrementOutputs(void);

void setup() {
  Serial.begin(74880);
  Serial.println("Booting");
  // Declare Pin Modes
  for (int i = 0; i < 4; i++) {
    pinMode(MULTIPLEXER_PINS_MAJOR[i], OUTPUT);
    pinMode(MULTIPLEXER_PINS_MINOR[i], OUTPUT);
    digitalWrite(MULTIPLEXER_PINS_MAJOR[i], LOW);
    digitalWrite(MULTIPLEXER_PINS_MINOR[i], LOW);
  }

  pinMode(SYNC_PIN, OUTPUT);
}

void loop() {
  unsigned long delta_micros = micros() - prev_micros;
  if (delta_micros >= actual_min_time_switch) {
    incrementOutputs();
    //
    actual_min_time_switch = min(2 * default_min_time_switch - delta_micros,
                                 default_min_time_switch);
    prev_micros = micros();
  }
}

void multiplexerWriteByte(const uint8_t PINS[4], byte byte_to_write) {
  for (int i = 0; i < MULTIPLEXER_BITS; i++) {
    digitalWrite(PINS[i], bitRead(byte_to_write, i));
  }
}

void incrementOutputs() {
  current_minor_state++;
  if (current_minor_state >= MINOR_COUNT_TO) {

    current_major_state++;

    if (current_major_state > MAJOR_COUNT_TO) {
      current_major_state = 0;
      current_minor_state = 0;
      digitalWrite(SYNC_PIN, LOW);

    } else if (current_major_state == MAJOR_COUNT_TO) {
      digitalWrite(SYNC_PIN, HIGH);
    } else {
      current_minor_state = 0;
    }
  }
  if (current_major_state != MAJOR_COUNT_TO) {
    multiplexerWriteByte(MULTIPLEXER_PINS_MINOR, current_minor_state);
    multiplexerWriteByte(MULTIPLEXER_PINS_MAJOR, current_major_state);
  }

  // Serial.println("\n");
  // Serial.println(current_major_state);
  // Serial.println(current_minor_state);
}
