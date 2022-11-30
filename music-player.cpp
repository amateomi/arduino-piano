#include "buzzer.hpp"
#include "music-player.hpp"

#include <Arduino.h>

#include "debug.hpp"

const MusicPlayer::Sound MusicPlayer::MELODY_SEPARATOR{ 0, 0 };

MusicPlayer::MusicPlayer() {
  pinMode(RECORD_PIN, INPUT_PULLUP);
  pinMode(PLAYBACK_PIN, INPUT_PULLUP);
  pinMode(PREVIOUS_MELODY_PIN, INPUT_PULLUP);
  pinMode(NEXT_MELODY_PIN, INPUT_PULLUP);
}

void MusicPlayer::update() {
  if (const int buttonStatus = digitalRead(RECORD_PIN);
      buttonStatus == LOW && !m_isRecordingPressed) {
    m_isRecordingPressed = true;

    m_isRecording = !m_isRecording;
    if (m_isRecording) {
      *m_recordMelody = MELODY_SEPARATOR;
      ++m_recordMelody;
    } else {
      m_recordMelody[-1] = MELODY_SEPARATOR;
    }

    LOG("MusicPlayer: Recording status=%i", m_isRecording);

  } else if (buttonStatus == HIGH && m_isRecordingPressed) {
    m_isRecordingPressed = false;
  }

  if (const int buttonStatus = digitalRead(PLAYBACK_PIN);
      buttonStatus == LOW && !m_isPlaybackPressed) {
    m_isPlaybackPressed = true;

    m_isPlayback = !m_isPlayback;

    LOG("MusicPlayer: Playback status=%i", m_isRecording);

  } else if (buttonStatus == HIGH && m_isPlaybackPressed) {
    m_isPlaybackPressed = false;
  }
}

bool MusicPlayer::isRecording() const {
  return m_isRecording;
}
bool MusicPlayer::isPlayback() const {
  return m_isPlayback;
}

void MusicPlayer::appendSound(unsigned int frequency) {
  // First sound in melody
  if (m_recordMelody[-1] == MELODY_SEPARATOR && frequency != 0) {
    m_recordMelody->frequency = frequency;
    m_recordMelody->duration = millis();
    LOG("MusicPlayer: First sound frequency=%u", m_recordMelody->frequency);
    ++m_recordMelody;

    // All other sounds
  } else if (m_recordMelody[-1].frequency != frequency) {
    m_recordMelody[-1].duration = millis() - m_recordMelody[-1].duration;
    LOG("MusicPlayer: Add sound={ frequency=%u, duration=%lu }", m_recordMelody[-1].frequency, m_recordMelody[-1].duration);
    m_recordMelody->frequency = frequency;
    LOG("MusicPlayer: New sound frequency=%u", m_recordMelody->frequency);
    m_recordMelody->duration = millis();
    ++m_recordMelody;
  }
}

void MusicPlayer::playback(const Buzzer& buzzer) {
  for (int i = 1; m_currentMelody[i] != MELODY_SEPARATOR; ++i) {
    buzzer.play(m_currentMelody[i].frequency);
    delay(m_currentMelody[i].duration);    
  }
  m_isPlayback = false;
}