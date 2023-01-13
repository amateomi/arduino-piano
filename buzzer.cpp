#include "buzzer.hpp"

#include "logger.hpp"

Buzzer::Buzzer(uint8_t pin)
  : PIN{ pin } {
  pinMode(PIN, OUTPUT);

  log("Buzzer created");
}

void Buzzer::Play(Note note, int octave) {
  if (note != m_LastPlayedNote || octave != m_LastPlayedOctave) {
    const auto frequency = MatchOctaveNoteWithFrequency(note, octave);
    frequency ? tone(PIN, frequency) : noTone(PIN);

    m_LastPlayedNote = note;
    m_LastPlayedOctave = octave;

    log("Buzzer::Play frequency=%u (octave=%i)", frequency, octave);
  }
}

unsigned int Buzzer::MatchOctaveNoteWithFrequency(Note note, int octave) {
  const auto frequency = static_cast<unsigned int>(note);
  octave -= Octave::MIDDLE_OCTAVE;
  return (octave < 0) ? frequency >> abs(octave) : frequency << octave;
}