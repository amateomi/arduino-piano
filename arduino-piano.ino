#define DEBUG

#ifdef DEBUG
char logBuffer[256];
#define LOG(...) \
  sprintf(logBuffer, __VA_ARGS__); \
  Serial.println(logBuffer);
#else
#define LOG(...)
#endif


constexpr auto keyboardPin = A5;
constexpr auto buzzerPin = 2;

enum class Note : unsigned {
  NOT_NOTE,
  C4 = 262,
  C4_SHARP = 277,
  D4 = 294,
  D4_SHARP = 311,
  E4 = 330,
  F4 = 349,
  F4_SHARP = 370,
  G4 = 392,
  G4_SHARP = 415,
  A4 = 440,
  A4_SHARP = 466,
  B4 = 494,
};

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  // Wait until connected to PC
  while (!Serial) {}
  LOG("Setup finished");
#endif
}

void loop() {
  int voltage = analogRead(keyboardPin);
  LOG("Analog input is %i", voltage);
  if (auto note = getNote(voltage); note != Note::NOT_NOTE) {
    auto frequency = static_cast<unsigned>(note);
    tone(buzzerPin, frequency);
  } else {
    noTone(buzzerPin);
  }
}

/// Return frequency to play or -1 when no pressed buttons
Note getNote(int voltage) {
  if (voltage < 38)
    return Note::C4_SHARP;

  if (voltage < 55)
    return Note::C4;

  if (voltage < 84)
    return Note::D4_SHARP;

  if (voltage < 120)
    return Note::D4;

  if (voltage < 196)
    return Note::F4_SHARP;

  if (voltage < 225)
    return Note::E4;

  if (voltage < 259)
    return Note::G4_SHARP;

  if (voltage < 296)
    return Note::F4;

  if (voltage < 322)
    return Note::A4_SHARP;

  if (voltage < 382)
    return Note::G4;

  if (voltage < 464)
    return Note::A4;

  if (voltage < 535)
    return Note::B4;

  return Note::NOT_NOTE;
}