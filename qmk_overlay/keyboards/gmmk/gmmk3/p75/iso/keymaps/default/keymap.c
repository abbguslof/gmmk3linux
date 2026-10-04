/* Copyright 2026 gulo
 *
 * GMMK 3 Pro 75% ISO (WB32FQ95) - Multi-OS Adaptive Firmware
 * Optimized for Arch Linux (Hyprland), macOS, and Windows
 */

#include QMK_KEYBOARD_H
#include "keymap_swedish.h"
#ifdef VIA_ENABLE
#    include "via.h"
#endif

/*
 * GMMK 3 Pro 75% - 3 Hardware Profiles via Physical Rear Slider (Matrix Column 7):
 *   Position 1 (Matrix [11, 7]): Arch Linux (Flashes Cyan)   -> Caps Lock = · (middle dot)
 *   Position 2 (Matrix [12, 7]): macOS      (Flashes White)  -> Left Option & Command swapped
 *   Position 3 (Matrix [13, 7]): Windows    (Flashes Purple) -> Standard Windows ISO
 *
 * Context-Aware Rotary Encoder & Knob Switch Matrix:
 * ┌─────────────────┬──────────────────────┬────────────────────────┬────────────────────────┐
 * │ Modifier State  │ Turn CCW             │ Turn CW                │ Knob Press (Click)     │
 * ├─────────────────┼──────────────────────┼────────────────────────┼────────────────────────┤
 * │ Default (None)  │ Step Back (Left Arr) │ Step Fwd (Right Arr)   │ Mic Mute / Pause (PAUS)│
 * │ Shift           │ Undo (Ctrl+Z/Cmd+Z)  │ Redo (Ctrl+Y/Cmd+S+Z)  │ Save File (Ctrl+S/CmdS)│
 * │ Ctrl            │ Zoom Out (Ctrl/Cmd -)│ Zoom In (Ctrl/Cmd +)   │ Reset Zoom 100% (C/G 0)│
 * │ Alt             │ Prev Word (Ctrl/OptL)│ Next Word (Ctrl/Opt R) │ Select Word (Ctrl/CmdD)│
 * │ Shift + Alt     │ Prev Tab (C+S+Tab)   │ Next Tab (Ctrl+Tab)    │ Close Tab (Ctrl/Cmd W) │
 * │ Super (GUI)     │ Focus Left (Super+←) │ Focus Right (Super+→)  │ Close Window (Super+W) │
 * │                 │ (macOS: Cmd+S+Tab)   │ (macOS: Cmd+Tab)       │ (macOS: Cmd+Q)         │
 * │                 │ (Win: Alt+S+Tab)     │ (Win: Alt+Tab)         │ (Win: Alt+F4)          │
 * ├─────────────────┼──────────────────────┼────────────────────────┼────────────────────────┤
 * │ Fn (Mouse Mode) │ Cursor Up (MS_UP)    │ Cursor Down (MS_DOWN)  │ Mouse Left Click (BTN1)│
 * │ Fn + Shift      │ Cursor Left (MS_LEFT)│ Cursor Right (MS_RIGHT)│ Mouse Right Click(BTN2)│
 * │ Fn + Alt        │ Wh Scroll Left       │ Wh Scroll Right        │ Mouse Mid Click (BTN3) │
 * └─────────────────┴──────────────────────┴────────────────────────┴────────────────────────┘
 */

enum custom_layers {
    PROF_LINUX,   // 0: Arch Linux Base (Position 1)
    PROF_MAC,     // 1: macOS Base (Position 2)
    PROF_WIN,     // 2: Windows Base (Position 3)
    SHARED_FN     // 3: Function Layer
};

enum custom_keycodes {
    KNOB_CLICK = SAFE_RANGE,
    FN_SLEP,      // Universal OS sleep key (Fn + Del)
};

// Physical LED index mapping for GMMK 3 Pro 75% ISO (AW20216S matrix driver)
enum gmmk3_led_index {
    LED_ESC   = 0,
    LED_F1    = 1,
    LED_F2    = 2,
    LED_F3    = 3,
    LED_F4    = 4,
    LED_F5    = 5,
    LED_F6    = 6,
    LED_F7    = 7,
    LED_F8    = 8,
    LED_F9    = 9,
    LED_F10   = 10,
    LED_F11   = 11,
    LED_F12   = 12,

