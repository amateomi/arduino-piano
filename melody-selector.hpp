#pragma once

#include "button.hpp"
#include "melody-storage.hpp"

class MelodySelector {
public:
  MelodySelector(uint8_t previousMelodyButtonPin,
                 uint8_t nextMelodyButtonPin,
                 const MelodyStorage& melodyStorage)
    : m_PreviousMelodyButton{ previousMelodyButtonPin, INPUT_PULLUP },
      m_NextMelodyButton{ nextMelodyButtonPin, INPUT_PULLUP },
      m_MelodyStorage{ melodyStorage } {}

  // Moving between recorded melodies in melody storage
  void OnUpdate() {
    if (const auto event = m_PreviousMelodyButton.OnUpdate();
        event == Button::Event::PRESS) {
      MoveToPreviousMelody();
      log("MelodySelector: previous melody, current index=%hu", m_CurrentMelodyIndex);
    }
    if (const auto event = m_NextMelodyButton.OnUpdate();
        event == Button::Event::PRESS) {
      MoveToNextMelody();
      log("MelodySelector: next melody, current index=%hu", m_CurrentMelodyIndex);
    }
  }

  [[nodiscard]] size_t GetCurrentMelodyIndex() const {
    return m_CurrentMelodyIndex;
  }

private:
  void MoveToPreviousMelody() {
    if (m_CurrentMelodyIndex == 0) {
      return;
    }
    --m_CurrentMelodyIndex;
    while (m_CurrentMelodyIndex != 0
           && !m_MelodyStorage.Read(m_CurrentMelodyIndex - 1).IsSeparator) {
      --m_CurrentMelodyIndex;
    }
  }

  void MoveToNextMelody() {
    size_t i = m_CurrentMelodyIndex + 1;
    while (i != m_MelodyStorage.GetUsedLength()
           && !m_MelodyStorage.Read(i - 1).IsSeparator) {
      ++i;
    }
    if (i != m_MelodyStorage.GetUsedLength()
        && !m_MelodyStorage.Read(i).IsSeparator) {
      m_CurrentMelodyIndex = i;
    }
  }

  Button m_PreviousMelodyButton;
  Button m_NextMelodyButton;
  size_t m_CurrentMelodyIndex{};
  const MelodyStorage& m_MelodyStorage;
};