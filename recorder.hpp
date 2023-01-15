#pragma once

#include "logger.hpp"
#include "melody-storage.hpp"
#include "keyboard.hpp"
#include "buzzer.hpp"

class Recorder {
public:
  Recorder(uint8_t pin,
           MelodyStorage& melodyStorage,
           const Keyboard& keyboard,
           const Buzzer& buzzer)
    : m_ControlButton{ pin, INPUT_PULLUP },
      m_MelodyStorage{ melodyStorage },
      m_Keyboard{ keyboard },
      m_Buzzer{ buzzer } {
    log("Recorder created");
  }

  // Handle recording state and control melody writing process
  void OnUpdate() {
    const auto frequency = Octave::MatchNoteWithFrequency(m_Keyboard.GetNote(),
                                                          m_Keyboard.GetOctave());

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
            reactToStorageOverflow();
          }
        } else {
          m_MelodyStorage.StopRecording();
        }
        break;

      case Button::Event::NONE:
        if (m_IsRecording) {
          if (!m_MelodyStorage.UpdateMelody(frequency)) {
            reactToStorageOverflow();
          }
        }
        break;
    }
  }

private:
  void reactToStorageOverflow() {
    log("Recorder: overflow attempt detected");
    m_Buzzer.PlayAlarm();
    m_IsRecording = false;    
  }

  Button m_ControlButton;
  bool m_IsRecording{};
  MelodyStorage& m_MelodyStorage;
  const Keyboard& m_Keyboard;
  const Buzzer& m_Buzzer;
};