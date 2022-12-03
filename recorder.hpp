#pragma once

#include "buzzer.hpp"

class Recorder {
public:
  Recorder();

  void updateRecordingState(const Buzzer&, unsigned int frequency);

private:
  void pressCallback();
  void beginMelody() const;
  void endMelody() const;

  bool appendMelodySound(unsigned int frequency); //< Return false when sound pool overflow

  static constexpr int PIN{ 6 };

  int m_nextSoundIndex{};  //< Next index in SoundPool to write

  bool m_isRecording{};
  bool m_isButtonPressed{};

  bool m_wasOutOfBoundWriteAttempt{};
};