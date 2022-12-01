#include "buzzer.hpp"

#include <Arduino.h>

#include "utility.hpp"

Buzzer::Buzzer() {
  pinMode(PIN, OUTPUT);
  LOG("Buzzer: Created");
}

void Buzzer::play(unsigned int frequency) const {
  if (frequency == 0) {
    noTone(PIN);
  } else {
    tone(PIN, frequency);
    LOG("Buzzer: playing frequency=%u", frequency);
  }
}