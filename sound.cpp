#include "sound.hpp"

Sound Sound::s_pool[SOUND_POOL_SIZE]{};

Sound::Sound(unsigned int frequency, unsigned long duration)
  : m_frequency{ frequency }, m_duration{ duration } {}

bool Sound::operator==(const Sound& s) const {
  return m_frequency == s.m_frequency && m_duration == s.m_duration;
}

bool Sound::operator!=(const Sound& s) const {
  return !(*this == s);
}

unsigned int Sound::frequency() const {
  return m_frequency;
}

unsigned long Sound::duration() const {
  return m_duration;
}

bool Sound::isSeparator() const {
  return m_frequency == 0 && m_duration == 0;
}

void Sound::setFrequency(unsigned int frequency) {
  m_frequency = frequency;
}

void Sound::setDuration(unsigned long duration) {
  m_duration = duration;
}

void Sound::setAsSeparator() {
  m_frequency = 0;
  m_duration = 0;
}

const Sound& Sound::poolRead(int index) {
  return s_pool[index];
}

Sound& Sound::poolWrite(int index) {
  return s_pool[index];
}