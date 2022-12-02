#pragma once

class Buzzer {
public:
  static Buzzer& get();

  Buzzer(const Buzzer&) = delete;
  Buzzer& operator=(const Buzzer&) = delete;

  /// Play sound or stop playing when frequency is 0
  void play(unsigned int frequency) const;

private:
  Buzzer();
  ~Buzzer() = default;

  static constexpr int PIN{ 2 };
};