#pragma once

class Buzzer {
public:
  Buzzer();

  /// Play sound or stop playing if frequency = 0
  void play(unsigned int frequency) const;

private:
  static constexpr int PIN{ 2 };
};