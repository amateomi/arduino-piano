#pragma once

#include "buzzer.hpp"

class RecordPlayer {
public:
  RecordPlayer();

  void updatePlaybackState(const Buzzer&);
  void updateCurrentMelody();

private:
  void pressPlaybackCallback(const Buzzer&) const;

  void pressPreviousCallback();
  void pressNextCallback();

  void setPreviousMelodyIndex();
  void setNextMelodyIndex();

  static constexpr int PLAYBACK_PIN{ 5 };
  static constexpr int PREVIOUS_MELODY_PIN{ 4 };
  static constexpr int NEXT_MELODY_PIN{ 3 };

  int m_melodyIndex{};  //< Current melody index to read from SoundPool

  bool m_isPlaybackButtonPressed{};

  bool m_isPreviousButtonPressed{};
  bool m_isNextButtonPressed{};
};