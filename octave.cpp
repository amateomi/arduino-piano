#include "octave.hpp"

#include <Arduino.h>

Octave::Octave(uint8_t decreaseOctaveButtonPin,
               uint8_t increaseOctaveButtonPin)
  : m_DecreaseOctaveButton{ decreaseOctaveButtonPin, INPUT_PULLUP },
    m_IncreaseOctaveButton{ increaseOctaveButtonPin, INPUT_PULLUP } {}

void Octave::OnUpdate() {
  if (const auto event = m_DecreaseOctaveButton.OnUpdate();
      event == Button::Event::PRESS) {
    DecreaseOctave();
  }
  if (const auto event = m_IncreaseOctaveButton.OnUpdate();
      event == Button::Event::PRESS) {
    IncreaseOctave();
  }
}

int Octave::GetOctave() const {
  return m_CurrentOctave;
}

void Octave::DecreaseOctave() {
  if (m_CurrentOctave != LOWEST_OCTAVE) {
    --m_CurrentOctave;
  }
}

void Octave::IncreaseOctave() {
  if (m_CurrentOctave != HIGHEST_OCTAVE) {
    ++m_CurrentOctave;
  }
}