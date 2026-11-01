# Read the rear slider from matrix column 7

Status: accepted

The vendor firmware read the rear slider from `A13`, which is the WB32 SWDIO/JTAG pin, so the read failed. The slider is wired to matrix column 7 and closes that column to row 11, 12, or 13. The firmware samples those three rows in `housekeeping_task_user()` every 25 ms and selects the profile from the result.

## Considered options

- Use `DIP_SWITCH_PINS { A13 }`: the pin is not a usable GPIO on this MCU.
- Add a dedicated GPIO: the switch is not wired to one.
- Scan the slider as matrix keys: works with the existing matrix hardware and needs no board changes.

## Consequences

The slider looks like a held key to QMK. Every suspend and wake path must mask column 7 on rows 11 to 13. The VIA layout does not expose those matrix positions as normal keys. Profile changes wait up to 25 ms for the next poll, which is acceptable because the slider moves by hand.
