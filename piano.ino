enum class Notes {
  C4 = 262,
  D4 = 294,
  E4 = 330,
  F4 = 349,
  G4 = 392,
  A4 = 440,
  B4 = 494,
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  int analogInput = analogRead(A0);
  
  if (int note = getNote(analogInput); note != -1) {
    tone(7, note);
  } else {
    noTone(7);
  }
}

/// Return frequency to play or -1 when no pressed buttons
int getNote(int analogInput) {
  if (analogInput < 60) {
    return static_cast<int>(Notes::C4);
  }
  if (analogInput < 130) {
    return static_cast<int>(Notes::D4);
  }
  if (analogInput < 230) {
    return static_cast<int>(Notes::E4);
  }
  if (analogInput < 300) {
    return static_cast<int>(Notes::F4);
  }
  if (analogInput < 380) {
    return static_cast<int>(Notes::G4);
  }
  if (analogInput < 450) {
    return static_cast<int>(Notes::A4);
  }
  if (analogInput < 470) {
    return static_cast<int>(Notes::B4);
  }
  if (analogInput < 530) {
    return static_cast<int>(Notes::C4) * 2;
  }
  return -1;
}
