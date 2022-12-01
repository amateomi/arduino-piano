#include "utility.hpp"
#include "keyboard.hpp"
#include "buzzer.hpp"
#include "recorder.hpp"
#include "record_player.hpp"

Keyboard* keyboard{};
Buzzer* buzzer{};
Recorder* recorder{};
RecordPlayer* recordPlayer{};

void setup() {
  Serial.begin(9600);
  SETUP();
  keyboard = new Keyboard;
  buzzer = new Buzzer;
  recorder = new Recorder;
  recordPlayer = new RecordPlayer;
}

void loop() {
  keyboard->updateCurrentOctave();
  const unsigned int frequency = keyboard->getNoteFrequency();
  recorder->updateRecordingState(frequency);
  recordPlayer->updateCurrentMelody();
  recordPlayer->updatePlaybackState(*buzzer);
  buzzer->play(frequency);
}