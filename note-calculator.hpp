#pragma once

#include "logger.hpp"
#include "note.hpp"

// Resistance of all resistors in the keyboard circuit.
// R1 should be equal 10kOm.
// Resistance of R2-R8 should be sorted ascending.
struct Resistors {
  unsigned long R1, R2, R3, R4, R5, R6, R7, R8;
};

class NoteCalculator {
public:
  explicit NoteCalculator(Resistors resistors)
    : RESISTORS{ resistors },
      NOTES_VOLTAGE{ calculateNoteVoltage(RESISTORS.R2),
                     calculateNoteVoltage(sumParallelResistors(RESISTORS.R2, RESISTORS.R3)),
                     calculateNoteVoltage(RESISTORS.R3),
                     calculateNoteVoltage(sumParallelResistors(RESISTORS.R3, RESISTORS.R4)),
                     calculateNoteVoltage(RESISTORS.R4),
                     calculateNoteVoltage(RESISTORS.R5),
                     calculateNoteVoltage(sumParallelResistors(RESISTORS.R5, RESISTORS.R6)),
                     calculateNoteVoltage(RESISTORS.R6),
                     calculateNoteVoltage(sumParallelResistors(RESISTORS.R6, RESISTORS.R7)),
                     calculateNoteVoltage(RESISTORS.R7),
                     calculateNoteVoltage(sumParallelResistors(RESISTORS.R7, RESISTORS.R8)),
                     calculateNoteVoltage(RESISTORS.R8) } {

    const char* NOTES_NAME[NOTES_AMOUNT] = { "C4", "C4_SHARP",
                                             "D4", "D4_SHARP",
                                             "E4",
                                             "F4", "F4_SHARP",
                                             "G4", "G4_SHARP",
                                             "A4", "A4_SHARP",
                                             "B4" };

    for (int i = 0; i < NOTES_AMOUNT; ++i) {
      log("Note: %s\tFrequency: %u\tVoltage: %i",
          NOTES_NAME[i],
          static_cast<unsigned int>(NOTES[i]),
          NOTES_VOLTAGE[i]);
    }
  }

  // Return note according to given voltage.
  // For unknown voltages return Note::NONE.
  [[nodiscard]] Note matchVoltageWithNote(int voltage) const {
    constexpr auto DEVIATION_ERROR = 10;
    for (auto i = 0; i < NOTES_AMOUNT; ++i) {
      if (const auto delta = abs(NOTES_VOLTAGE[i] - voltage);
          delta < DEVIATION_ERROR) {
        return NOTES[i];
      }
    }
    return Note::NONE;
  }

private:
  [[nodiscard]] unsigned long sumParallelResistors(unsigned long r1,
                                                   unsigned long r2) const {
    return r1 * r2 / static_cast<float>(r1 + r2);
  }

  [[nodiscard]] int calculateNoteVoltage(unsigned long noteResistance) const {
    constexpr auto ADC_MAX_VALUE = 1024;
    return ADC_MAX_VALUE * (static_cast<float>(noteResistance) / (RESISTORS.R1 + noteResistance));
  }

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