#pragma once

// Middle octave note frequencies
enum class Note {
  NONE = 0,
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

constexpr auto NOTES_AMOUNT = 12;