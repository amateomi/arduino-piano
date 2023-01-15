#pragma once

#include "logger.hpp"
#include "button.hpp"
#include "melody-storage.hpp"
#include "keyboard.hpp"
#include "buzzer.hpp"

class Recorder {
public:
  Recorder(uint8_t pin,
           MelodyStorage& melodyStorage)
    : m_ControlButton{ pin, INPUT_PULLUP },
      m_MelodyStorage{ melodyStorage } {
    log("Recorder created");
  }

  // Handle recording state and control melody writing process
  void OnUpdate(const Keyboard& keyboard, const Buzzer& buzzer) {
    const auto frequency = Octave::MatchNoteWithFrequency(keyboard.GetNote(),
                                                          keyboard.GetOctave());

    switch (const auto event = m_ControlButton.OnUpdate()) {
      case Button::Event::PRESS:
        if (m_MelodyStorage.IsBufferFull()) {
          log("Recorder: melody storage is full");
          return;
        }
        m_IsRecording = !m_IsRecording;
        log("Recorder: %s", (m_IsRecording ? "on" : "off"));
        if (m_IsRecording) {
          if (!m_MelodyStorage.StartRecording(frequency)) {
            reactToStorageOverflow(buzzer);
          }
        } else {
          m_MelodyStorage.StopRecording();
        }
        break;

      case Button::Event::NONE:
        if (m_IsRecording) {
          if (!m_MelodyStorage.UpdateMelody(frequency)) {
            reactToStorageOverflow(buzzer);
          }
        }
        break;
    }
  }

private:
  void reactToStorageOverflow(const Buzzer& buzzer) {
    log("Recorder: overflow attempt detected");
    buzzer.PlayAlarm();
    m_IsRecording = false;
  }

  Button m_ControlButton;
  bool m_IsRecording{};
  MelodyStorage& m_MelodyStorage;
};