# Disable USB wakeup by default, harden the firmware guard

Status: accepted

The keyboard advertises USB Remote Wakeup. The rear slider stays electrically closed, and a device reset or reconnect can wake a suspended host. The host enables wakeup for this device by default, so `systemctl suspend` woke within milliseconds. The udev rule now sets `power/wakeup` to `disabled` for `504b:320f`. The firmware also masks the slider, waits about 255 ms after suspend entry, requires a key to be released and pressed again, and resets its state on a new suspend entry.

## Considered options

- Firmware guard only: cannot stop a host wake caused by a device reset or reconnect.
- Disable wakeup for all USB devices: broader than needed and breaks wake for other peripherals.
- Disable wakeup for this keyboard by default, with an opt-in: keeps suspend reliable and leaves the choice to the user.

## Consequences

The power button wakes the machine by default. Keyboard wake requires editing the udev rule. Users who opt in still rely on the firmware guard, which cannot prevent a reset or reconnect from waking the host. `USB_SUSPEND_WAKEUP_DELAY` only delays the driver restart after a firmware-initiated wake; it does not prevent wake.