    LED_GRV   = 13, // §
    LED_1     = 14,
    LED_2     = 15,
    LED_3     = 16,
    LED_4     = 17,
    LED_5     = 18,
    LED_6     = 19,
    LED_7     = 20, // {
    LED_8     = 21, // [
    LED_9     = 22, // ]
    LED_0     = 23, // }
    LED_MINS  = 24, // Backslash key (+ key in SE)
    LED_EQL   = 25, // ´
    LED_BSPC  = 26, // Backspace (EE_CLR)
    LED_DEL   = 27, // Delete (FN_SLEP)

    LED_TAB   = 28, // RGB_TOG
    LED_Q     = 29,
    LED_W     = 30,
    LED_E     = 31,
    LED_R     = 32,
    LED_T     = 33,
    LED_Y     = 34,
    LED_U     = 35, // Home
    LED_I     = 36, // Up
    LED_O     = 37, // End
    LED_P     = 38,
    LED_ARNG  = 39,
    LED_DIAE  = 40,
    LED_HASH  = 41,
    LED_PGUP  = 42,

    LED_CAPS  = 43,
    LED_A     = 44,
    LED_S     = 45,
    LED_D     = 46,
    LED_F     = 47,
    LED_G     = 48,
    LED_H     = 49, // Vim Left
    LED_J     = 50, // Vim Down
    LED_K     = 51, // Vim Up
    LED_L     = 52, // Vim Right
    LED_SCLN  = 53,
    LED_QUOT  = 54,
    LED_ENT   = 55,
    LED_PGDN  = 56,

    LED_LSFT  = 57,
    LED_NUBS  = 58, // |
    LED_Z     = 59,
    LED_X     = 60,
    LED_C     = 61, // RGB_SAD
    LED_V     = 62, // RGB_SAI
    LED_B     = 63, // RGB_SPD
    LED_N     = 64, // RGB_SPI
    LED_M     = 65,
    LED_COMM  = 66,
    LED_DOT   = 67,
    LED_SLSH  = 68,
    LED_RSFT  = 69,
    LED_UP    = 70, // RGB_VAI
    LED_END   = 71,

    LED_LCTL  = 72,
    LED_LGUI  = 73, // GU_TOGG
    LED_LALT  = 74,
    LED_SPC   = 75, // Play/Pause
    LED_RALT  = 76,
    LED_FN    = 77,
    LED_LEFT  = 78, // RGB_RMOD
    LED_DOWN  = 79, // RGB_VAD
    LED_RGHT  = 80  // RGB_MOD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Profile 1: Arch Linux (Caps Lock is Swedish Middle Dot ·) */
    [PROF_LINUX] = LAYOUT(
        KC_ESC,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KNOB_CLICK,
        SE_HALF,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SE_PLUS, SE_ACUT, KC_BSPC,  KC_DEL,
        KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    SE_ARNG, SE_DIAE,            KC_PGUP,
        RALT(KC_DOT),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    SE_ODIA, SE_ADIA, SE_QUOT, KC_ENT,   KC_PGDN,
        KC_LSFT,       KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  SE_MINS, KC_RSFT, KC_UP,    KC_END,
        KC_LCTL,       KC_LGUI, KC_LALT,                         KC_SPC,                   KC_ALGR, MO(SHARED_FN),    KC_LEFT, KC_DOWN,  KC_RGHT
    ),

    /* Profile 2: macOS (Left Option / Command swapped for Mac layout) */
    [PROF_MAC] = LAYOUT(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KNOB_CLICK,
        SE_HALF,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SE_PLUS, SE_ACUT, KC_BSPC,  KC_DEL,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    SE_ARNG, SE_DIAE,            KC_PGUP,
        KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    SE_ODIA, SE_ADIA, SE_QUOT, KC_ENT,   KC_PGDN,
        KC_LSFT,  KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  SE_MINS, KC_RSFT, KC_UP,    KC_END,
        KC_LCTL,  KC_LOPT, KC_LCMD,                         KC_SPC,                   KC_RCMD, MO(SHARED_FN),    KC_LEFT, KC_DOWN,  KC_RGHT
    ),

