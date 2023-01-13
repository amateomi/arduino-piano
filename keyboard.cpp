#include "keyboard.hpp"

#include "logger.hpp"

namespace {

[[nodiscard]] unsigned long sumParallelResistors(unsigned long r1,
                                                 unsigned long r2) {
  return r1 * r2 / static_cast<float>(r1 + r2);
}

}

Keyboard::Keyboard(Resistors resistors,
                   uint8_t analogPin,
                   uint8_t decreaseOctaveButtonPin,
                   uint8_t increaseOctaveButtonPin)
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
                   calculateNoteVoltage(RESISTORS.R8) },
    ANALOG_PIN{ analogPin },
    m_Octave{ decreaseOctaveButtonPin, increaseOctaveButtonPin } {

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

  log("Keyboard created");
}

void Keyboard::OnUpdate() {
  m_Octave.OnUpdate();

  const int adcVoltage = analogRead(ANALOG_PIN);
  m_CurrentNote = matchVoltageWithNote(adcVoltage);
}

Note Keyboard::GetNote() const {
  return m_CurrentNote;
}

int Keyboard::GetOctave() const {
  return m_Octave.GetOctave();
}

int Keyboard::calculateRealVoltage(int adcVoltage) {
  constexpr auto POWER_VOLTAGE = 5.0;
  constexpr auto MAX_ADC_VOLTAGE = 1024;
  return adcVoltage * POWER_VOLTAGE / MAX_ADC_VOLTAGE;
}

Note Keyboard::matchVoltageWithNote(int voltage) const {
  constexpr auto DEVIATION_ERROR = 10;
  for (auto i = 0; i < NOTES_AMOUNT; ++i) {
    if (const auto delta = abs(NOTES_VOLTAGE[i] - voltage);
        delta < DEVIATION_ERROR) {
      return NOTES[i];
    }
  }
  return Note::NONE;
}

int Keyboard::calculateNoteVoltage(unsigned long noteResistance) const {
  constexpr auto POWER_VOLTAGE = 1024;
  return POWER_VOLTAGE * (static_cast<float>(noteResistance) / (RESISTORS.R1 + noteResistance));
}