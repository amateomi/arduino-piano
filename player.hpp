#pragma once

#include "logger.hpp"
#include "button.hpp"
#include "buzzer.hpp"
#include "melody-selector.hpp"
#include "melody-storage.hpp"

class Player {
public:
  Player(uint8_t playbackButtonPin,
         uint8_t previousMelodyButtonPin,
         uint8_t nextMelodyButtonPin,
         const MelodyStorage& melodyStorage)
    : m_PlaybackButton{ playbackButtonPin, INPUT_PULLUP },
      m_MelodySelector{ previousMelodyButtonPin, nextMelodyButtonPin, melodyStorage },
      m_MelodyStorage{ melodyStorage } {
    log("Player created");
  }

  // Manage melody playback
  void OnUpdate(const Buzzer& buzzer) {
    m_MelodySelector.OnUpdate();

    if (const auto event = m_PlaybackButton.OnUpdate();
        event == Button::Event::PRESS) {
      log("Player: start playback");
      Playback(buzzer);
      log("Player: stop playback");
    }
  }

private:
  void Playback(const Buzzer& buzzer) const {
    for (size_t i = m_MelodySelector.GetCurrentMelodyIndex();
         i != m_MelodyStorage.GetUsedLength() && !m_MelodyStorage.Read(i).IsSeparator;
         ++i) {
      buzzer.Play(m_MelodyStorage.Read(i));
    }
  }

  Button m_PlaybackButton;
  MelodySelector m_MelodySelector;
  const MelodyStorage& m_MelodyStorage;
};