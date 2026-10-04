/* Copyright 2026 gulo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see .
 */

#include QMK_KEYBOARD_H
#include "keymap_swedish.h"

/*
 * GMMK 3 Pro 75% - 3 Hardware Profiles via Physical Rear Slider (Matrix Matrix Col 7):
 *   Position 1 (Matrix 11,7): Arch Linux (Flashes Cyan)   -> Caps Lock = · (middle dot)
 *   Position 2 (Matrix 12,7): macOS      (Flashes White)  -> Left Option & Command swapped
 *   Position 3 (Matrix 13,7): Windows    (Flashes Purple) -> Standard Windows ISO
 *
 * Rotary Knob Mappings:
 * ┌───────────────┬──────────────────────────────────────┬────────────────────────────────────────┐
 * │ Modifier      │ Fn Held (Mouse Emulation Suite)      │ Normal (Code & Text Manipulation)      │
 * ├───────────────┼──────────────────────────────────────┼────────────────────────────────────────┤
 * │ None (Turn)   │ Vertical Mouse Movement (Up / Down)  │ Move Lines Up / Down (Alt + Up / Down) │
 * │ Shift + Turn  │ Horizontal Mouse Move (Left / Right) │ Scrub Undo / Redo (Ctrl+Z / Ctrl+Y)    │
 * │ Ctrl + Turn   │ Native Scroll Wheel (WhDn / WhUp)    │ Universal Zoom In / Out (Ctrl+/-)      │
 * │ Alt + Turn    │ Slow Fine-Scroll / Micro Wheel       │ Word Token Jump (Ctrl+Right / Left)    │
 * │ Knob Press    │ Mouse Middle Click (KC_MS_BTN3)      │ Hardware Pause / Break (KC_PAUS)       │
 * └───────────────┴──────────────────────────────────────┴────────────────────────────────────────┘
 *
 * Layer 0: Arch Linux Swedish Base Layer
 * ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐    ┌───┐
 * │Esc││F1 │F2 │F3 │F4 ││F5 │F6 │F7 │F8 ││F9 │F10│F11│F12│    │Pau│ (Knob Press)
 * └───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘    └───┘
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │ § │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ + │ ´ │ Backsp│Del│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ Å │ ¨ │     │PgU│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐ Ent├───┤
 * │  ·   │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ö │ Ä │ ' │    │PgD│
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
 * │Shft│ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ - │Shift │ ↑ │End│
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 * │Ctrl│Super│Alt│         Space          │AltG│ Fn │ │ ← │ ↓ │ → │
 * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
 *
 * Layer 1: macOS Base Layer (Swapped Option / Command)
 * ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐    ┌───┐
 * │Esc││F1 │F2 │F3 │F4 ││F5 │F6 │F7 │F8 ││F9 │F10│F11│F12│    │Pau│ (Knob Press)
 * └───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘    └───┘
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │ § │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ + │ ´ │ Backsp│Del│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ Å │ ¨ │     │PgU│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐ Ent├───┤
 * │CapsLk│ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ö │ Ä │ ' │    │PgD│
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
 * │Shft│ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ - │Shift │ ↑ │End│
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 * │Ctrl│ Opt │Cmd│         Space          │Cmd │ Fn │ │ ← │ ↓ │ → │
 * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
 *
 * Layer 2: Windows Base Layer
 * ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐    ┌───┐
 * │Esc││F1 │F2 │F3 │F4 ││F5 │F6 │F7 │F8 ││F9 │F10│F11│F12│    │Pau│ (Knob Press)
 * └───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘    └───┘
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │ § │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ + │ ´ │ Backsp│Del│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ Å │ ¨ │     │PgU│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐ Ent├───┤
 * │CapsLk│ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ö │ Ä │ ' │    │PgD│
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
 * │Shft│ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ - │Shift │ ↑ │End│
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 * │Ctrl│ Win │Alt│         Space          │AltG│ Fn │ │ ← │ ↓ │ → │
 * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
 *
 * Layer 3: Fn Function Layer (Media, Navigation, Coding & RGB)
 * ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐    ┌───┐
 * │RST││MyC│Hom│Cal│Sel││Prv│Nxt│Ply│Stp││Mut│Vo-│Vo+│PSc│    │M3 │ (Knob Press)
 * └───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘    └───┘
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │   │   │   │   │   │   │   │ { │ [ │ ] │ } │ \ │   │EE_CLR │Ins│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │RTOG │   │   │   │   │   │   │Hom│ ↑ │End│   │   │ ~ │     │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
 * │CapsLk│   │   │   │   │   │ ← │ ↓ │ ↑ │ → │   │   │   │    │   │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
 * │    │ | │SAD│SAI│SPD│SPI│   │   │   │   │   │   │      │VAI│   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 * │    │GUI │   │         Play/Pause      │    │    │ │RMOD│VAD│MOD│
 * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
 */

