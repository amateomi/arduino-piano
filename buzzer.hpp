#pragma once

#include "note.hpp"
#include "octave.hpp"

class Buzzer {
public:
  explicit Buzzer(uint8_t pin)
    : PIN{ pin } {
    pinMode(PIN, OUTPUT);

    log("Buzzer created");
  }

  void Play(Note note, int octave) {
    const bool isChange = note != m_LastPlayedNote || octave != m_LastPlayedOctave;
    if (isChange) {
      const auto frequency = Octave::MatchNoteWithFrequency(note, octave);
      frequency ? tone(PIN, frequency) : noTone(PIN);

      m_LastPlayedNote = note;
      m_LastPlayedOctave = octave;

      log("Buzzer: play frequency=%u (octave=%i)", frequency, octave);
    }
  }

  void PlayAlarm() const {

  }

private:
  const uint8_t PIN;
  Note m_LastPlayedNote{ Note::NONE };
  int m_LastPlayedOctave{ Octave::MIDDLE_OCTAVE };
};