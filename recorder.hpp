#pragma once

class Recorder {
public:
  static Recorder& get();

  Recorder(const Recorder&) = delete;
  Recorder& operator=(const Recorder&) = delete;

  void updateRecordingState(unsigned int frequency);

private:
  Recorder();
  ~Recorder() = default;

  void pressCallback();
  void beginMelody() const;
  void endMelody() const;
  void appendMelodySound(unsigned int frequency);

  static constexpr int PIN{ 6 };

  int m_nextSoundIndex{};  //< Next index in SoundPool to write
  
  bool m_isRecording{};
  bool m_isButtonPressed{};
  
  bool m_wasOutOfBoundWriteAttempt{};
};