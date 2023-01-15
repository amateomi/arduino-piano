#pragma once

#include "note.hpp"
#include "button.hpp"

class Octave {
public:
  static constexpr auto LOWEST_OCTAVE = 1;
  static constexpr auto MIDDLE_OCTAVE = 4;
  static constexpr auto HIGHEST_OCTAVE = 7;

  Octave(uint8_t decreaseOctaveButtonPin,
         uint8_t increaseOctaveButtonPin)
    : m_DecreaseOctaveButton{ decreaseOctaveButtonPin, INPUT_PULLUP },
      m_IncreaseOctaveButton{ increaseOctaveButtonPin, INPUT_PULLUP } {}

  // Update current octave each main loop tick
  void OnUpdate() {
    if (const auto event = m_DecreaseOctaveButton.OnUpdate();
        event == Button::Event::PRESS) {
      DecreaseOctave();
    }
    if (const auto event = m_IncreaseOctaveButton.OnUpdate();
        event == Button::Event::PRESS) {
      IncreaseOctave();
    }
  }

  // Return current octave in range {1..7}
  // where default (start value) is 4 (middle octave)
  [[nodiscard]] int GetOctave() const {
    return m_CurrentOctave;
  }

private:
  void DecreaseOctave() {
    if (m_CurrentOctave != LOWEST_OCTAVE) {
      --m_CurrentOctave;
    }
  }
  void IncreaseOctave() {
    if (m_CurrentOctave != HIGHEST_OCTAVE) {
      ++m_CurrentOctave;
    }
  }

  int m_CurrentOctave{ MIDDLE_OCTAVE };
  Button m_DecreaseOctaveButton;
  Button m_IncreaseOctaveButton;
};