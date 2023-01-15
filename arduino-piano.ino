#include "logger.hpp"
#include "keyboard.hpp"
#include "buzzer.hpp"
#include "recorder.hpp"

enum Pins : uint8_t {
  ANALOG_KEYBOARD = A5,
  DECREASE_OCTAVE_BUTTON = 8,
  INCREASE_OCTAVE_BUTTON = 7,
  BUZZER = 2,
  RECORDER_BUTTON = 6,
};

const Resistors resistors{ .R1 = 10000,
                           .R2 = 560,
                           .R3 = 1300,
                           .R4 = 2700,
                           .R5 = 3900,
                           .R6 = 5600,
                           .R7 = 7500,
                           .R8 = 10000 };

MelodyStorage melodyStorage;

Keyboard* keyboard{};
Buzzer* buzzer{};
Recorder* recorder{};

void setup() {
  log("Setup start");

  keyboard = new Keyboard{ resistors,
                           Pins::ANALOG_KEYBOARD,
                           Pins::DECREASE_OCTAVE_BUTTON,
                           Pins::INCREASE_OCTAVE_BUTTON };

  buzzer = new Buzzer{ Pins::BUZZER };

  recorder = new Recorder{ Pins::RECORDER_BUTTON,
                           melodyStorage,
                           *keyboard,
                           *buzzer };

  log("Setup end");
}

void loop() {
  keyboard->OnUpdate();
  recorder->OnUpdate();
  buzzer->Play(keyboard->GetNote(), keyboard->GetOctave());
}