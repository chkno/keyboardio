// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details


/* =================================================================================================
 *  This file sets up the following:
 *  - LED mode configuration and ordering
 *  - Macro definitions
 *  - Key mappings
 *  - Main setup and loop functions
 *  Macros must come before key mappings, so we do key mappings late.
 * ============================================================================================== */

// Standard plugins
#include <Kaleidoscope.h>
#include <Kaleidoscope-MouseKeys.h>  // for enabling mouse control in numlock mode
#include <Kaleidoscope-Macros.h>  // for making shifted numbers be macros
#include <Kaleidoscope-LEDControl.h>  // for controlling the LEDs
#include <Kaleidoscope-LEDEffect-BootGreeting.h>  // pulses the LED button for 10s upon power-on
#include <Kaleidoscope-LEDEffect-SolidColor.h>  // LED modes that set all LEDs to a single color
#include <Kaleidoscope-LEDEffect-Breathe.h>  // LED modes that make the keys "breathe"
#include <Kaleidoscope-LEDEffect-Rainbow.h> // LED mode that pulses the keys in a rainbow pattern
#include <Kaleidoscope-LED-Stalker.h>  // "plz reveal my password" mode
#include <Kaleidoscope-LED-AlphaSquare.h>  // "no really make my password super obvious" mode

// 3rd party plugins
#include <Kaleidoscope-CapsLock.h>  // "caps are locked" LED mode
#include <Kaleidoscope-LEDEffect-DigitalRain.h>  // matrix style LED mode
#include <Kaleidoscope-ModifierLayers.h>  // for changing how number & punctation keys shift


/* ------------------------------------------------------------------------------------------------
 *  LED Mode configuration
 * ---------------------------------------------------------------------------------------------- */

// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.
static kaleidoscope::plugin::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::plugin::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::plugin::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::plugin::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::plugin::LEDSolidColor solidBlue(0, 100, 130);
static kaleidoscope::plugin::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::plugin::LEDSolidColor solidViolet(130, 0, 120);

void config_and_use_LED_modes() {
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);
  AlphaSquare.color = { 0, 150, 150 };
  StalkerEffect.variant = STALKER(BlazingTrail);
  LEDOff.activate();
}

/* ------------------------------------------------------------------------------------------------
 *  Macro definitions
 * ---------------------------------------------------------------------------------------------- */

enum { ANY,        // presses a random key when the Any key is pressed
       LOCK,       // Locks the screen
     };

static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  bool toggledOn = false;
  if (keyToggledOn(keyState)) {
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);
    toggledOn = true;
  }

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey, toggledOn);
}

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case ANY:
    anyKeyMacro(keyState);
    break;

  case LOCK:
    MACRODOWN(D(LeftControl), D(LeftShift), T(Power), U(LeftShift), U(LeftControl));
    break;
  }
  return MACRO_NONE;
}


/* ------------------------------------------------------------------------------------------------
 *  Key mappings
 * ---------------------------------------------------------------------------------------------- */

// Aliases:
#define UNUSED XXX  // marks keys that are "open"

#define K_NextTrack Consumer_ScanNextTrack
#define K_PrevTrack Consumer_ScanPreviousTrack
#define K_PlayPause Consumer_PlaySlashPause
#define K_Mute Key_Mute
#define K_LeftClick Key_mouseBtnL
#define K_RightClick Key_mouseBtnR
#define K_MiddleClick Key_mouseBtnM

// Dvorak -> Qwerty
//Row 4
#define K_Backtick Key_Backtick
#define K_1 Key_1
#define K_2 Key_2
#define K_3 Key_3
#define K_4 Key_4
#define K_5 Key_5
#define K_6 Key_6
#define K_7 Key_7
#define K_8 Key_8
#define K_9 Key_9
#define K_0 Key_0
#define K_LeftBracket Key_Minus
#define K_RightBracket Key_Equals

// Row 3
#define K_Quote Key_Q
#define K_Comma Key_W
#define K_Period Key_E
#define K_P Key_R
#define K_Y Key_T
#define K_F Key_Y
#define K_G Key_U
#define K_C Key_I
#define K_R Key_O
#define K_L Key_P
#define K_Slash Key_LeftBracket
#define K_Equals Key_RightBracket
#define K_Backslash Key_Backslash

// Row 2
#define K_A Key_A
#define K_O Key_S
#define K_E Key_D
#define K_U Key_F
#define K_I Key_G
#define K_D Key_H
#define K_H Key_J
#define K_T Key_K
#define K_N Key_L
#define K_S Key_Semicolon
#define K_Minus Key_Quote

// Row 1
#define K_Semicolon Key_Z
#define K_Q Key_X
#define K_J Key_C
#define K_K Key_V
#define K_X Key_B
#define K_B Key_N
#define K_M Key_M
#define K_W Key_Comma
#define K_V Key_Period
#define K_Z Key_Slash

enum { DVORAK, SHIFTED, FUNCTION };  // layers

