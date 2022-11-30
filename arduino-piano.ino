#include "debug.hpp"
#include "keyboard.hpp"
#include "buzzer.hpp"
#include "music-player.hpp"

Keyboard* keyboard{};
Buzzer* buzzer{};
MusicPlayer* musicPlayer{};

void setup() {
  SETUP();
  keyboard = new Keyboard;
  buzzer = new Buzzer;
  musicPlayer = new MusicPlayer;
}

void loop() {
  keyboard->update();
  musicPlayer->update();
  const unsigned int frequency = keyboard->getFrequency();
  if (musicPlayer->isRecording())
    musicPlayer->appendSound(frequency);
  else if (musicPlayer->isPlayback())
    musicPlayer->playback(*buzzer);
  buzzer->play(frequency);
}