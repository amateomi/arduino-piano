#pragma once

#include "notes.hpp"
#include "octave.hpp"

class Keyboard {
public:
  // Resistance of all resistors in the keyboard circuit.
  // R1 should be equal 10kOm.
  // Resistance of R2-R8 should be sorted ascending.
  struct Resistors {
    unsigned long R1, R2, R3, R4, R5, R6, R7, R8;
  };

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
  [[nodiscard]] int calculateRealVoltage(int adcVoltage);
  [[nodiscard]] Note matchVoltageWithNote(int voltage) const;

  [[nodiscard]] int calculateNoteVoltage(unsigned long noteResistance) const;

  const Resistors RESISTORS;
  const Note NOTES[NOTES_AMOUNT]{ Note::C4, Note::C4_SHARP,
                                  Note::D4, Note::D4_SHARP,
                                  Note::E4,
                                  Note::F4, Note::F4_SHARP,
                                  Note::G4, Note::G4_SHARP,
                                  Note::A4, Note::A4_SHARP,
                                  Note::B4 };
  const int NOTES_VOLTAGE[NOTES_AMOUNT];

  const uint8_t ANALOG_PIN;
  Note m_CurrentNote{};
  Octave m_Octave;
};