// *INDENT-OFF*
/* Visual layer representation template

┌───┬───┬───┬───┬───┬───┬───┐                   ┌───┬───┬───┬───┬───┬───┬───┐
│   │   │   │   │   │   │   │                   │   │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼───┼───┤
│   │   │   │   │   │   │   │                   │   │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┤   │                   │   ├───┼───┼───┼───┼───┼───┤
│   │   │   │   │   │   ├───┘                   └───┤   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┼───┐                   ┌───┼───┼───┼───┼───┼───┼───┤
│   │   │   │   │   │   │   │                   │   │   │   │   │   │   │   │
└───┴───┴───┴───┴───┼───┼───┼───┬───┐   ┌───┬───┼───┼───┼───┴───┴───┴───┴───┘
                    │   │   │   │   │   │   │   │   │   │
                    └───┴───┼───┼───┘   └───┼───┼───┴───┘
                            │   │           │   │
                            └───┘           └───┘
*/

/* Layout template:
(___, ___, ___, ___, ___, ___, ___,
 ___, ___, ___, ___, ___, ___, ___,
 ___, ___, ___, ___, ___, ___,
 ___, ___, ___, ___, ___, ___, ___,
 ___, ___, ___, ___,
 ___,

 ___, ___, ___, ___, ___, ___, ___,
 ___, ___, ___, ___, ___, ___, ___,
      ___, ___, ___, ___, ___, ___,
 ___, ___, ___, ___, ___, ___, ___,
 ___, ___, ___, ___,
 ___)
 */

