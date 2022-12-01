#pragma once

#define DEBUG

#ifdef DEBUG

constexpr int LOG_MAX_LENGTH{ 256 };
inline char logBuffer[LOG_MAX_LENGTH];

/// Printf-like logger
#define LOG(...) \
  sprintf(logBuffer, __VA_ARGS__); \
  Serial.println(logBuffer)

/// Wait for Arduino connection to computer
#define SETUP() \
  while (!Serial) {} \
  LOG("Setup finished")

#else

#define LOG(...)
#define SETUP()

#endif

/// Used in update functions with buttons to set action on press and release
#define PUSH_BUTTON_HANDLER(pin, isPressed, pressCallback, releaseCallback) \
  if (const int buttonStatus = digitalRead(pin); \
      buttonStatus == LOW && !isPressed) { \
    isPressed = true; \
    pressCallback; \
  } else if (buttonStatus == HIGH && isPressed) { \
    isPressed = false; \
    releaseCallback; \
  }