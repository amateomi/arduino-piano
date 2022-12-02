#pragma once

class Sound {
public:
  [[nodiscard]] unsigned int frequency() const;
  [[nodiscard]] unsigned long duration() const;
  [[nodiscard]] bool isSeparator() const;

  void setFrequency(unsigned int);
  void setDuration(unsigned long);
  void setAsSeparator();

  static constexpr int POOL_SIZE{ 64 };

private:
  unsigned int m_frequency{};
  unsigned long m_duration{};  //< Duration in milliseconds
};

class SoundPool {
public:
  static SoundPool& get();

  SoundPool(const SoundPool&) = delete;
  SoundPool& operator=(const SoundPool&) = delete;

  static constexpr int CAPACITY{ 64 };

  [[nodiscard]] Sound& operator[](int index);
  [[nodiscard]] const Sound& operator[](int index) const;

private:
  SoundPool() = default;
  ~SoundPool() = default;

  Sound m_pool[CAPACITY]{};  //< All sounds are separators by default
};