#include "debug.hpp"
#include "keyboard.hpp"
#include "buzzer.hpp"

Keyboard* keyboard{};
Buzzer* buzzer{};

void setup() {
  SETUP();
  keyboard = new Keyboard;
  buzzer = new Buzzer;
}

void loop() {
  keyboard->update();
  const unsigned int frequency = keyboard->getFrequency();
  buzzer->play(frequency);
}