#include "sound.hpp"

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

SoundPool& SoundPool::get() {
  static SoundPool instance;
  return instance;
}

Sound& SoundPool::operator[](int index) {
  return m_pool[index];
}
const Sound& SoundPool::operator[](int index) const {
  return m_pool[index];
}