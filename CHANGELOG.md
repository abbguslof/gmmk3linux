# Changelog

## 1.0.0 - 2026-11-01

### Added

- Public release documentation, glossary, and three ADRs.
- SHA-256 for the prebuilt binary.
- Pinned upstream QMK commit in the build script.
- Released-then-pressed wake guard with suspend-entry reset.

### Changed

- Debounce is now `asym_eager_defer_pk` with `DEBOUNCE 8`: immediate press, 8 ms deferred release.
- The udev rule disables USB wakeup for `504b:320f` by default. A commented rule enables keyboard wake.
- The build script checks out the pinned commit, restores tracked files, and prints tool versions.
- Removed duplicate root copies of `config.h`, `keymap.c`, `rules.mk`, and `info.json`.
- Removed overlay files that were byte-identical to upstream.

### Fixed

- Double letters on release: debounce now uses `asym_eager_defer_pk` at 8 ms. Verify on `ä`, `r`, and `i` after flashing.
- Immediate wake on suspend: the udev rule disables wakeup by default; the firmware guard is secondary.
- Recovery instructions no longer claim `Space + B`. This QMK build uses Bootmagic Lite with the `Esc` key only.
