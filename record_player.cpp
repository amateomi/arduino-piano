#include "record_player.hpp"

#include <Arduino.h>

#include "utility.hpp"
#include "sound.hpp"
#include "buzzer.hpp"

RecordPlayer& RecordPlayer::get() {
  static RecordPlayer instance;
  return instance;
}

RecordPlayer::RecordPlayer() {
  pinMode(PLAYBACK_PIN, INPUT_PULLUP);
  pinMode(PREVIOUS_MELODY_PIN, INPUT_PULLUP);
  pinMode(NEXT_MELODY_PIN, INPUT_PULLUP);
  LOG("RecordPlayer: Created and attached to playback pin=%i, previous melody pin=%i, next melody pin=%i",
      PLAYBACK_PIN, PREVIOUS_MELODY_PIN, NEXT_MELODY_PIN);
}

void RecordPlayer::updateCurrentMelody() {
  PUSH_BUTTON_HANDLER(PREVIOUS_MELODY_PIN, m_isPreviousButtonPressed, pressPreviousCallback());
  PUSH_BUTTON_HANDLER(NEXT_MELODY_PIN, m_isNextButtonPressed, pressNextCallback());
}

void RecordPlayer::updatePlaybackState() {
  PUSH_BUTTON_HANDLER(PLAYBACK_PIN, m_isPlaybackButtonPressed, pressPlaybackCallback());
}

void RecordPlayer::pressPlaybackCallback() const {
  for (int i = m_melodyIndex; !SoundPool::get()[i].isSeparator(); ++i) {
    Buzzer::get().play(SoundPool::get()[i].frequency());
    delay(SoundPool::get()[i].duration());
    LOG("RecordPlayer: playback sound={ frequency=%u, duration=%lu }",
        SoundPool::get()[i].frequency(),
        SoundPool::get()[i].duration());
  }
}

void RecordPlayer::pressPreviousCallback() {
  setPreviousMelodyIndex();
  LOG("RecordPlayer: Previous button is pressed, melody index=%i", m_melodyIndex);
}

void RecordPlayer::pressNextCallback() {
  setNextMelodyIndex();
  LOG("RecordPlayer: Next button is pressed, melody index=%i", m_melodyIndex);
}

void RecordPlayer::setPreviousMelodyIndex() {
  if (m_melodyIndex == 0)
    return;

  --m_melodyIndex;
  while (m_melodyIndex != 0 && !SoundPool::get()[m_melodyIndex - 1].isSeparator())
    --m_melodyIndex;
}

void RecordPlayer::setNextMelodyIndex() {
  int nextIndex = m_melodyIndex + 1;
  while (nextIndex < Sound::POOL_SIZE && !SoundPool::get()[nextIndex - 1].isSeparator())
    ++nextIndex;

  if (nextIndex == Sound::POOL_SIZE || SoundPool::get()[nextIndex].isSeparator())
    return;

  m_melodyIndex = nextIndex;
}