    /* Profile 3: Standard Windows */
    [PROF_WIN] = LAYOUT(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KNOB_CLICK,
        SE_HALF,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SE_PLUS, SE_ACUT, KC_BSPC,  KC_DEL,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    SE_ARNG, SE_DIAE,            KC_PGUP,
        KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    SE_ODIA, SE_ADIA, SE_QUOT, KC_ENT,   KC_PGDN,
        KC_LSFT,  KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  SE_MINS, KC_RSFT, KC_UP,    KC_END,
        KC_LCTL,  KC_LGUI, KC_LALT,                         KC_SPC,                   KC_ALGR, MO(SHARED_FN),    KC_LEFT, KC_DOWN,  KC_RGHT
    ),

    /* Universal Fn Layer */
    [SHARED_FN] = LAYOUT(
        QK_BOOT,  KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, KC_PSCR,           KNOB_CLICK,
        _______,  _______, _______, _______, _______, _______, _______, SE_LCBR, SE_LBRC, SE_RBRC, SE_RCBR, SE_BSLS, _______, EE_CLR,   FN_SLEP,
        RGB_TOG,  _______, _______, _______, _______, _______, _______, KC_HOME, KC_UP,   KC_END,  _______, _______, SE_TILD,          _______,
        KC_CAPS,  _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______, _______,  _______,
        _______,  SE_PIPE, RGB_SAD, RGB_SAI, RGB_SPD, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, RGB_VAI,  _______,
        _______,  GU_TOGG, _______,                         KC_MPLY,                  _______, _______,          RGB_RMOD,RGB_VAD, RGB_MOD
    )
};

static uint8_t active_profile = 0; // Starts at 0 to guarantee initial switch_to_profile() runs

#define GMMK3_EEPROM_MAGIC_VERSION 0x4709 // Version tag to auto-initialize dynamic EEPROM on first boot

#ifdef VIA_ENABLE
void via_init_kb(void) {
    // If the layout version in EEPROM does not match this firmware, force dynamic_keymap_reset()
    if (eeprom_read_word((uint16_t *)VIA_EEPROM_CUSTOM_CONFIG_ADDR) != GMMK3_EEPROM_MAGIC_VERSION) {
        via_eeprom_set_valid(false);
    }
}
#endif

// Context-Aware Key & Knob Click Handler
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case FN_SLEP:
            if (record->event.pressed) {
                if (active_profile == 2) {
                    // macOS: Command + Option + Eject triggers immediate sleep
                    register_code(KC_LGUI);
                    register_code(KC_LALT);
                    tap_code(KC_EJCT);
                    unregister_code(KC_LALT);
                    unregister_code(KC_LGUI);
                } else {
                    // Linux & Windows: Universal System Sleep
                    tap_code16(KC_SLEP);
                }
            }
            return false;

        case KNOB_CLICK:
            if (record->event.pressed) {
                uint8_t mods = get_mods();

                // Fn Layer Active: Mouse Suite Clicks
                if (layer_state_is(SHARED_FN)) {
                    if (mods & MOD_MASK_ALT) {
                        tap_code16(KC_MS_BTN3); // Mouse Middle Click
                    } else if (mods & MOD_MASK_SHIFT) {
                        tap_code16(KC_MS_BTN2); // Mouse Right Click
                    } else {
                        tap_code16(KC_MS_BTN1); // Mouse Left Click
                    }
                    return false;
                }

                // Base Layers Active:
                // 1. Shift + Alt: Close Active Tab
                if ((mods & MOD_MASK_SHIFT) && (mods & MOD_MASK_ALT)) {
                    clear_mods();
                    send_keyboard_report();
                    if (active_profile == 2) {
                        tap_code16(G(KC_W)); // macOS Cmd + W
                    } else {
                        tap_code16(C(KC_W)); // Linux / Windows Ctrl + W
                    }
                    set_mods(mods);
                    send_keyboard_report();
                }
                // 2. Super (GUI): Kill Active Window
                else if (mods & MOD_MASK_GUI) {
                    if (active_profile == 1) {
                        // Hyprland: Super is already held; tap W sends Super + W (Omarchy killactive)
                        tap_code(KC_W);
                    } else if (active_profile == 2) {
                        // macOS: Command is held; tap Q sends Cmd + Q (Quit app)
                        tap_code(KC_Q);
                    } else {
                        // Windows: Alt + F4
                        clear_mods();
                        send_keyboard_report();
                        tap_code16(A(KC_F4));
                        set_mods(mods);
                        send_keyboard_report();
                    }
                }
                // 3. Ctrl: Reset Zoom to 100%
                else if (mods & MOD_MASK_CTRL) {
                    clear_mods();
                    send_keyboard_report();
                    if (active_profile == 2) {
                        tap_code16(G(KC_0)); // macOS Cmd + 0
                    } else {
                        tap_code16(C(KC_0)); // Linux / Windows Ctrl + 0
                    }
                    set_mods(mods);
                    send_keyboard_report();
                }
                // 4. Alt: Select Current Word / Occurrence
                else if (mods & MOD_MASK_ALT) {
                    clear_mods();
                    send_keyboard_report();
                    if (active_profile == 2) {
                        tap_code16(G(KC_D)); // macOS Cmd + D
                    } else {
                        tap_code16(C(KC_D)); // Linux / Windows Ctrl + D
                    }
                    set_mods(mods);
                    send_keyboard_report();
                }
                // 5. Shift: Save File
                else if (mods & MOD_MASK_SHIFT) {
                    clear_mods();
                    send_keyboard_report();
                    if (active_profile == 2) {
                        tap_code16(G(KC_S)); // macOS Cmd + S
                    } else {
                        tap_code16(C(KC_S)); // Linux / Windows Ctrl + S
                    }
                    set_mods(mods);
                    send_keyboard_report();
                }
                // 6. Default: Hardware Pause / Break (Hyprland mic mute hook)
                else {
                    tap_code16(KC_PAUS);
                }
            }
            return false;
    }
    return true;
}

