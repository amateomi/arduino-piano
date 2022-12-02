#include "recorder.hpp"

#include <Arduino.h>

#include "utility.hpp"
#include "sound.hpp"
#include "buzzer.hpp"

Recorder& Recorder::get() {
  static Recorder instance;
  return instance;
}

Recorder::Recorder() {
  pinMode(PIN, INPUT_PULLUP);
  LOG("Recorder: Created and attached to pin=%i", PIN);
}

void Recorder::updateRecordingState(unsigned int frequency) {
  PUSH_BUTTON_HANDLER(PIN, m_isButtonPressed, pressCallback());
  if (m_isRecording && !m_wasOutOfBoundWriteAttempt)
    appendMelodySound(frequency);
}

void Recorder::pressCallback() {
  m_isRecording = !m_isRecording;
  if (!m_wasOutOfBoundWriteAttempt) {
    if (m_isRecording)
      beginMelody();
    else
      endMelody();
  }
}

void Recorder::beginMelody() const {
  LOG("Recorder: Begin recording, next sound index=%i", m_nextSoundIndex);
}

void Recorder::endMelody() const {
  if (m_nextSoundIndex != 0)
    SoundPool::get()[m_nextSoundIndex - 1].setAsSeparator();
  LOG("Recorder: End recording, next sound index=%i", m_nextSoundIndex);
}

void Recorder::appendMelodySound(unsigned int frequency) {
  if (m_nextSoundIndex == SoundPool::CAPACITY) {
    m_wasOutOfBoundWriteAttempt = true;
    LOG("Recorder: Was out of bound write attempt");
    Buzzer::get().play(1337);
    delay(2000);
    return;
  }
  
  if (m_nextSoundIndex == 0 || SoundPool::get()[m_nextSoundIndex - 1].isSeparator()) {
    if (frequency != 0) {
      SoundPool::get()[m_nextSoundIndex].setFrequency(frequency);
      SoundPool::get()[m_nextSoundIndex].setDuration(millis());
      ++m_nextSoundIndex;
    }
  } else if (SoundPool::get()[m_nextSoundIndex - 1].frequency() != frequency) {
    const unsigned long duration = millis() - SoundPool::get()[m_nextSoundIndex - 1].duration();
    SoundPool::get()[m_nextSoundIndex - 1].setDuration(duration);

    LOG("Recorder: New sound={ frequency=%u, duration=%lu }",
        SoundPool::get()[m_nextSoundIndex - 1].frequency(),
        SoundPool::get()[m_nextSoundIndex - 1].duration());

    SoundPool::get()[m_nextSoundIndex].setFrequency(frequency);
    SoundPool::get()[m_nextSoundIndex].setDuration(millis());
    ++m_nextSoundIndex;
  }
}