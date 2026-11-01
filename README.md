# GMMK 3 Pro 75% ISO Linux firmware

A QMK firmware replacement for the **Glorious GMMK 3 Pro 75% ISO (wired, non-HE)**. It runs on the Westberry WB32FQ95 and gives you the full keyboard without Glorious Core: four layers, a rear profile slider, a context-aware encoder, per-key RGB, VIA WebHID, and a suspend policy that keeps the host asleep.

The firmware is built and tested on Arch Linux with a Swedish ISO board. The macOS and Windows layers are included but not verified on this release.

> [!WARNING]
> Flashing replaces the vendor firmware. A bad flash can leave the keyboard in DFU until you recover it. Read the recovery section before you flash. No warranty.

## What you get

| Feature | Setting |
| :--- | :--- |
| USB polling | 1000 Hz (`USB_POLLING_INTERVAL_MS 1`) |
| Key press | Reported on the first scan (`asym_eager_defer_pk`) |
| Key release | Deferred until contact is stable for 8 ms (`DEBOUNCE 8`) |
| Matrix scan | Roughly 2 kHz (`MATRIX_IO_DELAY 30`) |
| RGB update | About 60 Hz (`RGB_MATRIX_LED_FLUSH_LIMIT 16`) |
| Rollover | NKRO always on (`FORCE_NKRO`) |
| Layers | 4: Linux, macOS, Windows, Fn |
| Profiles | Rear 3-position slider, scanned from matrix column 7 |
| Encoder | Context-aware rotation and click |
| Configurator | VIA v3 WebHID |