// Context-Aware Rotary Encoder Rotation Handler
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index != 0) return false;

    uint8_t mods = get_mods();

    // 1. Fn Layer Active: Ergonomic Mouse Navigation Suite
    if (layer_state_is(SHARED_FN)) {
        if (mods & MOD_MASK_ALT) {
            // Horizontal Wheel Scrolling
            tap_code16(clockwise ? KC_MS_WH_RIGHT : KC_MS_WH_LEFT);
        } else if (mods & MOD_MASK_SHIFT) {
            // Horizontal Cursor Navigation (X-Axis)
            tap_code16(clockwise ? KC_MS_RIGHT : KC_MS_LEFT);
        } else {
            // Vertical Cursor Navigation (Y-Axis)
            tap_code16(clockwise ? KC_MS_DOWN : KC_MS_UP);
        }
        return false;
    }

    // 2. Shift + Alt: Browser & Editor Tab Management
    if ((mods & MOD_MASK_SHIFT) && (mods & MOD_MASK_ALT)) {
        clear_mods();
        send_keyboard_report();
        if (clockwise) {
            // Next Tab: Ctrl + Tab
            register_code(KC_LCTL);
            tap_code(KC_TAB);
            unregister_code(KC_LCTL);
        } else {
            // Prev Tab: Ctrl + Shift + Tab
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            tap_code(KC_TAB);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
        }
        set_mods(mods);
        send_keyboard_report();
        return false;
    }

    // 3. Super (GUI): Window Management & Focus Navigation
    if (mods & MOD_MASK_GUI) {
        if (active_profile == 1) {
            // Hyprland: Super is physically held; tap Arrow directly to trigger `SUPER, RIGHT` or `SUPER, LEFT`
            tap_code(clockwise ? KC_RGHT : KC_LEFT);
        } else if (active_profile == 2) {
            // macOS: App Switcher (Cmd + Tab / Cmd + Shift + Tab)
            if (clockwise) {
                tap_code(KC_TAB);
            } else {
                register_code(KC_LSFT);
                tap_code(KC_TAB);
                unregister_code(KC_LSFT);
            }
        } else {
            // Windows: Task Switcher (Alt + Tab / Alt + Shift + Tab)
            clear_mods();
            send_keyboard_report();
            if (clockwise) {
                register_code(KC_LALT);
                tap_code(KC_TAB);
                unregister_code(KC_LALT);
            } else {
                register_code(KC_LALT);
                register_code(KC_LSFT);
                tap_code(KC_TAB);
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
            }
            set_mods(mods);
            send_keyboard_report();
        }
        return false;
    }

    // 4. Ctrl: Universal Display & Document Zoom
    if (mods & MOD_MASK_CTRL) {
        if (active_profile == 2) {
            clear_mods();
            send_keyboard_report();
            tap_code16(clockwise ? G(SE_PLUS) : G(SE_MINS));
            set_mods(mods);
            send_keyboard_report();
        } else {
            // Ctrl is already held; send Swedish ISO plus/minus directly
            tap_code16(clockwise ? SE_PLUS : SE_MINS);
        }
        return false;
    }

    // 5. Alt: Code & Text Word/Token Jump
    if (mods & MOD_MASK_ALT) {
        if (active_profile == 2) {
            // macOS: Option is held; Option + Right / Option + Left is native word jump
            tap_code(clockwise ? KC_RGHT : KC_LEFT);
        } else {
            // Linux & Windows: Ctrl + Right / Ctrl + Left
            clear_mods();
            send_keyboard_report();
            register_code(KC_LCTL);
            tap_code(clockwise ? KC_RGHT : KC_LEFT);
            unregister_code(KC_LCTL);
            set_mods(mods);
            send_keyboard_report();
        }
        return false;
    }

    // 6. Shift: History Stepping (Undo / Redo)
    if (mods & MOD_MASK_SHIFT) {
        clear_mods();
        send_keyboard_report();
        if (active_profile == 2) {
            // macOS: Cmd + Shift + Z (Redo) / Cmd + Z (Undo)
            if (clockwise) {
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                tap_code(KC_Z);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
            } else {
                register_code(KC_LGUI);
                tap_code(KC_Z);
                unregister_code(KC_LGUI);
            }
        } else {
            // Linux & Windows: Ctrl + Y (Redo) / Ctrl + Z (Undo)
            register_code(KC_LCTL);
            tap_code(clockwise ? KC_Y : KC_Z);
            unregister_code(KC_LCTL);
        }
        set_mods(mods);
        send_keyboard_report();
        return false;
    }

    // 7. Default (Unmodified): Video / Timeline / Arrow Scrubbing
    tap_code(clockwise ? KC_RGHT : KC_LEFT);
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

