#include "utility.hpp"
#pragma once

class Sound {
public:
  [[nodiscard]] unsigned int frequency() const;
  [[nodiscard]] unsigned long duration() const;
  [[nodiscard]] bool isSeparator() const;

  void setFrequency(unsigned int);
  void setDuration(unsigned long);
  void setAsSeparator();

private:
  unsigned int m_frequency{};
  unsigned long m_duration{};  //< Duration in milliseconds
};

constexpr int POOL_BASE_CAPACITY{ 64 };

#ifdef DEBUG
constexpr int POOL_CAPACITY{ POOL_BASE_CAPACITY };
#else
constexpr int POOL_CAPACITY{ POOL_BASE_CAPACITY + LOG_MAX_LENGTH / sizeof(Sound) };
#endif

inline Sound soundPool[POOL_CAPACITY]{};  //< All sounds are separators by default