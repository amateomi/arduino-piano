#pragma once

#include "note.hpp"

// Resistance of all resistors in the keyboard circuit.
// R1 should be equal 10kOm.
// Resistance of R2-R8 should be sorted ascending.
struct Resistors {
  unsigned long R1, R2, R3, R4, R5, R6, R7, R8;
};

class NoteCalculator {
public:
  explicit NoteCalculator(Resistors);

  // Return note according to given voltage.
  // For unknown voltages return Note::NONE.
  [[nodiscard]] Note matchVoltageWithNote(int voltage) const;

private:
  [[nodiscard]] unsigned long sumParallelResistors(unsigned long r1,
                                                   unsigned long r2) const;
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
};