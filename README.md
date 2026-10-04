# Glorious GMMK 3 Pro 75% ISO (WB32) — Custom Linux & Hyprland Firmware

[![Firmware](https://img.shields.io/badge/firmware-QMK-blue.svg)](https://qmk.fm)
[![Platform](https://img.shields.io/badge/MCU-Westberry%20WB32FQ95-orange.svg)](https://www.westberrytech.com/)
[![OS](https://img.shields.io/badge/OS-Arch%20Linux%20%7C%20Hyprland-blueviolet.svg)](https://archlinux.org)
[![Layout](https://img.shields.io/badge/layout-Swedish%20ISO%2075%25-green.svg)](#layout--profiles)
[![VIA](https://img.shields.io/badge/configurator-VIA%20v3%20WebHID-red.svg)](https://usevia.app)
[![License](https://img.shields.io/badge/license-GPL--2.0-yellow.svg)](LICENSE)

An open-source, ultra-low-latency QMK firmware replacement for the **Glorious GMMK 3 Pro 75% ISO (Wired, Non-HE)** keyboard powered by the **Westberry WB32FQ95** MCU. Designed to give complete control without Glorious Core software, tailored for Arch Linux, Hyprland, and multi-OS workflows.

---

## ⚡ Highlights

* **No Glorious Core Required**: Full standalone hardware configuration, native dynamic lighting, and persistent on-board memory.
* **Maximum Performance & Ultra-Low Latency**:
  * **1000Hz (1ms) USB Polling Rate** forced via hardware descriptor (`USB_POLLING_INTERVAL_MS 1`).
  * **0ms Latency Eager Debouncing** (`sym_eager_pk`) registering instant keydown response on first switch contact.
  * **True N-Key Rollover (NKRO)** forced active by default.
  * **Zero Debug Overhead**: Removed serial logging and console polling for pure scanning throughput.
* **Hardware 3-Position Slider Support**: Native matrix scanning of the rear slider switch dynamically selects OS profiles on the fly with RGB color confirmation.
* **Full VIA v3 WebHID Compatibility**: Edit keymaps and layers live in Chromium or [usevia.app](https://usevia.app) using the included Swedish ISO definitions.
* **1-Click Build & Flash**: Automated environment setup, submodule checkouts, compilation, and bootloader flashing.

---

## 🛠️ Hardware Discoveries & Architecture

### 1. Westberry WB32FQ95 & Bootloader Toolchain
* **Microcontroller**: Westberry **WB32FQ95** (ARM Cortex-M3 core).
* **Bootloader Protocol**: Custom USB DFU implementation (`wb32-dfu`). Requires `wb32-dfu-updater_cli` instead of standard STM32/Atmel DFU tools.
* **Bootloader Entry**: Press **Fn + Esc** in firmware, or hold the physical **Esc** key while plugging in the USB cable.

### 2. The 3-Position Hardware Slider Discovery
Upstream vendor firmware erroneously configured `#define DIP_SWITCH_PINS { A13 }`. On WB32 chips, `A13` is the hardware `SWDIO/JTAG` debug interface, causing direct GPIO reads to fail.

The physical 3-position rear slider is actually wired directly into **Column 7** of the keyboard matrix:
* **Position 1 (Left Dot)**: Matrix `[Row 11, Col 7]` (`0x80` mask) $\rightarrow$ **Arch Linux Profile**
* **Position 2 (Center Dot)**: Matrix `[Row 12, Col 7]` (`0x80` mask) $\rightarrow$ **macOS Profile**
* **Position 3 (Right Dot)**: Matrix `[Row 13, Col 7]` (`0x80` mask) $\rightarrow$ **Windows Profile**

A non-blocking matrix scanner in `housekeeping_task_user()` samples Rows 11, 12, and 13 every 25ms, dynamically activating the appropriate base layer and firing a visual RGB confirmation flash.

---

## ⌨️ Layout & Profiles

### Physical Slider Profiles

| Position | Target OS | Base Layer | Distinct Features | RGB Confirmation Flash |
| :---: | :---: | :---: | :--- | :---: |
| **Position 1 (Left)** | **Arch Linux** | `PROF_LINUX` (0) | Swedish ISO, Caps Lock mapped to Middle Dot (`·` via `RALT(KC_DOT)`) | **Cyan / Teal** |
| **Position 2 (Center)** | **macOS** | `PROF_MAC` (1) | Left Option and Command swapped for native Mac muscle memory | **White** |
| **Position 3 (Right)** | **Windows** | `PROF_WIN` (2) | Standard Windows ISO modifier cluster | **Purple** |

### Shared Function Layer (`SHARED_FN` / Layer 3)
Activated by holding `MO(SHARED_FN)`:
* **Esc**: Bootloader Mode (`QK_BOOT`)
* **F1 – F12**: Media controls (`My Computer`, `Calculator`, `Prev`, `Next`, `Play`, `Stop`, `Mute`, `Vol -`, `Vol +`, `PrintScreen`)
* **Number Row**: Direct Swedish programmer symbols: `{`, `[`, `]`, `}`, `\`
* **Navigation**: Vim / Arrow cluster on `HJKL`, `Home`, `End`
* **RGB Controls**: `RGB_TOG`, Hue, Saturation (`RGB_SAI`/`RGB_SAD`), Brightness (`RGB_VAI`/`RGB_VAD`), Effect modes (`RGB_MOD`/`RGB_RMOD`)
* **EEPROM Clear**: `EE_CLR` (Fn + Backspace) resets dynamic VIA EEPROM memory.

---

## 🎛️ Rotary Encoder & Knob Switch

The rotary encoder and push switch provide rich contextual actions:

| Action / Modifier | Mode / State | Behavior |
| :--- | :--- | :--- |
| **Turn (Normal)** | Unmodified | **Volume Up / Down** (or Line Up/Down) |
| **Turn + Shift** | Any profile | **Scrub Undo / Redo** (`Ctrl + Z` / `Ctrl + Y`) |
| **Turn + Ctrl** | Any profile | **Universal Zoom** (`Ctrl + Plus` / `Ctrl + Minus`) |
| **Turn + Alt** | Any profile | **Word Jump** (`Ctrl + Right` / `Ctrl + Left`) |
| **Turn + Fn** | Fn Layer held | **Mouse Wheel / Vertical Navigation** |
| **Knob Click** | Normal | **Hardware Pause / Mic Mute** (`KC_PAUS`) |
| **Knob Click + Fn** | Fn Layer held | **Mouse Middle Click** (`KC_MS_BTN3`) |

*(Note: In Arch Linux Hyprland / Omarchy, `KC_PAUS` natively triggers your microphone mute toggle script).*

---

## 🚀 Getting Started

### 1. Prerequisites (Arch Linux)

Install the required build toolchain and dependencies:

```bash
sudo pacman -S --needed git arm-none-eabi-gcc arm-none-eabi-newlib arm-none-eabi-binutils python-pipx cmake libusb
pipx install qmk
pipx ensurepath
```

Install the Westberry DFU flasher utility:

```bash
git clone https://github.com/westberrytech/wb32-dfu-updater.git
cd wb32-dfu-updater
mkdir build && cd build
cmake .. && make
sudo cp wb32-dfu-updater_cli /usr/local/bin/
```

### 2. Install Udev Rules

Allow non-root flashing and WebHID access (for VIA):

```bash
sudo cp udev/99-gmmk3-pro.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && sudo udevadm trigger
```

Alternatively, use the Makefile shortcut:
```bash
make udev
```

### 3. Build Firmware

Compile the firmware using the automated build script:

```bash
make build
# or: ./setup_and_flash.sh --build
```

The script automatically clones the upstream Glorious QMK branch from GitLab, updates submodules (`chibios`, `chibios-contrib`, `lufa`, `printf`), applies this repository's performance overlay, and compiles `.build/gmmk_gmmk3_p75_iso_default.bin`.

### 4. Flash to Keyboard

1. Put the keyboard into DFU Bootloader mode:
   * Press **Fn + Esc** on the keyboard, OR
   * Unplug the USB cable, hold **Esc**, and plug it back in.
2. Run:
```bash
make flash
# or: ./setup_and_flash.sh --flash
```

*Manual flash option:*
```bash
wb32-dfu-updater_cli -D gmmk_gmmk3_p75_iso_default.bin -R
```

---

## 🌐 VIA Configurator (WebHID)

This firmware has full VIA v3 support enabled. You can customize keys and lighting directly from your browser without installing native software:

1. Open **[https://usevia.app](https://usevia.app)** in Chromium, Chrome, or Brave.
2. Go to the **Settings** gear icon $\rightarrow$ Enable **Show Design tab**.
3. Click the **Design** (paintbrush) tab.
4. Click **Load Draft Definition** and select:
   * [`definition/gmmk3_via_v3_swedish.json`](definition/gmmk3_via_v3_swedish.json) (Swedish ISO key legends)
   * OR [`definition/gmmk3_via_v3.json`](definition/gmmk3_via_v3.json) (Standard layout definition)
5. Return to the **Configure** tab and click **Authorize device** $\rightarrow$ select `GMMK3 75% ISO`.

All 4 layers (`PROF_LINUX`, `PROF_MAC`, `PROF_WIN`, and `SHARED_FN`) are editable in real-time.

---

## 📁 Repository Structure

```text
gmmk3linux/
├── README.md                      # Documentation, architecture, and user guide
├── LICENSE                        # GNU General Public License v2.0
├── Makefile                       # Convenience targets (build, flash, udev, clean)
├── setup_and_flash.sh             # 1-click clone, patch, build, and flash script
├── gmmk_gmmk3_p75_iso_default.bin # Precompiled ready-to-flash binary
├── udev/
│   └── 99-gmmk3-pro.rules         # Udev rules for WB32 DFU & WebHID
├── definition/
│   ├── gmmk3_via_v3.json          # Standard VIA v3 layout definition
│   └── gmmk3_via_v3_swedish.json  # Swedish ISO localized VIA v3 definition
└── qmk_overlay/                   # Drop-in overlay for Glorious QMK tree
    └── keyboards/
        └── gmmk/
            └── gmmk3/
                └── p75/
                    ├── config.h   # Low latency & 1000Hz polling tuning
                    ├── halconf.h  # SPI and hardware config
                    ├── info.json  # Matrix and RGB animations
                    ├── mcuconf.h  # MCU clock and peripheral configuration
                    └── iso/
                        ├── info.json
                        ├── iso.c  # AW20216S LED driver mapping
                        ├── rules.mk
                        └── keymaps/
                            └── default/
                                └── keymap.c # Multi-OS adaptive keymap & scanner
```

---

## 🆘 Troubleshooting & Recovery

* **Keyboard unresponsive / stuck in bootloader**:
  Run `wb32-dfu-updater_cli -R` to trigger a software reset, or reconnect the USB cable.
* **Reset EEPROM (Clear VIA remappings)**:
  Press **Fn + Backspace** (`EE_CLR`), then replug the board.
* **Force Bootloader on Plug-in**:
  Unplug the USB cable, hold down the physical `Esc` key, and reconnect the cable.

---

## 📜 License

This project is licensed under the **GNU General Public License v2.0 (GPL-2.0-or-later)** to match QMK Firmware. See [LICENSE](LICENSE) for details.
