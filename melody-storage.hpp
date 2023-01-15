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
  [[nodiscard]] bool StartRecording() {
    if (IsBufferFull()) {
      return false;
    }
    log("MelodyStorage: start recording melody, used %hu storage length", m_UsedLength);
    return true;
  }

  // Must be called after StartRecording.
  // Continue to write melody into buffer.
  // Return false if buffer is full.
  [[nodiscard]] bool UpdateMelody(unsigned int frequency) {
    if (frequency == m_Buffer[m_UsedLength].Frequency) {
      return true;
    }
    if (m_Buffer[m_UsedLength].IsSeparator) {
      StartSound(frequency);
    } else {
      StopSound();
      ++m_UsedLength;
      if (IsBufferFull()) {
        return false;
      }
      StartSound(frequency);
    }
    return true;
  }

  void StopRecording() {
    m_Buffer[m_UsedLength].IsSeparator = true;
    ++m_UsedLength;
    log("MelodyStorage: stop recording melody, used %hu storage length", m_UsedLength);
  }

  [[nodiscard]] size_t GetUsedLength() const {
    return m_UsedLength;
  }

  [[nodiscard]] bool IsBufferFull() const {
    return m_UsedLength == CAPACITY;
  }

  [[nodiscard]] const Sound& Read(size_t index) const {
    return m_Buffer[index];
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
  }

  static constexpr auto CAPACITY = 64;
  Sound m_Buffer[CAPACITY]{};
  size_t m_UsedLength{};
};