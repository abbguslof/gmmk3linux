# Glorious GMMK 3 Pro 75% ISO (WB32) - Build Configuration
# Optimized for Arch Linux, Hyprland, and Maximum Gaming/Typing Performance

BOOTMAGIC_ENABLE = yes      # Bootmagic Lite (Hold Esc on plug-in to enter bootloader)
ENCODER_ENABLE = yes        # Rotary encoder support
MOUSEKEY_ENABLE = yes       # Mouse keys suite
EXTRAKEY_ENABLE = yes       # Audio control and System control
AUDIO_ENABLE = no           # Audio output (not equipped)
CONSOLE_ENABLE = no         # Disabled for 0ms USB logging overhead
COMMAND_ENABLE = no         # Disabled for maximum scanning speed
NKRO_ENABLE = yes           # True N-Key Rollover (infinite simultaneous keys)
BACKLIGHT_ENABLE = no       # Single-color backlight disabled
RGBLIGHT_ENABLE = no        # Underglow disabled
RGB_MATRIX_ENABLE = yes     # Per-key addressable RGB Matrix enabled
DIP_SWITCH_ENABLE = no      # Disabled (3-position switch is matrix-scanned via housekeeping)

# Performance & Latency Tuning
DEBOUNCE_TYPE = asym_eager_defer_pk
FORCE_NKRO = yes

# Dynamic Keymap & VIA WebHID
VIA_ENABLE = yes
EEPROM_ENABLE = yes
