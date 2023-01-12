#include "button.hpp"
#include "octave.hpp"

constexpr auto LOWEST_OCTAVE = 1;
constexpr auto MIDDLE_OCTAVE = 4;
constexpr auto HIGHEST_OCTAVE = 7;

Octave::Octave(uint8_t decreaseOctaveButtonPin,
               uint8_t increaseOctaveButtonPin)
  : m_CurrentOctave{ MIDDLE_OCTAVE },
    m_DecreaseOctaveButton{ decreaseOctaveButtonPin, INPUT_PULLUP },
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