KEYMAPS(
  /* Dvorak base layer

┌───┬───┬───┬───┬───┬───┬───┐                   ┌───┬───┬───┬───┬───┬───┬───┐
│Prg│   │   │   │   │   │LED│                   │Any│   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼───┼───┤
│ ! │ ' │ , │ . │ p │ y │Ply│                   │Vol│ f │ g │ c │ r │ l │ ? │
├───┼───┼───┼───┼───┼───┤Pau│                   │Up ├───┼───┼───┼───┼───┼───┤
│ " │ a │ o │ e │ u │ i ├───┘                   └───┤ d │ h │ t │ n │ s │ - │
├───┼───┼───┼───┼───┼───┼───┐                   ┌───┼───┼───┼───┼───┼───┼───┤
│ ↑ │ ; │ q │ j │ k │ x │ ← │                   │ → │ b │ m │ w │ v │ z │ ↓ │
└───┴───┴───┴───┴───┼───┼───┼───┬───┐   ┌───┬───┼───┼───┼───┴───┴───┴───┴───┘
                    │Ctl│Bsp│Shf│Alt│   │Tab│Cmd│Spc│Esc│
                    └───┴───┼───┼───┘   └───┼───┼───┴───┘
                            │Fnc│           │Ent│
                            └───┘           └───┘
  */
  [DVORAK] = KEYMAP_STACKED
  (___,             ___,          ___,      ___,       ___,  ___,  Key_LEDEffectNext,
   LSHIFT(K_1),     K_Quote,      K_Comma,  K_Period,  K_P,  K_Y,  K_PlayPause,
   LSHIFT(K_Quote), K_A,          K_O,      K_E,       K_U,  K_I,
   Key_UpArrow,     K_Semicolon,  K_Q,      K_J,       K_K,  K_X,  Key_LeftArrow,

   Key_LeftGui, Key_LeftControl, Key_LeftShift, Key_LeftAlt,
   ShiftToLayer(FUNCTION),

   M(ANY),          ___,  ___,  ___,  ___,  ___,  ___,
   Key_VolumeUp,    K_F,  K_G,  K_C,  K_R,  K_L,  LSHIFT(K_Slash),
                    K_D,  K_H,  K_T,  K_N,  K_S,  K_Minus,
   Key_RightArrow,  K_B,  K_M,  K_W,  K_V,  K_Z,  Key_DownArrow,

   Key_Tab, Key_Backspace, Key_Spacebar, Key_Escape,
   Key_Enter),

  /* Shifted layer
┌───┬───┬───┬───┬───┬───┬───┐                   ┌───┬───┬───┬───┬───┬───┬───┐
│Prg│   │   │   │   │   │LED│                   │Any│   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼───┼───┤
│ ! │ ' │ , │ . │ P │ Y │Prv│                   │Mut│ F │ G │ C │ R │ L │ ? │
├───┼───┼───┼───┼───┼───┤Trk│                   │   ├───┼───┼───┼───┼───┼───┤
│ " │ A │ O │ E │ U │ I ├───┘                   └───┤ D │ H │ T │ N │ S │ - │
├───┼───┼───┼───┼───┼───┼───┐                   ┌───┼───┼───┼───┼───┼───┼───┤
│ ↑ │ ; │ Q │ J │ K │ X │ ← │                   │ → │ B │ M │ W │ V │ Z │ ↓ │
└───┴───┴───┴───┴───┼───┼───┼───┬───┐   ┌───┬───┼───┼───┼───┴───┴───┴───┴───┘
                    │Cmd│Ctl│Shf│Alt│   │Tab│Bsp│Spc│Esc│
                    └───┴───┼───┼───┘   └───┼───┼───┴───┘
                            │Fnc│           │Ent│
                            └───┘           └───┘
  */
  [SHIFTED] = KEYMAP_STACKED
  (___, ___,         ___,           ___,      ___, ___, Key_LEDEffectPrevious,
   ___, K_Quote,     K_Comma,       K_Period, ___, ___, K_PrevTrack,
   ___, ___,         ___,           ___,      ___, ___,
   ___, K_Semicolon, ___,           ___,      ___, ___, ___,

   ___, ___, ___, ___,
   ___,

   ___,    ___, ___, ___, ___, ___, ___,
   K_Mute, ___, ___, ___, ___, ___, ___,
           ___, ___, ___, ___, ___, K_Minus,
   ___,    ___, ___, ___, ___, ___, ___,

   ___, ___, ___, ___,
   ___),

  /* Right function layer
┌───┬───┬───┬───┬───┬───┬───┐                   ┌───┬───┬───┬───┬───┬───┬───┐
│Pow│   │   │   │   │   │Lck│                   │Any│   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼───┼───┤
│ ~ │ & │ < │ / │ [ │ { │Nxt│                   │Vol│ } │ ] │ \ │ > │ | │ @ │
├───┼───┼───┼───┼───┼───┤Trk│                   │Dn ├───┼───┼───┼───┼───┼───┤
│ ` │ # │ ^ │ % │ : │ ( ├───┘                   └───┤ ) │ = │ + │ $ │ * │ _ │
├───┼───┼───┼───┼───┼───┼───┐                   ┌───┼───┼───┼───┼───┼───┼───┤
│ ↑ │ 1 │ 2 │ 3 │ 4 │ 5 │ ← │                   │ → │ 6 │ 7 │ 8 │ 9 │ 0 │ ↓ │
└───┴───┴───┴───┴───┼───┼───┼───┬───┐   ┌───┬───┼───┼───┼───┴───┴───┴───┴───┘
                    │Cmd│Ctl│Clk│Alt│   │Tab│Del│Spc│Esc│
                    └───┴───┼───┼───┘   └───┼───┼───┴───┘
                            │Fnc│           │Ent│
                            └───┘           └───┘
  */
  [FUNCTION] =  KEYMAP_STACKED
  (Key_Power,          ___,         ___,             ___,         ___,                 ___,                   M(LOCK),
   LSHIFT(K_Backtick), LSHIFT(K_7), LSHIFT(K_Comma), K_Slash,     K_LeftBracket,       LSHIFT(K_LeftBracket), K_NextTrack,
   K_Backtick,         LSHIFT(K_3), LSHIFT(K_6),     LSHIFT(K_5), LSHIFT(K_Semicolon), LSHIFT(K_9),
   ___,                K_1,         K_2,             K_3,         K_4,                 K_5,                   ___,

   ___, ___, Key_CapsLock, ___,
   ShiftToLayer(FUNCTION),

   ___,             ___,                    ___,            ___,              ___,              ___,                 ___,
   Key_VolumeDown,  LSHIFT(K_RightBracket), K_RightBracket, K_Backslash,      LSHIFT(K_Period), LSHIFT(K_Backslash), LSHIFT(K_2),
                    LSHIFT(Key_0),          K_Equals,       LSHIFT(K_Equals), LSHIFT(K_4),      LSHIFT(K_8),         LSHIFT(K_Minus),
   ___,             K_6,                    K_7,            K_8,              K_9,              K_0,                 ___,

   ___, Key_Delete, ___, ___,
   ___)
};
// *INDENT-ON*

// Allows us to modify what happens when shift is pressed:
static const kaleidoscope::ModifierLayers::overlay_t overlays[] = {
  {LAYER_MODIFIER_KEY(Key_LeftShift) | LAYER_MODIFIER_KEY(Key_RightShift), DVORAK, SHIFTED},
  {0, 0, 0}
)

/* ------------------------------------------------------------------------------------------------
 *  Main setup & loop functions
 * ---------------------------------------------------------------------------------------------- */

KALEIDOSCOPE_INIT_PLUGINS(
  ModifierLayers,
  Macros,
  MouseKeys,
  CapsLock,
  BootGreetingEffect,
  LEDControl,
  LEDOff,
  LEDRainbowWaveEffect,
  LEDDigitalRainEffect,
  solidRed, solidOrange, solidYellow, solidGreen, solidBlue, solidIndigo, solidViolet,
  StalkerEffect,
  AlphaSquareEffect,
  LEDRainbowEffect,
  LEDBreatheEffect
);

void setup() {
  Kaleidoscope.setup();

  ModifierLayers.overlays = overlays;
  config_and_use_LED_modes();

  CapsLock.color = CRGB(0, 0, 255);
}

void loop() {
  Kaleidoscope.loop();
}
