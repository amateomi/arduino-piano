#include "keyboard.hpp"

#include "logger.hpp"

Keyboard::Keyboard(Resistors resistors,
                   uint8_t analogPin,
                   uint8_t decreaseOctaveButtonPin,
                   uint8_t increaseOctaveButtonPin)
  : ANALOG_PIN{ analogPin },
    NOTE_CALCULATOR{ resistors },
    m_Octave{ decreaseOctaveButtonPin, increaseOctaveButtonPin } {
  log("Keyboard created");
}

void Keyboard::OnUpdate() {
  m_Octave.OnUpdate();

  const int voltage = analogRead(ANALOG_PIN);
  m_CurrentNote = NOTE_CALCULATOR.matchVoltageWithNote(voltage);
}

Note Keyboard::GetNote() const {
  return m_CurrentNote;
}

int Keyboard::GetOctave() const {
  return m_Octave.GetOctave();
}