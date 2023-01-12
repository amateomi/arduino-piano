#pragma once

#include <Arduino.h>

class Button {
public:
  enum class Event {
    NONE,
    PRESS,
    RELEASE
  };

  Button(uint8_t pin, uint8_t pinMode);

  // Monitor signal level on given pin.
  // Return Event::PRESS on first button press,
  // Event::RELEASE on button release and Event::NONE otherwise.
  [[nodiscard]] Event OnUpdate();

private:
  const uint8_t PIN;
  bool m_IsPressed{};
};