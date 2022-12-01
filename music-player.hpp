#pragma once

#include "buzzer.hpp"

class MusicPlayer {
public:
  MusicPlayer();

  void update();

  bool isRecording() const;
  bool isPlayback() const;

  void appendSound(unsigned int frequency);
  void playback(const Buzzer& buzzer);

private:
  static constexpr int RECORD_PIN{ 6 };
  static constexpr int PLAYBACK_PIN{ 5 };
  static constexpr int PREVIOUS_MELODY_PIN{ 4 };
  static constexpr int NEXT_MELODY_PIN{ 3 };

  static constexpr int SOUND_POOL_SIZE{ 64 };

  struct Sound {
    Sound() = default;
    Sound(unsigned int f, int d)
      : frequency{ f }, duration{ d } {}

    bool operator==(const Sound& sound) {
      return this->frequency == sound.frequency && this->duration == sound.duration;
    }
    bool operator!=(const Sound& sound) {
      return !(*this == sound);
    }

    bool isSeparator() const {
      return frequency == 0 && duration == 0;
    }
    void setAsSeparator() {
      frequency = 0;
      duration = 0;
    }

    unsigned int frequency{};
    unsigned long duration{};  //< Duration in milliseconds
  };

  Sound m_soundPool[SOUND_POOL_SIZE]{};

  int m_currentMelody{};
  bool m_isPreviousPressed{};
  bool m_isNextPressed{};

  int m_recordingIndex{};  //< Points to next melody sound
  bool m_isRecording{};
  bool m_isRecordingPressed{};

  bool m_isPlayback{};
  bool m_isPlaybackPressed{};
};