static void switch_to_profile(uint8_t prof) {
    if (active_profile == prof) return;
    active_profile = prof;

    switch (prof) {
        case 1: // Position 1: Arch Linux
            default_layer_set((layer_state_t)1 << PROF_LINUX);
            trigger_profile_flash(0, 255, 255);   // Cyan / Teal Flash
            break;
        case 2: // Position 2: macOS
            default_layer_set((layer_state_t)1 << PROF_MAC);
            trigger_profile_flash(255, 255, 255); // White Flash
            break;
        case 3: // Position 3: Windows
            default_layer_set((layer_state_t)1 << PROF_WIN);
            trigger_profile_flash(180, 0, 255);   // Purple Flash
            break;
    }
}

// Non-blocking real-time matrix poller for physical rear slider switch
static uint16_t poll_timer = 0;
void housekeeping_task_user(void) {
    if (timer_elapsed(poll_timer) > 25) {
        poll_timer = timer_read();

        // Sample Column 7 (bit 0x80) on Rows 11, 12, and 13
        if (matrix_get_row(11) & 0x80) {
            switch_to_profile(1);
        } else if (matrix_get_row(12) & 0x80) {
            switch_to_profile(2);
        } else if (matrix_get_row(13) & 0x80) {
            switch_to_profile(3);
        }
    }
}

// Initialize correct profile and RGB state on startup
void keyboard_post_init_user(void) {
    poll_timer = timer_read();
    if (!rgb_matrix_is_enabled()) {
        rgb_matrix_enable_noeeprom();
    }

#ifdef VIA_ENABLE
    // Ensure EEPROM is synced to compiled flash keymaps on first boot with new layout
    if (eeprom_read_word((uint16_t *)VIA_EEPROM_CUSTOM_CONFIG_ADDR) != GMMK3_EEPROM_MAGIC_VERSION) {
        eeconfig_init_via();
        eeprom_update_word((uint16_t *)VIA_EEPROM_CUSTOM_CONFIG_ADDR, GMMK3_EEPROM_MAGIC_VERSION);
    }
#endif
}

