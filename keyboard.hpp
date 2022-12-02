#pragma once

#include <Arduino.h>

class Keyboard {
public:
  Keyboard();

  void updateCurrentOctave();

  /// Return frequency for Buzzer to play or 0 when none keyboard button are pressed
  unsigned int getNoteFrequency() const;

private:
  void pressLowerCallback();
  void pressUpperCallback();

  enum VoltageDividerResistors {
    R0,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
  };

  static int calculateNoteVoltage();
  static unsigned int voltageToFrequency(int voltage);

  static constexpr int PIN{ A5 };
  static constexpr int UPPER_OCTAVE_PIN{ 7 };
  static constexpr int LOWER_OCTAVE_PIN{ 8 };

  static constexpr int OCTAVE_NOTES_NUM{ 12 };
  static const int OCTAVE_VOLTAGES[OCTAVE_NOTES_NUM];
  static const unsigned int OCTAVE_FREQUENCIES[OCTAVE_NOTES_NUM];

  int m_currentOctave{};
  bool m_isLowerPressed{};
  bool m_isUpperPressed{};
};