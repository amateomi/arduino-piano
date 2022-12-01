#include "music-player.hpp"

#include <Arduino.h>

#include "debug.hpp"

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
      m_soundPool[m_recordingIndex].setAsSeparator();
      ++m_recordingIndex;
    } else {
      // m_soundPool[m_recordingIndex].duration = millis() - m_soundPool[m_recordingIndex].duration;
      // LOG("MusicPlayer: Last sound={ frequency=%u, duration=%lu }", m_soundPool[m_recordingIndex].frequency, m_soundPool[m_recordingIndex].duration);
      // ++m_recordingIndex;
      m_soundPool[m_recordingIndex - 1].setAsSeparator();
    }

    LOG("MusicPlayer: Recording status=%i", m_isRecording);

  } else if (buttonStatus == HIGH && m_isRecordingPressed) {
    m_isRecordingPressed = false;
  }

  if (const int buttonStatus = digitalRead(PLAYBACK_PIN);
      buttonStatus == LOW && !m_isPlaybackPressed) {
    m_isPlaybackPressed = true;

    m_isPlayback = !m_isPlayback;

    LOG("MusicPlayer: Playback status=%i", m_isPlayback);

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
  if (m_soundPool[m_recordingIndex - 1].isSeparator()) {
    if (frequency != 0) {
      m_soundPool[m_recordingIndex].frequency = frequency;
      m_soundPool[m_recordingIndex].duration = millis();
      LOG("MusicPlayer: First sound frequency=%u", m_soundPool[m_recordingIndex].frequency);
      ++m_recordingIndex;
    }
  } else if (m_soundPool[m_recordingIndex - 1].frequency != frequency) {
    m_soundPool[m_recordingIndex - 1].duration = (millis() - m_soundPool[m_recordingIndex - 1].duration);
    LOG("MusicPlayer: Add sound={ frequency=%u, duration=%lu }", m_soundPool[m_recordingIndex - 1].frequency, m_soundPool[m_recordingIndex - 1].duration);
    m_soundPool[m_recordingIndex].frequency = frequency;
    m_soundPool[m_recordingIndex].duration = millis();
    LOG("MusicPlayer: New sound frequency=%u", m_soundPool[m_recordingIndex].frequency);
    ++m_recordingIndex;
  }
}

void MusicPlayer::playback(const Buzzer& buzzer) {
  for (int i = m_currentMelody + 1; !m_soundPool[i].isSeparator(); ++i) {
    LOG("MusicPlayer: playback sound={ frequency=%u, duration=%lu }", m_soundPool[i].frequency, m_soundPool[i].duration);
    buzzer.play(m_soundPool[i].frequency);
    delay(m_soundPool[i].duration);
  }
  m_isPlayback = false;
}