# GMMK 3 Linux firmware

Terms for the keyboard firmware in this repository. The vocabulary comes from QMK, USB HID, and the GMMK 3 hardware.

## Language

**Profile**:
A complete typing configuration selected by the rear slider.
_Avoid_: mode, preset

**Base layer**:
The default layer for one profile.
_Avoid_: main layer, default keymap

**Fn layer**:
The shared momentary layer that holds media, navigation, sleep, and RGB controls.
_Avoid_: function map, secondary layer

**Slider**:
The three-position switch on the rear edge of the keyboard.
_Avoid_: DIP switch, profile switch

**Matrix**:
The row and column grid that QMK scans to detect key positions.
_Avoid_: key grid, scan grid

**Column 7**:
The matrix column that carries the slider contacts.
_Avoid_: slider column, profile column

**Debounce**:
The filter that ignores contact bounce while a key settles.
_Avoid_: chatter filter, noise filter

**Eager press**:
A press reported before the debounce window finishes.
_Avoid_: instant press, zero-latency press

**Deferred release**:
A release reported only after the key has stayed released for the debounce window.
_Avoid_: delayed release, release filter

**Wake guard**:
The firmware logic that decides whether a matrix change may wake the host.
_Avoid_: wake filter, wake check

**Remote wakeup**:
The USB feature that lets a device wake a suspended host.
_Avoid_: USB wake, device wake

**DFU**:
The Westberry bootloader mode used to flash the keyboard.
_Avoid_: boot mode, flash mode

**Bootmagic**:
The startup check that jumps to the bootloader when a chosen key is held during power-up.
_Avoid_: boot key, recovery key

**VIA**:
The WebHID configurator used to edit layers and keycodes in a browser.
_Avoid_: configurator, web config
