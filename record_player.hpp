#pragma once

#include "buzzer.hpp"

class RecordPlayer {
public:
  RecordPlayer();

  void updateCurrentMelody();
  void updatePlaybackState(const Buzzer&);

private:
  void pressPlaybackCallback(const Buzzer&);
  void pressPreviousCallback();
  void pressNextCallback();

  void setPreviousMelodyIndex();
  void setNextMelodyIndex();

  static constexpr int PLAYBACK_PIN{ 5 };
  static constexpr int PREVIOUS_MELODY_PIN{ 4 };
  static constexpr int NEXT_MELODY_PIN{ 3 };

  bool m_isPlaybackButtonPressed{};

  int m_melodyIndex{};  //< Sound pool melody index
  bool m_isPreviousButtonPressed{};
  bool m_isNextButtonPressed{};
};