enum custom_layers {
    PROF_LINUX,   // 0: Linux (Position 1)
    PROF_MAC,     // 1: macOS (Position 2)
    PROF_WIN,     // 2: Windows (Position 3)
    SHARED_FN     // 3: Fn Layer
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Profile 1: Arch Linux (Caps is ·) */
    [PROF_LINUX] = LAYOUT(
        KC_ESC,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PAUS,
        SE_HALF,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SE_PLUS, SE_ACUT, KC_BSPC,  KC_DEL,
        KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    SE_ARNG, SE_DIAE,            KC_PGUP,
        RALT(KC_DOT),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    SE_ODIA, SE_ADIA, SE_QUOT, KC_ENT,   KC_PGDN,
        KC_LSFT,       KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  SE_MINS, KC_RSFT, KC_UP,    KC_END,
        KC_LCTL,       KC_LGUI, KC_LALT,                         KC_SPC,                   KC_ALGR, MO(SHARED_FN),    KC_LEFT, KC_DOWN,  KC_RGHT
    ),

    /* Profile 2: macOS (Left Option / Command swapped) */
    [PROF_MAC] = LAYOUT(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PAUS,
        SE_HALF,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SE_PLUS, SE_ACUT, KC_BSPC,  KC_DEL,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    SE_ARNG, SE_DIAE,            KC_PGUP,
        KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    SE_ODIA, SE_ADIA, SE_QUOT, KC_ENT,   KC_PGDN,
        KC_LSFT,  KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  SE_MINS, KC_RSFT, KC_UP,    KC_END,
        KC_LCTL,  KC_LOPT, KC_LCMD,                         KC_SPC,                   KC_RCMD, MO(SHARED_FN),    KC_LEFT, KC_DOWN,  KC_RGHT
    ),

    /* Profile 3: Standard Windows */
    [PROF_WIN] = LAYOUT(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PAUS,
        SE_HALF,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SE_PLUS, SE_ACUT, KC_BSPC,  KC_DEL,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    SE_ARNG, SE_DIAE,            KC_PGUP,
        KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    SE_ODIA, SE_ADIA, SE_QUOT, KC_ENT,   KC_PGDN,
        KC_LSFT,  KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  SE_MINS, KC_RSFT, KC_UP,    KC_END,
        KC_LCTL,  KC_LGUI, KC_LALT,                         KC_SPC,                   KC_ALGR, MO(SHARED_FN),    KC_LEFT, KC_DOWN,  KC_RGHT
    ),

    /* Universal Fn Layer */
    [SHARED_FN] = LAYOUT(
        QK_BOOT,  KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, KC_PSCR,           KC_MS_BTN3,
        _______,  _______, _______, _______, _______, _______, _______, SE_LCBR, SE_LBRC, SE_RBRC, SE_RCBR, SE_BSLS, _______, EE_CLR,   KC_INS,
        RGB_TOG,  _______, _______, _______, _______, _______, _______, KC_HOME, KC_UP,   KC_END,  _______, _______, SE_TILD,          _______,
        KC_CAPS,  _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______, _______,  _______,
        _______,  SE_PIPE, RGB_SAD, RGB_SAI, RGB_SPD, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, RGB_VAI,  _______,
        _______,  GU_TOGG, _______,                         KC_MPLY,                  _______, _______,          RGB_RMOD,RGB_VAD, RGB_MOD
    )
};

