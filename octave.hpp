#pragma once

#include "button.hpp"

class Octave {
public:
  static constexpr auto LOWEST_OCTAVE = 1;
  static constexpr auto MIDDLE_OCTAVE = 4;
  static constexpr auto HIGHEST_OCTAVE = 7;

  Octave(uint8_t decreaseOctaveButtonPin,
         uint8_t increaseOctaveButtonPin);

  // Update current octave each main loop tick
  void OnUpdate();

  // Return current octave in range {1..7}
  // where default (start value) is 4 (middle octave)
  [[nodiscard]] int GetOctave() const;

private:
  void DecreaseOctave();
  void IncreaseOctave();

  int m_CurrentOctave{ MIDDLE_OCTAVE };
  Button m_DecreaseOctaveButton;
  Button m_IncreaseOctaveButton;
};