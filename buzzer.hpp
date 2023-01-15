#pragma once

#include "note.hpp"
#include "octave.hpp"
#include "melody-storage.hpp"

class Buzzer {
public:
  explicit Buzzer(uint8_t pin)
    : PIN{ pin } {
    pinMode(PIN, OUTPUT);

    log("Buzzer created");
  }

  void Play(Note note, int octave) {
    const auto frequency = MatchNoteWithFrequency(note, octave);
    frequency != 0 ? tone(PIN, frequency) : noTone(PIN);

    const bool isChange = note != m_LastPlayedNote || octave != m_LastPlayedOctave;
    if (isChange) {
      m_LastPlayedNote = note;
      m_LastPlayedOctave = octave;
      log("Buzzer: play frequency=%u (octave=%i)", frequency, octave);
    }
  }

  void Play(const Sound& sound) const {
    sound.Frequency != 0 ? tone(PIN, sound.Frequency) : noTone(PIN);
    delay(sound.DurationMs);
    log("Buzzer: play sound{ frequency=%u, duration=%lums }",
        sound.Frequency, sound.DurationMs);
  }

  void PlayAlarm() const {
    Sound alarm;
    alarm.Frequency = 1337;
    alarm.DurationMs = 1000;
    Play(alarm);
  }

  // Convert note to frequency according to octave
  [[nodiscard]] static unsigned int MatchNoteWithFrequency(Note note, int octave) {
    const auto frequency = static_cast<unsigned int>(note);
    octave -= Octave::MIDDLE_OCTAVE;
    return (octave < 0) ? frequency >> abs(octave) : frequency << octave;
  }

private:
  const uint8_t PIN;
  Note m_LastPlayedNote{ Note::NONE };
  int m_LastPlayedOctave{ Octave::MIDDLE_OCTAVE };
};