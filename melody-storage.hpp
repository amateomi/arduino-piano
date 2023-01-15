#pragma once

#include "logger.hpp"

struct Sound {
  unsigned int Frequency{};
  unsigned long DurationMs{};
  bool IsSeparator{ true };

  void StartCountDuration() {
    DurationMs = millis();
  }

  void StopCountDuration() {
    DurationMs = millis() - DurationMs;
  }
};

class MelodyStorage {
public:
  // Return false if buffer is full
  bool StartRecording(unsigned int frequency) {
    if (IsBufferFull()) {
      return false;
    }
    log("MelodyStorage: start recording melody, used %hu storage length", m_UsedLength);
    StartSound(frequency);
    return true;
  }

  // Must be called after StartRecording.
  // Continue to write melody into buffer.
  // Return false if buffer is full.
  bool UpdateMelody(unsigned int frequency) {
    if (frequency == m_Buffer[m_UsedLength].Frequency) {
      return true;
    }
    StopSound();
    if (IsBufferFull()) {
      return false;
    }
    StartSound(frequency);
    return true;
  }

  void StopRecording() {
    StopSound();
    log("MelodyStorage: stop recording melody, used %hu storage length", m_UsedLength);
  }

  bool IsBufferFull() const {
    return m_UsedLength == CAPACITY;
  }

private:
  void StartSound(unsigned int frequency) {
    m_Buffer[m_UsedLength].Frequency = frequency;
    m_Buffer[m_UsedLength].StartCountDuration();
    m_Buffer[m_UsedLength].IsSeparator = false;
  }

  void StopSound() {
    m_Buffer[m_UsedLength].StopCountDuration();
    log("MelodyStorage: new sound{ frequency=%u, duration=%lums }",
        m_Buffer[m_UsedLength].Frequency, m_Buffer[m_UsedLength].DurationMs);
    ++m_UsedLength;
  }

  static constexpr auto CAPACITY = 10;
  Sound m_Buffer[CAPACITY]{};
  size_t m_UsedLength{};
};