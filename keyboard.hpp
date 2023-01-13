#pragma once

#include "note.hpp"
#include "note-calculator.hpp"
#include "octave.hpp"

class Keyboard {
public:
  Keyboard(Resistors,
           uint8_t analogPin,
           uint8_t decreaseOctaveButtonPin,
           uint8_t increaseOctaveButtonPin);

  // Manage keyboard analog input and convert it into note
  void OnUpdate();

  // Return current note
  [[nodiscard]] Note GetNote() const;

  // Return current octave in range {1..7}
  // where default (start value) is 4 (middle octave)
  [[nodiscard]] int GetOctave() const;

private:
  const uint8_t ANALOG_PIN;
  Note m_CurrentNote{ Note::NONE };
  const NoteCalculator NOTE_CALCULATOR;
  Octave m_Octave;
};