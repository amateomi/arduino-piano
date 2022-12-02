#pragma once

#include <Arduino.h>

class Keyboard {
public:
  static Keyboard& get();

  Keyboard(const Keyboard&) = delete;
  Keyboard& operator=(const Keyboard&) = delete;

  void updateCurrentOctave();

  /// Return frequency for Buzzer to play or 0 when none keyboard button are pressed
  [[nodiscard]] unsigned int getNoteFrequency() const;

private:
  Keyboard();
  ~Keyboard() = default;

  void pressLowerCallback();
  void pressUpperCallback();

  [[nodiscard]] static unsigned int mainOctaveVoltageToFrequency(int voltage);
  [[nodiscard]] static constexpr int calculateMainOctaveVoltages(unsigned int noteResistor);

  static constexpr int PIN{ A5 };
  static constexpr int UPPER_OCTAVE_PIN{ 7 };
  static constexpr int LOWER_OCTAVE_PIN{ 8 };

  static constexpr int OCTAVE_NOTES_NUM{ 12 };
  static const int MAIN_OCTAVE_VOLTAGES[OCTAVE_NOTES_NUM];
  static const unsigned int MAIN_OCTAVE_FREQUENCIES[OCTAVE_NOTES_NUM];

  int m_currentOctave{};

  bool m_isLowerPressed{};
  bool m_isUpperPressed{};
};