// Rotary Knob configuration
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        uint8_t mods = get_mods();

        // 1. Holding Fn: Mouse Emulation Suite
        if (layer_state_is(SHARED_FN)) {
            if (mods & MOD_MASK_SHIFT) {
                tap_code16(clockwise ? KC_MS_RIGHT : KC_MS_LEFT);
            } else if (mods & MOD_MASK_CTRL) {
                tap_code16(clockwise ? KC_MS_WH_DOWN : KC_MS_WH_UP);
            } else if (mods & MOD_MASK_ALT) {
                tap_code16(clockwise ? KC_MS_WH_DOWN : KC_MS_WH_UP);
            } else {
                tap_code16(clockwise ? KC_MS_DOWN : KC_MS_UP);
            }
        }
        // 2. Normal Modes (Fn NOT held): Code & Editing Suite
        else {
            if (mods & MOD_MASK_CTRL) {
                tap_code16(clockwise ? C(SE_PLUS) : C(SE_MINS));
            } else if (mods & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                tap_code16(clockwise ? C(KC_Y) : C(KC_Z));
                set_mods(mods);
            } else if (mods & MOD_MASK_ALT) {
                del_mods(MOD_MASK_ALT);
                tap_code16(clockwise ? C(KC_RGHT) : C(KC_LEFT));
                set_mods(mods);
            } else {
                tap_code16(clockwise ? A(KC_DOWN) : A(KC_UP));
            }
        }
    }
    return false;
}

// Visual RGB Flash state tracker
static uint16_t flash_timer = 0;
static uint8_t  flash_r = 0, flash_g = 0, flash_b = 0;

static void trigger_profile_flash(uint8_t r, uint8_t g, uint8_t b) {
    flash_r = r;
    flash_g = g;
    flash_b = b;
    flash_timer = timer_read();
}

// Active Profile switching engine based on physical switch matrix
static uint8_t current_profile = 255;
static uint16_t poll_timer = 0;

static void switch_to_profile(uint8_t prof) {
    if (current_profile == prof) return;
    current_profile = prof;

    // Turn off base layers
    layer_off(PROF_MAC);
    layer_off(PROF_WIN);

    switch (prof) {
        case 1: // Position 1: Arch Linux
            // PROF_LINUX is Layer 0 (default base)
            trigger_profile_flash(0, 255, 255);   // Cyan / Teal Flash
            break;
        case 2: // Position 2: macOS
            layer_on(PROF_MAC);
            trigger_profile_flash(255, 255, 255); // White Flash
            break;
        case 3: // Position 3: Windows
            layer_on(PROF_WIN);
            trigger_profile_flash(180, 0, 255);   // Purple Flash
            break;
    }
}

// Poll physical matrix state with zero overhead
void housekeeping_task_user(void) {
    if (timer_elapsed(poll_timer) > 25) {
        poll_timer = timer_read();

        // Check Column 7 (bit 0x80) on Rows 11, 12, and 13
        if (matrix_get_row(11) & 0x80) {
            switch_to_profile(1);
        } else if (matrix_get_row(12) & 0x80) {
            switch_to_profile(2);
        } else if (matrix_get_row(13) & 0x80) {
            switch_to_profile(3);
        }
    }
}

// Initialize correct profile on startup
void keyboard_post_init_user(void) {
    // Delay check slightly to let matrix scanning stabilize
    poll_timer = timer_read();
}

// Non-blocking RGB matrix hook to render visual flash over animations
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (flash_timer != 0) {
        if (timer_elapsed(flash_timer) < 600) {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, flash_r, flash_g, flash_b);
            }
            return false;
        } else {
            flash_timer = 0; // Flash complete
        }
    }
    return true;
}
