#pragma once

#include "logger.hpp"
#include "note-calculator.hpp"
#include "octave.hpp"

class Keyboard {
public:
  Keyboard(Resistors resistors,
           uint8_t analogPin,
           uint8_t decreaseOctaveButtonPin,
           uint8_t increaseOctaveButtonPin)
    : ANALOG_PIN{ analogPin },
      NOTE_CALCULATOR{ resistors },
      m_Octave{ decreaseOctaveButtonPin, increaseOctaveButtonPin } {
    log("Keyboard created");
  }

  // Manage keyboard analog input and convert it into note
  void OnUpdate() {
    m_Octave.OnUpdate();

    const int voltage = analogRead(ANALOG_PIN);
    m_CurrentNote = NOTE_CALCULATOR.matchVoltageWithNote(voltage);
  }

  // Return current note
  [[nodiscard]] Note GetNote() const {
    return m_CurrentNote;
  }

  // Return current octave in range {1..7}
  // where default (start value) is 4 (middle octave)
  [[nodiscard]] int GetOctave() const {
    return m_Octave.GetOctave();
  }

private:
  const uint8_t ANALOG_PIN;
  Note m_CurrentNote{ Note::NONE };
  const NoteCalculator NOTE_CALCULATOR;
  Octave m_Octave;
};