#include "button.hpp"

Button::Button(uint8_t pin, uint8_t mode)
  : PIN(pin) {
  pinMode(PIN, mode);
}

Button::Event Button::OnUpdate() {
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