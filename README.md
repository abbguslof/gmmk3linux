# Glorious GMMK 3 Pro 75% ISO (WB32) — Custom Linux Firmware

```text
   ______ __  __ __  __ _  __ _____     ____  ____   ___        ____ _____ ____ 
  / ____// / / //  |/  // |/ //__  /    / __ \/ __ \ / _ \      /  _// ___// __ \
 / / __ / / / // /|_/ // /|_/ / / /    / /_/ / /_/ // / / /     / /  \__ \/ / / /
/ /_/ // /_/ // /  / // /  / / / /__  / ____// _, _// /_/ /   _/ /  ___/ / /_/ / 
\____/ \____//_/  /_//_/  /_/ /____/ /_/    /_/ |_| \____/   /___/ /____/\____/  
```

[![Firmware](https://img.shields.io/badge/firmware-QMK-blue.svg)](https://qmk.fm)
[![Platform](https://img.shields.io/badge/MCU-Westberry%20WB32FQ95-orange.svg)](https://www.westberrytech.com/)
[![OS](https://img.shields.io/badge/OS-Arch%20Linux%20%7C%20Hyprland-blueviolet.svg)](https://archlinux.org)
[![Layout](https://img.shields.io/badge/layout-Swedish%20ISO%2075%25-green.svg)](#-layout--profiles)
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
  * **Zero Debug Overhead**: Stripped serial logging and console polling for pure scanning throughput.
* **Hardware 3-Position Slider Support**: Native matrix scanning of the rear slider switch dynamically selects OS profiles on the fly with RGB color confirmation.
* **Context-Aware Productivity Encoder**: High-speed scrubber, word navigator, tab manager, window controller, and mouse emulation tool (no volume dial).
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

```text
┌────────────────────────────────────────────────────────────────────────┐
│                        REAR HARDWARE SLIDER                            │
│                                                                        │
│         [Pos 1: Left]             [Pos 2: Mid]           [Pos 3: Right]│
│             ●───────○────────○                   ○────────○───────●    │
│                │                       │                     │         │
│                ▼                       ▼                     ▼         │
│           ARCH LINUX                 macOS                WINDOWS      │
│      • Caps Lock: · (middle)   • Opt ↔ Cmd swapped   • Standard Win ISO│
│      • Hyprland Focus & Kill   • Mac Shortcuts       • Win Shortcuts   │
│      • Matrix: [Row 11, Col 7] • Matrix: [12, Col 7] • Matrix: [13, 7]│
│      • Ambient: Dim Grey/White • Ambient: Warm Amber • Ambient: DeepBlu│
│      • [RGB Flash: Cyan]       • [RGB Flash: White]  • [Flash: Purple] │
└────────────────────────────────────────────────────────────────────────┘
```

A non-blocking matrix scanner in `housekeeping_task_user()` samples Rows 11, 12, and 13 every 25ms, dynamically activating the appropriate base layer and firing a visual RGB confirmation flash before settling into the profile's solid dim ambient backlight.

---

## ⌨️ Layout & Profiles

### Physical Layout: 75% ISO Swedish (Arch Linux Profile 1)

```text
┌───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐    ┌───────┐
│Esc│ │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│    │ KNOB  │
└───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘    │ ↺ ↻ 🔘│
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

* **Position 1 (Arch Linux)**: Base layer 0 (`PROF_LINUX`). Caps Lock is customized to Swedish middle dot (`·` via `RALT(KC_DOT)`). Ambient lighting: **Solid Dim Neutral White / Grey** (with instant Cyan flash confirmation on switch).
* **Position 2 (macOS)**: Base layer 1 (`PROF_MAC`). Left Option and Command are swapped for natural macOS muscle memory. Ambient lighting: **Solid Dim Warm Amber / Candlelight** (with instant White flash confirmation on switch).
* **Position 3 (Windows)**: Base layer 2 (`PROF_WIN`). Standard Windows ISO modifiers. Ambient lighting: **Solid Dim Subtle Deep Blue** (with instant Purple flash confirmation on switch).

*(Minimalist design: no rainbow RGB or animated distractions — pure solid faint backlight for night reading).*

---

### Shared Function Layer (`SHARED_FN` / Layer 3)

Hold `Fn` (`MO(SHARED_FN)`) to access media, navigation, system controls, and programming symbols:

```text
┌───────┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐    ┌───────┐
│QK_BOOT│ │MyC│Hom│Cal│Sel│ │Prv│Nxt│Ply│Stp│ │Mut│Vo-│Vo+│PSc│    │ MOUSE │
└───────┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘    │ ↺ ↻ 🔘│
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐    └───────┘
│   │   │   │   │   │   │   │ { │ [ │ ] │ } │ \ │   │EE_CLR │    ┌───────┐
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤    │FN_SLEP│
│RTOG │   │   │   │   │   │   │Hom│ ↑ │End│   │   │ ~ │Ent  │    ├───────┤
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐   │    │       │
│CapsLk│   │   │   │   │   │ ← │ ↓ │ ↑ │ → │   │   │   │   │    ├───────┤
├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┤    │       │
│    │ | │SAD│SAI│SPD│SPI│   │   │   │   │   │   │       │VAI│    ├───────┤
├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼────┤       │
│    │GUI │   │         Play/Pause      │    │    │ │RMOD│VAD│MOD │└───────┘
└────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴────┘
```

#### ⌨️ Fn Layer Quick Reference Table

| Key Cluster | Keys | Action / Feature |
| :--- | :--- | :--- |
| **System & Sleep** | `Esc`, `Del`, `Backspace` | `Esc` (DFU Bootloader), `Del` (Universal OS Sleep), `Backspace` (EEPROM Reset) |
| **App & System** | `F1` – `F4` | `F1` (My Computer), `F2` (Browser Home), `F3` (Calculator), `F4` (Media Player) |
| **Media Playback** | `F5` – `F9`, `Space` | `F5` (Prev Track), `F6` (Next Track), `F7` (Play), `F8` (Stop), `F9` (Mute), `Space` (Play/Pause) |
| **Audio Volume** | `F10` – `F11` | `F10` (Volume Down), `F11` (Volume Up) |
| **PrintScreen** | `F12` | Instant Screen Capture (`PrintScreen`) |
| **Brackets & Syntax** | `7`, `8`, `9`, `0`, `+`, `\`, `<` | Swedish ISO programmer symbols (`{ [ ] } \ \|`) |
| **Navigation & Vim** | `H`, `J`, `K`, `L`, `U`, `I`, `O` | Vim navigation (`← ↓ ↑ →`), `Home`, `End` |
| **Hardware RGB Controls** | `Tab`, `Z`, `X`, `C`, `V`, Arrow Cluster | Toggle (`Tab`), Saturation (`Z`/`X`), Speed (`C`/`V`), Brightness (`↑`/`↓`), Mode Prev/Next (`←`/`→`) |
| **Windows GUI Lock** | `Super` (`GU_TOGG`) | Lock / unlock Windows key (`Super`) |

* **Built-in OS Sleep Key (`Fn + Del`)**:
  * **Linux / Windows**: Triggers universal ACPI system sleep (`KC_SLEP` / systemd suspend).
  * **macOS**: Triggers native immediate sleep (`Cmd + Option + Eject`).
* **EE_CLR (`Fn + Backspace`)**: Resets dynamic VIA EEPROM memory back to firmware defaults.

---

## 🎛️ Rotary Encoder & Knob Switch Matrix

```text
                     ┌────────────────────────┐
                     │   ROTARY KNOB MODES    │
                     └───────────┬────────────┘
                                 │
           ┌─────────────────────┼─────────────────────┐
           │                     │                     │
           ▼                     ▼                     ▼
     [ DEFAULT ]             [ SHIFT ]              [ CTRL ]
   ↺ : Step Left (←)      ↺ : Undo (Ctrl+Z)      ↺ : Zoom Out (-)
   ↻ : Step Right (→)     ↻ : Redo (Ctrl+Y)      ↻ : Zoom In (+)
   🔘: Mic Mute (PAUS)    🔘: Save File (Ctrl+S) 🔘: Reset 100% (0)
           │                     │                     │
           ├─────────────────────┼─────────────────────┤
           │                     │                     │
           ▼                     ▼                     ▼
      [  ALT  ]           [ SHIFT + ALT ]          [ SUPER ]
   ↺ : Prev Word          ↺ : Prev Tab           ↺ : Focus Left (←)
   ↻ : Next Word          ↻ : Next Tab           ↻ : Focus Right (→)
   🔘: Select Word (C+D)  🔘: Close Tab (C+W)    🔘: Kill Window (S+W)
           │
           └─────────────────────┬─────────────────────┐
                                 │
                                 ▼
                         [ FN (MOUSE MODE) ]
                   Fn Alone   : ↺ Cursor Up   ↻ Cursor Down   🔘 Left Click
                   Fn + Shift : ↺ Cursor Left ↻ Cursor Right  🔘 Right Click
                   Fn + Alt   : ↺ Scroll Left ↻ Scroll Right  🔘 Middle Click
```

### Base Profiles (Linux / macOS / Windows)

| State / Modifiers | Turn CCW (↺) | Turn CW (↻) | Knob Click (🔘) | Workflow |
| :--- | :--- | :--- | :--- | :--- |
| **Default (None)** | **Step Backward** (`Left Arrow`) | **Step Forward** (`Right Arrow`) | **Hardware Pause / Mic Mute** (`KC_PAUS`) | Video scrubbing (DaVinci/YouTube), timeline navigation, Hyprland mic toggle |
| **Shift** | **Undo** (`Ctrl+Z` / `Cmd+Z`) | **Redo** (`Ctrl+Y` / `Cmd+Shift+Z`) | **Save File** (`Ctrl+S` / `Cmd+S`) | Document history stepping & instant save |
| **Ctrl** | **Zoom Out** (`Ctrl+-` / `Cmd+-`) | **Zoom In** (`Ctrl++` / `Cmd++`) | **Reset Zoom 100%** (`Ctrl+0` / `Cmd+0`) | Universal display scaling across browsers, IDEs, and terminals |
| **Alt** | **Previous Word** (`Ctrl+Left` / `Opt+Left`) | **Next Word** (`Ctrl+Right` / `Opt+Right`) | **Select Word / Token** (`Ctrl+D` / `Cmd+D`) | Fast code/text navigation & multi-cursor expansion |
| **Shift + Alt** | **Previous Tab** (`Ctrl+Shift+Tab`) | **Next Tab** (`Ctrl+Tab`) | **Close Active Tab** (`Ctrl+W` / `Cmd+W`) | Browser & editor tab cycling and closing |
| **Super (GUI)** | **Focus Left** (`Super+Left`)<br>*(macOS: `Cmd+Shift+Tab`)*<br>*(Win: `Alt+Shift+Tab`)* | **Focus Right** (`Super+Right`)<br>*(macOS: `Cmd+Tab`)*<br>*(Win: `Alt+Tab`)* | **Kill Active Window** (`Super+W`)<br>*(macOS: `Cmd+Q`)*<br>*(Win: `Alt+F4`)* | Native Hyprland Omarchy window navigation & close without lifting hands |

### Function Layer (`Fn`) — Ergonomic Mouse Suite

| State / Modifiers | Turn CCW (↺) | Turn CW (↻) | Knob Click (🔘) | Workflow |
| :--- | :--- | :--- | :--- | :--- |
| **Fn (Alone)** | **Cursor Up** (`KC_MS_UP`) | **Cursor Down** (`KC_MS_DOWN`) | **Mouse Left Click** (`KC_MS_BTN1`) | Primary Y-axis mouse navigation and selection |
| **Fn + Shift** | **Cursor Left** (`KC_MS_LEFT`) | **Cursor Right** (`KC_MS_RIGHT`) | **Mouse Right Click** (`KC_MS_BTN2`) | Primary X-axis mouse navigation & context menus |
| **Fn + Alt** | **Horizontal Wheel Left** (`KC_MS_WH_LEFT`) | **Horizontal Wheel Right** (`KC_MS_WH_RIGHT`) | **Mouse Middle Click** (`KC_MS_BTN3`) | Wide timeline scrubbing, spreadsheets, diffs, autoscroll |

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

> [!IMPORTANT]
> **Always run the flash command FIRST before putting the keyboard into DFU mode!**
> Because entering DFU mode makes the keyboard completely unresponsive to typing, starting the flash command first ensures you don't need a second keyboard. The script will safely compile your firmware and wait (`Waiting for WB32 DFU device...`) until the keyboard is connected in bootloader mode.

1. **Start the flasher:**
```bash
./setup_and_flash.sh --flash
# or: make flash
```

2. **Put the keyboard into DFU Bootloader mode while the script waits:**
   * **Method 1 (Hardware Bootmagic — Most Reliable):** Unplug the USB cable, hold **`Space + B`** (or **`Esc`**), and reconnect the cable.
   * **Method 2 (Software):** Press **`Fn + Esc`** on the keyboard (`QK_BOOT`).

   > [!TIP]
   > **How to confirm DFU mode:** When entering the WB32 ROM DFU bootloader, **the keyboard will become completely unresponsive to typing and ALL RGB lights will turn OFF**. The script will instantly detect the keyboard, flash the firmware, and automatically reboot it back into typing mode!

*Manual flash option (if already in DFU mode):*
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
                                └── keymap.c # Multi-OS adaptive keymap & knob engine
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
