#pragma once

#include <Arduino.h>

class Button {
public:
  enum class Event {
    NONE,
    PRESS,
    RELEASE
  };

  Button(uint8_t pin, uint8_t mode)
    : PIN{ pin } {
    pinMode(PIN, mode);
  }

  // Monitor signal level on given pin.
  // Return Event::PRESS on first button press,
  // Event::RELEASE on button release and Event::NONE otherwise.
  [[nodiscard]] Event OnUpdate() {
    const auto level = digitalRead(PIN);
    if (!m_IsPressed && level == LOW) {
      m_IsPressed = true;
      return Event::PRESS;
    }
    if (m_IsPressed && level == HIGH) {
      m_IsPressed = false;
      return Event::RELEASE;
    }
    return Event::NONE;
  }

private:
  const uint8_t PIN;
  bool m_IsPressed{};
};