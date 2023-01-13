#pragma once

#include <Arduino.h>

inline bool wasSetup = false;
inline char buffer[256];

template<typename... Args>
void log(Args... args) {
  if (!wasSetup) {
    Serial.begin(19200);
    while (!Serial) {}
    wasSetup = true;
  }
  sprintf(buffer, args...);
  Serial.println(buffer);
}