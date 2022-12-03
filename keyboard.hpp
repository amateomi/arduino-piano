#pragma once

#include <Arduino.h>

class Keyboard {
public:
  Keyboard();

  void updateCurrentOctave();

  /// Return frequency for Buzzer to play or 0 when none keyboard button are pressed
  [[nodiscard]] unsigned int getNoteFrequency() const;

private:
  void pressLowerCallback();
  void pressUpperCallback();

  [[nodiscard]] static unsigned int mainOctaveVoltageToFrequency(int voltage);

  static constexpr int PIN{ A5 };
  static constexpr int UPPER_OCTAVE_PIN{ 7 };
  static constexpr int LOWER_OCTAVE_PIN{ 8 };

  enum NoteFrequency : unsigned int {
    C4 = 262,
    C4_SHARP = 277,
    D4 = 294,
    D4_SHARP = 311,
    E4 = 330,
    F4 = 349,
    F4_SHARP = 370,
    G4 = 392,
    G4_SHARP = 415,
    A4 = 440,
    A4_SHARP = 466,
    B4 = 494,
  };

  static constexpr int OCTAVE_NOTES_NUM{ 12 };
  static const int MAIN_OCTAVE_VOLTAGES[OCTAVE_NOTES_NUM];
  static const NoteFrequency MAIN_OCTAVE_FREQUENCIES[OCTAVE_NOTES_NUM];

  int m_currentOctave{};

  bool m_isLowerPressed{};
  bool m_isUpperPressed{};
};