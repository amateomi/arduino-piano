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
}

void RecordPlayer::updatePlaybackState(const Buzzer& buzzer) {
  PUSH_BUTTON_HANDLER(PLAYBACK_PIN, m_isPlaybackButtonPressed, pressPlaybackCallback(buzzer), nullptr);
}

void RecordPlayer::pressPlaybackCallback(const Buzzer& buzzer) {
  for (int i = m_melodyIndex + 1; !Sound::poolRead(i).isSeparator(); ++i) {
    buzzer.play(Sound::poolRead(i).frequency());
    delay(Sound::poolRead(i).duration());
    LOG("RecordPlayer: playback sound={ frequency=%u, duration=%lu }",
        Sound::poolRead(i).frequency(),
        Sound::poolRead(i).duration());
  }
}