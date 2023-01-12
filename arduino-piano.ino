#include "notes.hpp"
#include "keyboard.hpp"

Keyboard* keyboard{};

void setup() {
  Keyboard::Resistors resistors{ 10000, 560, 1300, 2700, 3900, 5600, 7500, 10000 };
  keyboard = new Keyboard{ A5, 8, 7, resistors };
}

void loop() {
}