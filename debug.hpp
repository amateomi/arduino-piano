#pragma once

// #define DEBUG

constexpr int LOG_MAX_SIZE{ 256 };

#ifdef DEBUG

extern char logBuffer[LOG_MAX_SIZE];

#define LOG(...) \
  sprintf(logBuffer, __VA_ARGS__); \
  Serial.println(logBuffer)

#define SETUP() \
  Serial.begin(9600); \
  while (!Serial) {} \
  LOG("Setup finished")

#else

#define LOG(...)
#define SETUP()

#endif