/* Copyright 2024 Glorious, LLC
 * Copyright 2026 gulo
 *
 * GMMK 3 Pro 75% ISO (WB32FQ95) - Performance Configuration
 */

#pragma once

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
 */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* External spi flash */
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C4

/* SPI Config for LED Driver */
#define SPI_DRIVER SPIDQ
#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A7
#define SPI_MISO_PIN A6

#define AW20216S_CS_PIN_1 C5
#define AW20216S_CS_PIN_2 B11
#define AW20216S_EN_PIN C13

#define DRIVER_1_LED_TOTAL (67)
#define DRIVER_2_LED_TOTAL (59)
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

/* Performance & Low Latency */
#define USB_POLLING_INTERVAL_MS 1 // 1000Hz (1ms) USB Polling Rate
#define FORCE_NKRO                // Always active N-Key Rollover
#define DEBOUNCE                                                               \
  3 // 5ms release defer filter with asym_eager_defer_pk (0ms keydown delay, 0
    // chatter)
#define MATRIX_IO_DELAY                                                        \
  10 // Lowered from default 30us to 10us for ultra-fast matrix scanning
#define RGB_MATRIX_LED_FLUSH_LIMIT                                             \
  16 // Cap RGB flushes to 60 FPS to prevent bus throttling
#define RGB_MATRIX_LED_PROCESS_LIMIT                                           \
  25 // Limit RGB calculation per scan to maintain peak polling

/* VIA Dynamic Keymap Layers */
#define DYNAMIC_KEYMAP_LAYER_COUNT 4 // Linux, Mac, Win, and Fn

/* Power Management */
#define RGB_MATRIX_SLEEP // Shut down LEDs when USB host suspends/sleeps
