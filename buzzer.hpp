#pragma once

#include <stdint.h>

#include "note.hpp"
#include "octave.hpp"

class Buzzer {
public:
  explicit Buzzer(uint8_t pin);

  void Play(Note, int octave);

private:
  [[nodiscard]] unsigned int MatchOctaveNoteWithFrequency(Note, int octave);

  const uint8_t PIN;
  Note m_LastPlayedNote{Note::NONE};
  int m_LastPlayedOctave{Octave::MIDDLE_OCTAVE};
};