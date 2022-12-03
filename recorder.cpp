#include "recorder.hpp"

#include <Arduino.h>

#include "utility.hpp"
#include "sound.hpp"

Recorder::Recorder() {
  pinMode(PIN, INPUT_PULLUP);
  LOG("Recorder: Created and attached to pin=%i", PIN);
}

void Recorder::updateRecordingState(const Buzzer& buzzer, unsigned int frequency) {
  PUSH_BUTTON_HANDLER(PIN, m_isButtonPressed, pressCallback());
  if (m_isRecording && !m_wasOutOfBoundWriteAttempt) {
    if (!appendMelodySound(frequency))
      buzzer.playAlarm();
  }
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
    soundPool[m_nextSoundIndex - 1].setAsSeparator();
  LOG("Recorder: End recording, next sound index=%i", m_nextSoundIndex);
}

bool Recorder::appendMelodySound(unsigned int frequency) {
  if (m_nextSoundIndex == POOL_CAPACITY) {
    m_wasOutOfBoundWriteAttempt = true;
    soundPool[m_nextSoundIndex - 1].setAsSeparator();
    LOG("Recorder: Out of bound write attempt");
    return false;
  }

  if (m_nextSoundIndex == 0 || soundPool[m_nextSoundIndex - 1].isSeparator()) {
    if (frequency != 0) {
      soundPool[m_nextSoundIndex].setFrequency(frequency);
      soundPool[m_nextSoundIndex].setDuration(millis());
      ++m_nextSoundIndex;
    }
  } else if (soundPool[m_nextSoundIndex - 1].frequency() != frequency) {
    if (const unsigned long duration = millis() - soundPool[m_nextSoundIndex - 1].duration();
        duration > 0) {
      soundPool[m_nextSoundIndex - 1].setDuration(duration);

      LOG("Recorder: New sound={ frequency=%u, duration=%lu }",
          soundPool[m_nextSoundIndex - 1].frequency(),
          soundPool[m_nextSoundIndex - 1].duration());

      soundPool[m_nextSoundIndex].setFrequency(frequency);
      soundPool[m_nextSoundIndex].setDuration(millis());
      ++m_nextSoundIndex;
    }
  }

  return true;
}