The debounce choice is a tradeoff. A press is reported before the debounce window, so keydown latency stays low. A release waits 8 ms for the contact to settle, which filters most release chatter. A tap shorter than 8 ms can be stretched to about 16 ms. See [Chatter tuning](#chatter-tuning).

## Hardware

- Keyboard: Glorious GMMK 3 Pro 75% ISO, wired, non-HE.
- MCU: Westberry WB32FQ95, ARM Cortex-M3.
- USB: `504b:320f`.
- Bootloader: Westberry `wb32-dfu`. Use `wb32-dfu-updater_cli`, not STM32 or Atmel DFU tools.

The ANSI, wireless, and HE versions need different firmware. The keymap and VIA definitions here describe the Swedish ISO layout.

## Slider and profiles

The vendor firmware configured the rear slider as `DIP_SWITCH_PINS { A13 }`. On the WB32, A13 is the SWDIO/JTAG pin, so that read fails. The slider is wired into matrix **column 7**: each position closes column 7 to one row.

| Slider | Profile | Layer | Matrix | Ambient | Switch flash |
| :--- | :--- | :--- | :--- | :--- | :--- |
| Left | Arch Linux | `PROF_LINUX` (0) | `[11, 7]` | Dim neutral (30, 32, 35) | Cyan |
| Middle | macOS | `PROF_MAC` (1) | `[12, 7]` | Dim amber (45, 26, 8) | White |
| Right | Windows | `PROF_WIN` (2) | `[13, 7]` | Dim blue (10, 25, 55) | Purple |

`housekeeping_task_user()` samples the three rows every 25 ms and sets the default layer. A 500 ms RGB flash confirms the change. The slider stays electrically closed, so every suspend path must mask column 7 on rows 11 to 13. See [ADR 0001](docs/adr/0001-slider-matrix-mapping.md).

## Layout

Physical layout, Swedish ISO:

```text
┌───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐    ┌───────┐
│Esc│ │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│    │ KNOB  │
└───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘    │ ↺ ↻ O │
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐    └───────┘
│ § │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ + │ ´ │Backsp │    ┌───────┐
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤    │  Del  │
│ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ Å │ ¨ │Ent  │    ├───────┤
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐   │    │ PgUp  │
│CapsLk│ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ö │ Ä │ '  │   │    ├───────┤
├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┤    │ PgDn  │
│Shft│ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ - │ Shift │ ↑ │    ├───────┤
├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼────┤  End  │
│Ctrl│Supr│Alt │         Space          │AltG│ Fn │ │ ← │ ↓ │ →  │└───────┘
└────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴────┘
```

The Linux profile maps Caps Lock to the Swedish middle dot (`RALT(KC_DOT)`). The macOS profile swaps Left Option and Left Command. The Windows profile uses the standard ISO modifiers.

### Fn layer

Hold `Fn` for media, navigation, system keys, and RGB controls.

```text
┌───────┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐    ┌───────┐
│ BOOT  │ │MyC│Hom│Cal│Sel│ │Prv│Nxt│Ply│Stp│ │Mut│Vo-│Vo+│PSc│    │ CLICK │
└───────┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘    │ ↺ ↻ O │
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐    └───────┘
│   │   │   │   │   │   │   │ { │ [ │ ] │ } │ \ │   │ EE_CLR│    ┌───────┐
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤    │SLEEP  │
│RTOG │   │   │   │   │   │   │Hom│ ↑ │End│   │   │ ~ │Ent  │    ├───────┤
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐   │    │       │
│CapsLk│   │   │   │   │   │ ← │ ↓ │ ↑ │ → │   │   │   │   │    ├───────┤
├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┤    │       │
│    │ | │SAD│SAI│SPD│SPI│   │   │   │   │   │   │       │VAI│    ├───────┤
├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼────┤       │
│    │GUI │    │        Play/Pause        │    │    │ │RMOD│VAD│MOD │└───────┘
└────┴────┴────┴─────────────────────────┴────┴────┘ └───┴───┴────┘
```

| Keys | Action |
| :--- | :--- |
| `Esc` | `QK_BOOT`, enter the bootloader. VIA remaps are kept. |
| `Del` | `FN_SLEP`, system sleep. Linux and Windows send `KC_SLEP`; macOS sends Command + Option + Eject. |
| `Backspace` | `EE_CLR`, clear dynamic keymap EEPROM. |
| `F1` to `F4` | My Computer, browser home, calculator, media select. |
| `F5` to `F9` | Previous, next, play, stop, mute. |
| `F10`, `F11` | Volume down, volume up. |
| `F12` | Print Screen. |
| `7`, `8`, `9`, `0`, `+` | `{`, `[`, `]`, `}`, `\`. |
| `¨` | `~`. |
| `<>` | `|`. |
| `H`, `J`, `K`, `L` | Left, down, up, right. |
| `U`, `I`, `O` | Home, up, end. |
| `Tab` | Toggle RGB. |
| `Z`, `X` | Saturation down, saturation up. |
| `C`, `V` | Speed down, speed up. |
| `Up`, `Down` | Brightness up, brightness down. |
| `Left`, `Right` | Previous effect, next effect. |
| `Super` | `GU_TOGG`, toggle the GUI key. |
| `Space` | Play/pause. |

`Fn + Esc` enters DFU. The keyboard stops typing and turns off the RGB. The flash script waits for it.

## Encoder

| Modifier | Counter-clockwise | Clockwise | Click |
| :--- | :--- | :--- | :--- |
| None | Left arrow | Right arrow | Pause / mic mute |
| Shift | Undo (`Ctrl+Z` or `Cmd+Z`) | Redo (`Ctrl+Y` or `Cmd+Shift+Z`) | Save (`Ctrl+S` or `Cmd+S`) |
| Ctrl | Zoom out (`Ctrl+-` or `Cmd+-`) | Zoom in (`Ctrl++` or `Cmd++`) | Reset zoom (`Ctrl+0` or `Cmd+0`) |
| Alt | Previous word (`Ctrl+Left` or `Opt+Left`) | Next word (`Ctrl+Right` or `Opt+Right`) | Select word (`Ctrl+D` or `Cmd+D`) |
| Shift + Alt | Previous tab (`Ctrl+Shift+Tab`) | Next tab (`Ctrl+Tab`) | Close tab (`Ctrl+W` or `Cmd+W`) |
| Super | Focus left (profile-specific) | Focus right (profile-specific) | Close window (profile-specific) |
| Fn | Mouse up | Mouse down | Left click |
| Fn + Shift | Mouse left | Mouse right | Right click |
| Fn + Alt | Horizontal wheel left | Horizontal wheel right | Middle click |

The Linux Super bindings assume Hyprland: `Super+Left`, `Super+Right`, and `Super+W`. The macOS bindings are `Cmd+Shift+Tab`, `Cmd+Tab`, and `Cmd+Q`. The Windows bindings are `Alt+Shift+Tab`, `Alt+Tab`, and `Alt+F4`.

The default click sends `KC_PAUS`. Bind Pause to your microphone mute command in Hyprland if you use that workflow.

## Install

### Prerequisites (Arch Linux)

```bash
sudo pacman -S --needed git arm-none-eabi-gcc arm-none-eabi-newlib \
  arm-none-eabi-binutils python-pipx cmake libusb
pipx install qmk
pipx ensurepath
```

Build and install the Westberry flasher:

```bash
git clone https://github.com/westberrytech/wb32-dfu-updater.git
cd wb32-dfu-updater
mkdir build && cd build
cmake .. && make
sudo cp wb32-dfu-updater_cli /usr/local/bin/
```

`setup_and_flash.sh` sets the QMK CLI home to `~/qmk_gmmk3` with `qmk config user.qmk_home`. This is a global QMK CLI setting. If you use QMK for other boards, point it back at that tree afterward.

### Udev rules

Install the rules for non-root flashing, WebHID, and the sleep policy:

```bash
make udev
```

The rule disables USB wakeup for `504b:320f` by default. `systemctl suspend` and `systemctl sleep` then keep the machine asleep, and you wake it with the power button. To wake with the keyboard, edit `/etc/udev/rules.d/99-gmmk3-pro.rules`, comment the `power/wakeup="disabled"` line, uncomment the `enabled` line, reload the rules, and replug the keyboard. See [Sleep and wake](#sleep-and-wake).

### Build

```bash
make build
```

The script checks out the pinned upstream commit, restores tracked files, applies the overlay in `qmk_overlay/`, and compiles `gmmk_gmmk3_p75_iso_default.bin`. It prints the upstream commit and tool versions. The build also needs the ChibiOS, ChibiOS-Contrib, LUFA, and printf submodules, which the script initializes.

The script treats `~/qmk_gmmk3` as a build tree. It restores tracked files before applying the overlay, so edits you make there are discarded. Edit `qmk_overlay/` instead.

### Flash

Run the flash command first. It builds, then waits for the bootloader, so you do not need a second keyboard.

```bash
make flash
```

Then put the keyboard into DFU:

1. Unplug the USB cable.
2. Hold the physical `Esc` key.
3. Reconnect the cable while holding `Esc`.

You can also press `Fn + Esc` while the script is waiting. When DFU starts, the keyboard stops typing and all RGB turns off. The script detects it, flashes, and reboots the keyboard.

`Fn + Esc` sends `QK_BOOT` and keeps the dynamic keymap. Holding `Esc` during power-up uses Bootmagic Lite, which clears the EEPROM before it jumps to the bootloader. Use `Fn + Esc` when the keyboard still types, and hold `Esc` only for recovery.

This QMK build uses Bootmagic Lite with the `Esc` key only. `Space + B` is not a bootloader shortcut here.

Manual flash if the keyboard is already in DFU:

```bash
wb32-dfu-updater_cli -w -D gmmk_gmmk3_p75_iso_default.bin -R
```

The prebuilt binary in this repository has SHA-256:

```text
a018af720685bc251c74b79355989f0dced3ba1cb547a4d2c9334bf632800f68
```

## VIA

1. Open [usevia.app](https://usevia.app) in Chromium, Chrome, or Brave.
2. Open Settings and enable the Design tab.
3. Open Design, choose **Load Draft Definition**, and select one of:
   - `definition/gmmk3_via_v3_swedish.json` for Swedish legends.
   - `definition/gmmk3_via_v3.json` for the standard definition.
4. Go to Configure, authorize `GMMK3 75% ISO`, and edit the four layers.

The custom keycodes `KNOB_CLICK` and `FN_SLEP` are in both definitions. The RGB menu uses the QMK RGB matrix menu.

EEPROM remaps survive reflashing the same layout version. A layout version change or `Fn + Backspace` clears them. Holding `Esc` during power-up also clears them, because that is Bootmagic.

## Sleep and wake

The keyboard advertises USB Remote Wakeup. On this board the rear slider reads as a held key, so a stock QMK build wakes the host as soon as it suspends. A device reset or reconnect can also wake a suspended host.

This release handles it in two places:

1. **Udev:** `power/wakeup` is `disabled` for `504b:320f` by default. This is the reliable fix. The power button wakes the machine.
2. **Firmware:** `suspend_wakeup_condition_kb()` masks column 7 on rows 11 to 13, waits about 255 ms after suspend entry, and only wakes on a key that was released and then pressed. The state resets on a new suspend entry even if the wakeup hook did not run.

The firmware guard cannot stop a host wake caused by a device reset or reconnect. If you enable keyboard wake and the machine still wakes, disable wakeup again and use the power button.

To inspect the current setting:

```bash
for d in /sys/bus/usb/devices/*; do
  if [ "$(cat "$d/idVendor" 2>/dev/null)" = "504b" ] &&
     [ "$(cat "$d/idProduct" 2>/dev/null)" = "320f" ]; then
    echo "$d $(cat "$d/power/wakeup")"
  fi
done
```

To test sleep:

```bash
systemctl suspend
journalctl -k -b -1 | grep -E 'suspend entry|suspend exit|Waking up'
```

## Chatter tuning

The current setting is `asym_eager_defer_pk` with `DEBOUNCE 8` in `qmk_overlay/keyboards/gmmk/gmmk3/p75/config.h`. The debounce type is set in `qmk_overlay/keyboards/gmmk/gmmk3/p75/iso/rules.mk`.

If a key still produces two letters:

1. Raise `DEBOUNCE` to 10 or 12 and rebuild.
2. If the duplicate happens on press instead of release, change `DEBOUNCE_TYPE` to `sym_defer_pk`. That filters both edges but adds the same delay to keydown.
3. If one key still doubles with a longer debounce, the switch is likely worn. Replace it.

`asym_eager_defer_pk` caps `DEBOUNCE` at 127 ms.

A key that doubles only when pressed quickly is bounce under fast actuation. Software can filter it with `sym_defer_pk` at 10 ms, at the cost of 10 ms keydown. If you want to keep the eager press, replace the switch.

A single key that doubles on slow, deliberate presses points to the switch or its socket. Reseat the switch, then swap it with a known-good switch. If the duplicate follows the switch, replace the switch. If it stays in the same socket, inspect the socket and PCB. A board where every key doubles during fast typing points to debounce instead.

Test with `evtest`, `wev` on Wayland, or a keyboard tester page. Type the problem keys slowly and quickly, and count duplicate press or release events.

## Troubleshooting

**The PC wakes immediately after `systemctl suspend` or `systemctl sleep`.**
Check `power/wakeup` for `504b:320f`. It should read `disabled`. If it reads `enabled`, reinstall the udev rule with `make udev`, then replug the keyboard or run `sudo udevadm trigger --action=add --subsystem-match=usb`.

**The keyboard does not type after a flash.**
It may be in DFU. Reconnect it while holding `Esc`, or run `wb32-dfu-updater_cli -R` to reset it.

**The keyboard is stuck in the bootloader.**
Unplug and replug the USB cable. If it still enumerates as `342d:dfa0`, flash again with `make flash`.

**VIA remaps do not match the firmware.**
Press `Fn + Backspace` to clear the dynamic keymap, then replug. The firmware also clears the layout when the EEPROM magic version changes.

**The build fails after an upstream change.**
The script pins commit `121e1a63`. Delete `~/qmk_gmmk3` and rerun. If you change the pin, expect to update the overlay under `qmk_overlay/`.

## Repository layout

```text
gmmk3linux/
├── README.md
├── CHANGELOG.md
├── LICENSE
├── Makefile
├── setup_and_flash.sh
├── gmmk_gmmk3_p75_iso_default.bin
├── udev/99-gmmk3-pro.rules
├── definition/
│   ├── gmmk3_via_v3.json
│   └── gmmk3_via_v3_swedish.json
├── docs/
│   ├── GLOSSARY.md
│   └── adr/
│       ├── 0001-slider-matrix-mapping.md
│       ├── 0002-suspend-wake-policy.md
│       └── 0003-debounce-tradeoff.md
└── qmk_overlay/
    ├── platforms/
    │   ├── suspend.c
    │   └── suspend.h
    └── keyboards/gmmk/gmmk3/p75/
        ├── config.h
        └── iso/
            ├── iso.c
            ├── rules.mk
            └── keymaps/default/keymap.c
```

`qmk_overlay/` mirrors the upstream QMK tree. Only changed files live here. The overlay also patches `platforms/suspend.c` and `platforms/suspend.h` to expose a keyboard-level wake condition. That patch is tied to the pinned upstream commit.

## Build reproducibility

- Upstream: `https://gitlab.com/glorious-public/qmk_firmware.git`, branch `gmmk3_p75_ansi_iso_wired`, commit `121e1a6341c5c045b396dab8c5e755a4b9a4aefd`.
- QMK CLI: 1.2.0.
- Compiler: `arm-none-eabi-gcc` 16.2.0 (Arch).
- Tested on: Arch Linux, kernel 7.2.3, Hyprland.

## License and credits

GPL-2.0-or-later. See [LICENSE](LICENSE).

Board files and the vendor QMK branch come from Glorious. The firmware uses QMK, ChibiOS, ChibiOS-Contrib, and the Westberry WB32 support. VIA definitions use the VIA v3 layout format.

Maintained by [abbguslof](https://github.com/abbguslof).
