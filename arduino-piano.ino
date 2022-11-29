#define DEBUG

#ifdef DEBUG
char logBuffer[256];
#define LOG(...) \
  sprintf(logBuffer, __VA_ARGS__); \
  Serial.println(logBuffer);
#else
#define LOG(...)
#endif

constexpr auto KEYBOARD_PIN = A5;
constexpr auto LOWER_OCTAVE_PIN = 8;
constexpr auto UPPER_OCTAVE_PIN = 7;
constexpr auto BUZZER_PIN = 2;

enum class Note {
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
  pinMode(KEYBOARD_PIN, INPUT);
  pinMode(LOWER_OCTAVE_PIN, INPUT_PULLUP);
  pinMode(UPPER_OCTAVE_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  const auto currentOctave = handleOctaveSwitch();
  handleKeyboardPlay(currentOctave);
}

// Octave switch block

constexpr auto LOWEST_OCTAVE = -3;
constexpr auto HIGHEST_OCTAVE = 3;

int handleOctaveSwitch() {
  static auto currentOctave = 0;

  static auto isLowerButtonPressed = false;
  static auto isUpperButtonPressed = false;

  // Handle lower button
  if (digitalRead(LOWER_OCTAVE_PIN) == LOW && !isLowerButtonPressed) {
    isLowerButtonPressed = true;
    if (currentOctave != LOWEST_OCTAVE)
      --currentOctave;
    LOG("Lower button is pressed, current octave is %i", currentOctave)
  } else if (digitalRead(LOWER_OCTAVE_PIN) == HIGH && isLowerButtonPressed) {
    isLowerButtonPressed = false;
    LOG("Lower button is released, current octave is %i", currentOctave)
  }

  // Handle upper button
  if (digitalRead(UPPER_OCTAVE_PIN) == LOW && !isUpperButtonPressed) {
    isUpperButtonPressed = true;
    if (currentOctave != HIGHEST_OCTAVE)
      ++currentOctave;
    LOG("Upper button is pressed, current octave is %i", currentOctave)
  } else if (digitalRead(UPPER_OCTAVE_PIN) == HIGH && isUpperButtonPressed) {
    isUpperButtonPressed = false;
    LOG("Upper button is released, current octave is %i", currentOctave)
  }

  return currentOctave;
}

void handleKeyboardPlay(int currentOctave) {
  const auto voltage = analogRead(KEYBOARD_PIN);
  LOG("Analog input is %i", voltage);
  if (const auto note = voltageToNote(voltage);
      note != Note::NOT_NOTE) {
    const auto frequency = noteToFrequency(note, currentOctave);
    LOG("Frequency to play is %u", frequency);
    tone(BUZZER_PIN, frequency);
  } else
    noTone(BUZZER_PIN);
}

Note voltageToNote(int voltage) {
  if (voltage < 10)
    return Note::NOT_NOTE;

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

unsigned int noteToFrequency(Note note, int currentOctave) {
  if (currentOctave < 0)
    return static_cast<unsigned int>(note) >> abs(currentOctave);
  return static_cast<unsigned int>(note) << currentOctave;
}