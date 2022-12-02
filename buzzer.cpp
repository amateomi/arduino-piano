#include "buzzer.hpp"

#include <Arduino.h>

#include "utility.hpp"

Buzzer& Buzzer::get() {
  static Buzzer instance;
  return instance;
}

Buzzer::Buzzer() {
  pinMode(PIN, OUTPUT);
  LOG("Buzzer: Created and attached to pin=%i", PIN);
}

void Buzzer::play(unsigned int frequency) const {
  if (frequency == 0) {
    noTone(PIN);
  } else {
    tone(PIN, frequency);
    LOG("Buzzer: playing frequency=%u", frequency);
  }
}