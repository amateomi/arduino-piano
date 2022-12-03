#pragma once

#include "sound.hpp"

class Buzzer {
public:
  Buzzer();

  /// Play sound or stop playing when frequency is 0
  void play(unsigned int frequency) const;
  void play(Sound) const;

  void playAlarm() const;

private:
  static constexpr int PIN{ 2 };
};