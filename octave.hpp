#pragma once

#include "button.hpp"

class Octave {
public:
  Octave(uint8_t decreaseOctaveButtonPin,
         uint8_t increaseOctaveButtonPin);

  // Update current octave each main loop tick
  void OnUpdate();

  [[nodiscard]] int GetOctave();

private:
  void DecreaseOctave();
  void IncreaseOctave();

  int m_CurrentOctave;
  Button m_DecreaseOctaveButton;
  Button m_IncreaseOctaveButton;
};