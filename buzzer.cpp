#include "buzzer.hpp"

#include <Arduino.h>

#include "debug.hpp"

Buzzer::Buzzer() {
  pinMode(PIN, OUTPUT);
}

void Buzzer::play(unsigned int frequency) const {
  if (frequency == 0) {
    noTone(PIN);
    LOG("Buzzer: no sound");
  } else {
    tone(PIN, frequency);
    LOG("Buzzer: playing frequency=%u", frequency);
  }
}