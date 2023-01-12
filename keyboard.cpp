#include "notes.hpp"
#include "keyboard.hpp"

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
    NOTES_VOLTAGE{ calculateNoteVoltage(RESISTORS[1]),
                   calculateNoteVoltage(sumParallelResistors(RESISTORS[1], RESISTORS[2])),
                   calculateNoteVoltage(RESISTORS[2]),
                   calculateNoteVoltage(sumParallelResistors(RESISTORS[2], RESISTORS[3])),
                   calculateNoteVoltage(RESISTORS[3]),
                   calculateNoteVoltage(RESISTORS[4]),
                   calculateNoteVoltage(sumParallelResistors(RESISTORS[4], RESISTORS[5])),
                   calculateNoteVoltage(RESISTORS[5]),
                   calculateNoteVoltage(sumParallelResistors(RESISTORS[5], RESISTORS[6])),
                   calculateNoteVoltage(RESISTORS[6]),
                   calculateNoteVoltage(sumParallelResistors(RESISTORS[6], RESISTORS[7])),
                   calculateNoteVoltage(RESISTORS[7]) },
    ANALOG_PIN{ analogPin },
    m_Octave{ decreaseOctaveButtonPin, increaseOctaveButtonPin } {
}

void Keyboard::OnUpdate() {
  m_Octave.OnUpdate();

  const int adcVoltage = analogRead(ANALOG_PIN);
  const int voltage = calculateRealVoltage(adcVoltage);
  m_CurrentNote = matchVoltageWithNote(voltage);
}

int Keyboard::calculateRealVoltage(int adcVoltage) {
  constexpr auto POWER_VOLTAGE = 5.0;
  constexpr auto MAX_ADC_VOLTAGE = 1024;
  return adcVoltage * POWER_VOLTAGE / MAX_ADC_VOLTAGE;
}

Note Keyboard::matchVoltageWithNote(int voltage) {
  constexpr auto DEVIATION_ERROR = 10;
  for (auto i = 0; i < NOTES_AMOUNT; ++i) {
    if (const auto delta = abs(NOTES_VOLTAGE[i] - voltage);
        delta < DEVIATION_ERROR) {
      return NOTES[i];
    }
  }
  return Note::NONE;
}

int Keyboard::calculateNoteVoltage(unsigned long noteResistance) {
  constexpr auto POWER_VOLTAGE = 5;
  return POWER_VOLTAGE * (static_cast<float>(noteResistance) / (RESISTORS[0] + noteResistance));
}