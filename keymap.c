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

#define GMMK3_EEPROM_MAGIC_VERSION 0x470A // Version tag to auto-initialize dynamic EEPROM on first boot

#ifdef VIA_ENABLE
void via_init_kb(void) {
    // If the layout version in EEPROM does not match this firmware, force dynamic_keymap_reset()
    if (eeprom_read_word((uint16_t *)VIA_EEPROM_CUSTOM_CONFIG_ADDR) != GMMK3_EEPROM_MAGIC_VERSION) {
        via_eeprom_set_valid(false);
    }
}
#endif

// Robust Fn layer state tracking across physical matrix events and QMK layer engine
static bool fn_physically_held = false;
static bool fn_layer_active    = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    fn_layer_active = (state & ((layer_state_t)1 << SHARED_FN)) != 0;
    return state;
}

static inline bool is_fn_active(void) {
    return fn_physically_held ||
           fn_layer_active ||
           layer_state_is(SHARED_FN) ||
           ((layer_state & ((layer_state_t)1 << SHARED_FN)) != 0) ||
           (get_highest_layer(layer_state | default_layer_state) == SHARED_FN);
}

// Context-Aware Key & Knob Click Handler
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Track physical Fn key (Row 9, Col 2 on 75% ISO) as well as any Fn keycodes
    if ((record->event.key.row == 9 && record->event.key.col == 2) ||
        keycode == MO(SHARED_FN) || keycode == MO(3) || keycode == MO(1)) {
        fn_physically_held = record->event.pressed;
    }

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
                if (is_fn_active()) {
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
    if (is_fn_active()) {
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

// Non-blocking RGB matrix hook: solid dim minimal backlight per active OS profile
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

    // 2. Solid dim minimal baseline color per active OS profile (night reading friendly)
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
