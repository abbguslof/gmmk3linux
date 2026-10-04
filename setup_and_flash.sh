#!/usr/bin/env bash
# ==============================================================================
# Glorious GMMK 3 Pro 75% ISO (WB32) - Firmware Builder & Flasher
# Optimized for Arch Linux, Hyprland, and Maximum Low-Latency Performance
# ==============================================================================

set -euo pipefail

# ANSI Colors
BOLD="\033[1m"
GREEN="\033[1;32m"
CYAN="\033[1;36m"
YELLOW="\033[1;33m"
RED="\033[1;31m"
RESET="\033[0m"

log_info() { echo -e "${CYAN}[*]${RESET} $1"; }
log_success() { echo -e "${GREEN}[✓]${RESET} $1"; }
log_warn() { echo -e "${YELLOW}[!]${RESET} $1"; }
log_error() { echo -e "${RED}[✗]${RESET} $1"; }

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
QMK_DIR="${HOME}/qmk_gmmk3"
UPSTREAM_REPO="https://gitlab.com/glorious-public/qmk_firmware.git"
UPSTREAM_BRANCH="gmmk3_p75_ansi_iso_wired"
BIN_NAME="gmmk_gmmk3_p75_iso_default.bin"
FLASH_MODE=false
INSTALL_UDEV=false

show_help() {
    cat << EOF
Usage: $(basename "$0") [OPTIONS]

Options:
  --build       Compile firmware (default)
  --flash       Compile and flash firmware to keyboard (waits for DFU bootloader)
  --udev        Install udev rules for non-root flashing & WebHID
  --clean       Clean QMK build directory
  -h, --help    Show this help message

Examples:
  ./setup_and_flash.sh             # Build firmware
  ./setup_and_flash.sh --flash     # Build and flash to board
  ./setup_and_flash.sh --udev      # Install udev permissions
EOF
}

# Parse Arguments
if [ $# -eq 0 ]; then
    DO_BUILD=true
else
    DO_BUILD=false
    while [ $# -gt 0 ]; do
        case "$1" in
            --build) DO_BUILD=true ;;
            --flash) DO_BUILD=true; FLASH_MODE=true ;;
            --udev) INSTALL_UDEV=true ;;
            --clean)
                if [ -d "${QMK_DIR}" ]; then
                    log_info "Cleaning QMK build artifacts..."
                    (cd "${QMK_DIR}" && qmk clean -a)
                    log_success "Clean complete."
                fi
                exit 0
                ;;
            -h|--help) show_help; exit 0 ;;
            *) log_error "Unknown option: $1"; show_help; exit 1 ;;
        esac
        shift
    done
fi

echo -e "${BOLD}================================================================${RESET}"
echo -e "${BOLD}   Glorious GMMK 3 Pro 75% ISO (WB32FQ95) Linux Toolkit          ${RESET}"
echo -e "${BOLD}================================================================${RESET}"

# Install Udev Rules if requested
if [ "$INSTALL_UDEV" = true ]; then
    log_info "Installing udev rules for non-root flashing and WebHID..."
    sudo cp "${REPO_DIR}/udev/99-gmmk3-pro.rules" /etc/udev/rules.d/
    sudo udevadm control --reload-rules && sudo udevadm trigger
    log_success "Udev rules installed and reloaded."
    if [ "$DO_BUILD" = false ]; then
        exit 0
    fi
fi

# Check Prerequisites
log_info "Checking toolchain prerequisites..."

MISSING_DEPS=()
command -v git >/dev/null 2>&1 || MISSING_DEPS+=("git")
command -v qmk >/dev/null 2>&1 || MISSING_DEPS+=("qmk (pipx install qmk)")
command -v arm-none-eabi-gcc >/dev/null 2>&1 || MISSING_DEPS+=("arm-none-eabi-gcc")

if [ ${#MISSING_DEPS[@]} -gt 0 ]; then
    log_error "Missing required dependencies: ${MISSING_DEPS[*]}"
    echo -e "\nOn Arch Linux, install with:"
    echo -e "  ${BOLD}sudo pacman -S --needed git arm-none-eabi-gcc arm-none-eabi-newlib arm-none-eabi-binutils python-pipx${RESET}"
    echo -e "  ${BOLD}pipx install qmk && pipx ensurepath${RESET}\n"
    exit 1
fi

if [ "$FLASH_MODE" = true ]; then
    if ! command -v wb32-dfu-updater_cli >/dev/null 2>&1; then
        log_error "wb32-dfu-updater_cli is required for flashing the Westberry WB32FQ95 MCU."
        echo -e "Install by building Westberry's updater:"
        echo -e "  git clone https://github.com/westberrytech/wb32-dfu-updater.git"
        echo -e "  cd wb32-dfu-updater && mkdir build && cd build && cmake .. && make"
        echo -e "  sudo cp wb32-dfu-updater_cli /usr/local/bin/"
        exit 1
    fi
fi

# Clone or verify QMK directory
if [ ! -d "${QMK_DIR}" ]; then
    log_info "Cloning Glorious QMK repository (${UPSTREAM_BRANCH})..."
    git clone --depth 1 -b "${UPSTREAM_BRANCH}" "${UPSTREAM_REPO}" "${QMK_DIR}"
fi

# Configure QMK home
qmk config user.qmk_home="${QMK_DIR}" >/dev/null

# Initialize required submodules
log_info "Verifying required QMK submodules (ChibiOS, LUFA, printf)..."
(
    cd "${QMK_DIR}"
    git submodule update --init lib/chibios lib/chibios-contrib lib/lufa lib/printf
)

# Sync overlay files
log_info "Applying Linux performance tweaks and Swedish ISO keymap..."
cp -r "${REPO_DIR}/qmk_overlay/"* "${QMK_DIR}/"

# Compile Firmware
log_info "Compiling firmware (gmmk/gmmk3/p75/iso:default)..."
(
    cd "${QMK_DIR}"
    qmk compile -kb gmmk/gmmk3/p75/iso -km default
)

# Copy output binary to repo
if [ -f "${QMK_DIR}/.build/${BIN_NAME}" ]; then
    cp "${QMK_DIR}/.build/${BIN_NAME}" "${REPO_DIR}/${BIN_NAME}"
    log_success "Firmware compiled successfully!"
    echo -e "Binary artifact saved to: ${BOLD}${REPO_DIR}/${BIN_NAME}${RESET}"
else
    log_error "Build output not found at ${QMK_DIR}/.build/${BIN_NAME}"
    exit 1
fi

# Flash if requested
if [ "$FLASH_MODE" = true ]; then
    echo -e "\n${BOLD}================================================================${RESET}"
    echo -e "${YELLOW}${BOLD}Ready to Flash!${RESET}"
    echo -e "Put your keyboard into DFU Bootloader mode now:"
    echo -e "  1. Press ${BOLD}Fn + Esc${RESET} on the keyboard, OR"
    echo -e "  2. Unplug the USB cable, hold ${BOLD}Esc${RESET}, and reconnect the cable."
    echo -e "Waiting for WB32 DFU device..."
    echo -e "${BOLD}================================================================${RESET}\n"

    wb32-dfu-updater_cli -w -D "${REPO_DIR}/${BIN_NAME}" -R
    log_success "Firmware flashed successfully and keyboard rebooted!"
else
    echo -e "\nTo flash to your keyboard, put it in bootloader (Fn+Esc) and run:"
    echo -e "  ${BOLD}./setup_and_flash.sh --flash${RESET}"
    echo -e "  OR: ${BOLD}wb32-dfu-updater_cli -D ${REPO_DIR}/${BIN_NAME} -R${RESET}\n"
fi
