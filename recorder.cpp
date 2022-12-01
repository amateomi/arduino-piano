#include "recorder.hpp"

#include <Arduino.h>

#include "utility.hpp"
#include "sound.hpp"

Recorder::Recorder() {
  pinMode(PIN, INPUT_PULLUP);
  LOG("Recorder: Created");
}

void Recorder::updateRecordingState(unsigned int frequency) {
  PUSH_BUTTON_HANDLER(PIN, m_isButtonPressed, pressCallback(), nullptr);
  if (m_isRecording)
    appendMelodySound(frequency);
}

void Recorder::pressCallback() {
  m_isRecording = !m_isRecording;
  if (m_isRecording)
    beginMelody();
  else
    endMelody();
}

void Recorder::beginMelody() {
  Sound::poolWrite(m_index).setAsSeparator();
  ++m_index;
  LOG("Recorder: Begin");
}

void Recorder::endMelody() const {
  Sound::poolWrite(m_index - 1).setAsSeparator();
  LOG("Recorder: End");
}

void Recorder::appendMelodySound(unsigned int frequency) {
  if (Sound::poolRead(m_index - 1).isSeparator()) {
    if (frequency != 0) {
      Sound::poolWrite(m_index).setFrequency(frequency);
      Sound::poolWrite(m_index).setDuration(millis());
      ++m_index;
    }
  } else if (Sound::poolRead(m_index - 1).frequency() != frequency) {
    const unsigned long duration = millis() - Sound::poolRead(m_index - 1).duration();
    Sound::poolWrite(m_index - 1).setDuration(duration);

    LOG("Recorder: New sound={ frequency=%u, duration=%lu }",
        Sound::poolRead(m_index - 1).frequency(),
        Sound::poolRead(m_index - 1).duration());

    Sound::poolWrite(m_index).setFrequency(frequency);
    Sound::poolWrite(m_index).setDuration(millis());
    ++m_index;
  }
}