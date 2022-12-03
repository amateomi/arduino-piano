#include "sound.hpp"
#include "buzzer.hpp"

#include <Arduino.h>

#include "utility.hpp"

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

void Buzzer::play(Sound sound) const {
  play(sound.frequency());
  delay(sound.duration());
}

void Buzzer::playAlarm() const {
  Sound alarm;
  alarm.setFrequency(1337);
  alarm.setDuration(2000);  //< 2 seconds
  play(alarm);
}