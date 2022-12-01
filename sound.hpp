#pragma once

class Sound {
public:
  Sound() = default;
  Sound(unsigned int frequency, unsigned long duration);

  [[nodiscard]] bool operator==(const Sound&) const;
  [[nodiscard]] bool operator!=(const Sound&) const;

  [[nodiscard]] unsigned int frequency() const;
  [[nodiscard]] unsigned long duration() const;
  [[nodiscard]] bool isSeparator() const;

  void setFrequency(unsigned int);
  void setDuration(unsigned long);
  void setAsSeparator();

  [[nodiscard]] static const Sound& poolRead(int index);
  [[nodiscard]] static Sound& poolWrite(int index);

private:
  static constexpr int SOUND_POOL_SIZE{ 64 };
  static Sound s_pool[SOUND_POOL_SIZE];

  unsigned int m_frequency{};
  unsigned long m_duration{};  //< Duration in milliseconds
};