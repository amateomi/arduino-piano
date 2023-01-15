#include "logger.hpp"
#include "keyboard.hpp"
#include "buzzer.hpp"
#include "recorder.hpp"
#include "player.hpp"

enum Pins : uint8_t {
  ANALOG_KEYBOARD = A5,
  DECREASE_OCTAVE_BUTTON = 8,
  INCREASE_OCTAVE_BUTTON = 7,
  RECORDER_BUTTON = 6,
  PLAYBACK_BUTTON = 5,
  PREVIOUS_MELODY_BUTTON = 4,
  NEXT_MELODY_BUTTON = 3,
  BUZZER = 2,
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
Player* player{};

void setup() {
  log("Setup start");

  keyboard = new Keyboard{ resistors,
                           Pins::ANALOG_KEYBOARD,
                           Pins::DECREASE_OCTAVE_BUTTON,
                           Pins::INCREASE_OCTAVE_BUTTON };

  recorder = new Recorder{ Pins::RECORDER_BUTTON,
                           melodyStorage };

  player = new Player{ Pins::PLAYBACK_BUTTON,
                       Pins::PREVIOUS_MELODY_BUTTON,
                       Pins::NEXT_MELODY_BUTTON,
                       melodyStorage };

  buzzer = new Buzzer{ Pins::BUZZER };

  log("Setup end");
}

void loop() {
  keyboard->OnUpdate();
  recorder->OnUpdate(*keyboard, *buzzer);
  player->OnUpdate(*buzzer);
  buzzer->Play(keyboard->GetNote(), keyboard->GetOctave());
}