#include "utility.hpp"
#include "keyboard.hpp"
#include "recorder.hpp"
#include "record_player.hpp"
#include "buzzer.hpp"

Keyboard* keyboard{};
Buzzer* buzzer{};
Recorder* recorder{};
RecordPlayer* recordPlayer{};

void setup() {
  SETUP();
  keyboard = new Keyboard;
  recorder = new Recorder;
  recordPlayer = new RecordPlayer;
  buzzer = new Buzzer;
}

void loop() {
  keyboard->updateCurrentOctave();
  const unsigned int frequency = keyboard->getNoteFrequency();
  recorder->updateRecordingState(*buzzer, frequency);
  recordPlayer->updateCurrentMelody();
  recordPlayer->updatePlaybackState(*buzzer);
  buzzer->play(frequency);
}