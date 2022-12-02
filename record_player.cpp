#include "record_player.hpp"

#include <Arduino.h>

#include "utility.hpp"
#include "sound.hpp"

RecordPlayer::RecordPlayer() {
  pinMode(PLAYBACK_PIN, INPUT_PULLUP);
  pinMode(PREVIOUS_MELODY_PIN, INPUT_PULLUP);
  pinMode(NEXT_MELODY_PIN, INPUT_PULLUP);
  LOG("RecordPlayer: Created");
}

void RecordPlayer::updateCurrentMelody() {
  PUSH_BUTTON_HANDLER(PREVIOUS_MELODY_PIN, m_isPreviousButtonPressed, pressPreviousCallback(), nullptr);
  PUSH_BUTTON_HANDLER(NEXT_MELODY_PIN, m_isNextButtonPressed, pressNextCallback(), nullptr);
}

void RecordPlayer::updatePlaybackState(const Buzzer& buzzer) {
  PUSH_BUTTON_HANDLER(PLAYBACK_PIN, m_isPlaybackButtonPressed, pressPlaybackCallback(buzzer), nullptr);
}

void RecordPlayer::pressPlaybackCallback(const Buzzer& buzzer) {
  for (int i = m_melodyIndex; !Sound::poolRead(i).isSeparator(); ++i) {
    buzzer.play(Sound::poolRead(i).frequency());
    delay(Sound::poolRead(i).duration());
    LOG("RecordPlayer: playback sound={ frequency=%u, duration=%lu }",
        Sound::poolRead(i).frequency(),
        Sound::poolRead(i).duration());
  }
}

void RecordPlayer::pressPreviousCallback() {
  setPreviousMelodyIndex();
  LOG("RecordPlayer: Previous button is pressed, current melodyIndex=%i", m_melodyIndex);
}

void RecordPlayer::pressNextCallback() {
  setNextMelodyIndex();
  LOG("RecordPlayer: Next button is pressed, current melodyIndex=%i", m_melodyIndex);
}

void RecordPlayer::setPreviousMelodyIndex() {
  if (m_melodyIndex == 0)
    return;

  --m_melodyIndex;
  while(m_melodyIndex != 0 && !Sound::poolRead(m_melodyIndex - 1).isSeparator())
    --m_melodyIndex;
}

void RecordPlayer::setNextMelodyIndex() {
  int nextIndex = m_melodyIndex + 1;
  while (nextIndex < Sound::POOL_SIZE && !Sound::poolRead(nextIndex - 1).isSeparator())
    ++nextIndex;

  if (nextIndex == Sound::POOL_SIZE || Sound::poolRead(nextIndex).isSeparator())
    return;

  m_melodyIndex = nextIndex;
}