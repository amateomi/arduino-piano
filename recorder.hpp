#pragma once

class Recorder {
public:
  Recorder();

  void updateRecordingState(unsigned int frequency);

private:
  void pressCallback();
  void beginMelody();
  void endMelody() const;

  void appendMelodySound(unsigned int frequency);

  static constexpr int PIN{ 6 };

  int m_index{};  //< Sound pool next write index
  bool m_isRecording{};
  bool m_isButtonPressed{};
};