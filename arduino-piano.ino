#include "utility.hpp"
#include "keyboard.hpp"
#include "recorder.hpp"
#include "record_player.hpp"
#include "buzzer.hpp"

void setup() {
  Serial.begin(9600);
  SETUP();
}

void loop() {
  Keyboard::get().updateCurrentOctave();
  const unsigned int frequency = Keyboard::get().getNoteFrequency();
  Recorder::get().updateRecordingState(frequency);
  RecordPlayer::get().updateCurrentMelody();
  RecordPlayer::get().updatePlaybackState();
  Buzzer::get().play(frequency);
}