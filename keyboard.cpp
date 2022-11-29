#include "keyboard.hpp"

#include "debug.hpp"

// TODO: calculate at compile time
const int Keyboard::OCTAVE_VOLTAGES[OCTAVE_NOTES_NUM]{ 38, 55, 84, 120, 196, 225, 259, 296, 322, 382, 464, 535 };
const unsigned int Keyboard::OCTAVE_FREQUENCIES[OCTAVE_NOTES_NUM]{ 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494 };

Keyboard::Keyboard() {
  pinMode(PIN, INPUT);
  pinMode(UPPER_OCTAVE_PIN, INPUT_PULLUP);
  pinMode(LOWER_OCTAVE_PIN, INPUT_PULLUP);
}

void Keyboard::update() {
  if (digitalRead(LOWER_OCTAVE_PIN) == LOW && !m_isLowerPressed) {
    m_isLowerPressed = true;

    if (m_currentOctave != LOWEST_OCTAVE)
      --m_currentOctave;

    LOG("Keyboard: Lower button is pressed, current octave=%i", m_currentOctave);

  } else if (digitalRead(LOWER_OCTAVE_PIN) == HIGH && m_isLowerPressed) {
    m_isLowerPressed = false;

    LOG("Keyboard: Lower button is released, current octave=%i", m_currentOctave);
  }

  if (digitalRead(UPPER_OCTAVE_PIN) == LOW && !m_isUpperPressed) {
    m_isUpperPressed = true;

    if (m_currentOctave != HIGHEST_OCTAVE)
      ++m_currentOctave;

    LOG("Keyboard: Upper button is pressed, current octave=%i", m_currentOctave);

  } else if (digitalRead(UPPER_OCTAVE_PIN) == HIGH && m_isUpperPressed) {
    m_isUpperPressed = false;

    LOG("Keyboard: Upper button is released, current octave=%i", m_currentOctave);
  }
}

unsigned int Keyboard::getFrequency() const {
  const int voltage = analogRead(PIN);
  unsigned int frequency = voltageToFrequency(voltage);
  frequency = m_currentOctave < 0 ? frequency >> abs(m_currentOctave) : frequency << m_currentOctave;
  
  LOG("Keyboard: In voltage=%i, Out frequency=%u", voltage, frequency);

  return frequency;
}

unsigned int Keyboard::voltageToFrequency(int voltage) {
  for (int i = 0; i < OCTAVE_NOTES_NUM; ++i) {
    if (voltage < OCTAVE_VOLTAGES[i])
      return OCTAVE_FREQUENCIES[i];
  }
  return 0;
}