// Non-blocking RGB matrix hook: solid dim minimal backlight with functional Fn layer map
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_is_enabled()) {
        return true;
    }

    // 1. Momentary profile confirmation flash (active for 500ms after slider change)
    if (flash_timer != 0) {
        if (timer_elapsed(flash_timer) < 500) {
            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, flash_r, flash_g, flash_b);
            }
            return false;
        } else {
            flash_timer = 0; // Flash complete, settle to ambient
        }
    }

    // 2. Functional Layer Visual Feedback (When holding Fn)
    if (layer_state_is(SHARED_FN)) {
        // Dim all non-functional keys to off/black
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0);
        }

        // --- System & Safety ---
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_ESC,  220, 20, 20);   // Bootloader (QK_BOOT) -> Red
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_DEL,  0, 160, 255);   // Built-in Sleep Button (FN_SLEP) -> Azure Blue
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_BSPC, 220, 70, 0);    // EEPROM Clear (EE_CLR) -> Orange

        // --- App Shortcuts (F1 - F4) ---
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_F1,  120, 50, 190);   // My Computer -> Soft Violet
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_F2,  120, 50, 190);   // Web Browser Home
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_F3,  120, 50, 190);   // Calculator
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_F4,  120, 50, 190);   // Media Player Select

        // --- Media Playback (F5 - F9, Space) ---
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_F5,  30, 180, 70);    // Prev Track -> Emerald Green
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_F6,  30, 180, 70);    // Next Track
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_F7,  30, 180, 70);    // Play
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_F8,  30, 180, 70);    // Stop
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_F9,  30, 180, 70);    // Mute
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_SPC, 30, 180, 70);    // Space = Play/Pause

        // --- Volume & PrintScreen (F10 - F12) ---
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_F10, 190, 130, 20);   // Volume Down -> Amber
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_F11, 190, 130, 20);   // Volume Up
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_F12, 190, 130, 20);   // PrintScreen

        // --- Programmer Brackets { [ ] } \ | ---
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_7,    0, 180, 180);   // { -> Crisp Cyan
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_8,    0, 180, 180);   // [
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_9,    0, 180, 180);   // ]
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_0,    0, 180, 180);   // }
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_MINS, 0, 180, 180);   // Backslash key 
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_NUBS, 0, 180, 180);   // |

        // --- Navigation & Vim Cursor ---
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_H,    180, 190, 220); // Vim Left -> Ice White
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_J,    180, 190, 220); // Vim Down
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_K,    180, 190, 220); // Vim Up
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_L,    180, 190, 220); // Vim Right
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_U,    140, 70, 200);  // Home -> Soft Purple
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_I,    180, 190, 220); // Up
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_O,    140, 70, 200);  // End

        // --- Hardware RGB Controls ---
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_TAB,  180, 160, 20);  // RGB_TOG -> Gold Yellow
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_Z,    180, 160, 20);  // RGB_SAD (Saturation -)
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_X,    180, 160, 20);  // RGB_SAI (Saturation +)
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_C,    180, 160, 20);  // RGB_SPD (Speed -)
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_V,    180, 160, 20);  // RGB_SPI (Speed +)
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_UP,   180, 160, 20);  // RGB_VAI (Brightness +)
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_DOWN, 180, 160, 20);  // RGB_VAD (Brightness -)
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_LEFT, 180, 160, 20);  // RGB_RMOD (Mode Prev)
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_RGHT, 180, 160, 20);  // RGB_MOD (Mode Next)

        // --- Active Modifiers / State ---
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_CAPS, 180, 180, 180); // Caps Lock
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_LGUI, 140, 50, 190);  // GU_TOGG (GUI Lock)
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_FN,   (active_profile == 1) ? 0 : ((active_profile == 2) ? 220 : 10),
                                                 (active_profile == 1) ? 220 : ((active_profile == 2) ? 220 : 80),
                                                 (active_profile == 1) ? 220 : ((active_profile == 2) ? 220 : 255));

        return false;
    }

    // 3. Solid dim minimal baseline color per active OS profile (night reading friendly)
    uint8_t base_r = 30, base_g = 32, base_b = 35; // Profile 1 (Arch Linux): Dim neutral white / grey
    if (active_profile == 2) {
        base_r = 45; base_g = 26; base_b = 8;       // Profile 2 (macOS): Dim warm amber / candlelight
    } else if (active_profile == 3) {
        base_r = 10; base_g = 25; base_b = 55;      // Profile 3 (Windows): Dim subtle deep blue
    }

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_INDICATOR_SET_COLOR(i, base_r, base_g, base_b);
    }
    return false;
}
