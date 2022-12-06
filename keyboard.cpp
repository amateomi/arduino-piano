#include "keyboard.hpp"

#include "utility.hpp"

enum Resistor : long {
  R0 = 10000,
  R1 = 560,
  R2 = 1300,
  R3 = 2700,
  R4 = 3900,
  R5 = 5600,
  R6 = 7500,
  R7 = 10000,
};

[[nodiscard]] constexpr long sumParallelResistors(Resistor r1, Resistor r2) {
  return r1 * r2 / float(r1 + r2);
}

enum class NoteResistance {
  C4 = R1,
  C4_SHARP = sumParallelResistors(R1, R2),
  D4 = R2,
  D4_SHARP = sumParallelResistors(R2, R3),
  E4 = R3,
  F4 = R4,
  F4_SHARP = sumParallelResistors(R4, R5),
  G4 = R5,
  G4_SHARP = sumParallelResistors(R5, R6),
  A4 = R6,
  A4_SHARP = sumParallelResistors(R6, R7),
  B4 = R7,
};

constexpr float ARDUINO_POWER_VOLTAGE = 5.0;
constexpr int ARDUINO_MAX_ADC_VOLTAGE = 1024;

constexpr int calculateMainOctaveVoltages(NoteResistance resistance) {
  return static_cast<int>(resistance) / float(R0 + static_cast<int>(resistance))
         * ARDUINO_MAX_ADC_VOLTAGE;
}

const int Keyboard::MAIN_OCTAVE_VOLTAGES[OCTAVE_NOTES_NUM]{
  calculateMainOctaveVoltages(NoteResistance::C4_SHARP),
  calculateMainOctaveVoltages(NoteResistance::C4),
  calculateMainOctaveVoltages(NoteResistance::D4_SHARP),
  calculateMainOctaveVoltages(NoteResistance::D4),
  calculateMainOctaveVoltages(NoteResistance::F4_SHARP),
  calculateMainOctaveVoltages(NoteResistance::E4),
  calculateMainOctaveVoltages(NoteResistance::G4_SHARP),
  calculateMainOctaveVoltages(NoteResistance::F4),
  calculateMainOctaveVoltages(NoteResistance::A4_SHARP),
  calculateMainOctaveVoltages(NoteResistance::G4),
  calculateMainOctaveVoltages(NoteResistance::A4),
  calculateMainOctaveVoltages(NoteResistance::B4),
};
const Keyboard::NoteFrequency Keyboard::MAIN_OCTAVE_FREQUENCIES[OCTAVE_NOTES_NUM]{
  Keyboard::NoteFrequency::C4_SHARP,
  Keyboard::NoteFrequency::C4,
  Keyboard::NoteFrequency::D4_SHARP,
  Keyboard::NoteFrequency::D4,
  Keyboard::NoteFrequency::F4_SHARP,
  Keyboard::NoteFrequency::E4,
  Keyboard::NoteFrequency::G4_SHARP,
  Keyboard::NoteFrequency::F4,
  Keyboard::NoteFrequency::A4_SHARP,
  Keyboard::NoteFrequency::G4,
  Keyboard::NoteFrequency::A4,
  Keyboard::NoteFrequency::B4,
};

Keyboard::Keyboard() {
  pinMode(PIN, INPUT);
  pinMode(UPPER_OCTAVE_PIN, INPUT_PULLUP);
  pinMode(LOWER_OCTAVE_PIN, INPUT_PULLUP);

  LOG("Keyboard: Created and atached to analog pin=%i, upper octave pin=%i, lower octave pin=%i",
      PIN, UPPER_OCTAVE_PIN, LOWER_OCTAVE_PIN);

  LOG("Keyboard: Main octave computations (voltages must be in increasing order)");
  for (int i = 0; i < OCTAVE_NOTES_NUM; ++i) {
    LOG("Keyboard: voltage=%i, frequency=%i", MAIN_OCTAVE_VOLTAGES[i], MAIN_OCTAVE_FREQUENCIES[i]);
  }
}

void Keyboard::updateCurrentOctave() {
  PUSH_BUTTON_HANDLER(LOWER_OCTAVE_PIN, m_isLowerPressed, pressLowerCallback());
  PUSH_BUTTON_HANDLER(UPPER_OCTAVE_PIN, m_isUpperPressed, pressUpperCallback());
}

void Keyboard::pressLowerCallback() {
  constexpr int LOWEST_OCTAVE{ -3 };
  if (m_currentOctave != LOWEST_OCTAVE)
    --m_currentOctave;
  LOG("Keyboard: Lower button is pressed, current octave=%i", m_currentOctave);
}

void Keyboard::pressUpperCallback() {
  constexpr int HIGHEST_OCTAVE{ 3 };
  if (m_currentOctave != HIGHEST_OCTAVE)
    ++m_currentOctave;
  LOG("Keyboard: Upper button is pressed, current octave=%i", m_currentOctave);
}

unsigned int Keyboard::getNoteFrequency() const {
  const int voltage = analogRead(PIN);
  unsigned int frequency = mainOctaveVoltageToFrequency(voltage);
  frequency = m_currentOctave < 0 ? frequency >> abs(m_currentOctave) : frequency << m_currentOctave;

  if (frequency != 0)
    LOG("Keyboard: In voltage=%i, Out frequency=%u", voltage, frequency);

  return frequency;
}

unsigned int Keyboard::mainOctaveVoltageToFrequency(int voltage) {
  for (int i = 0; i < OCTAVE_NOTES_NUM; ++i) {
    constexpr int reserve = 10;
    if (MAIN_OCTAVE_VOLTAGES[i] - reserve < voltage && voltage < MAIN_OCTAVE_VOLTAGES[i] + reserve)
      return MAIN_OCTAVE_FREQUENCIES[i];
  }
  return 0;
}
