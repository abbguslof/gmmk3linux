# Use eager press and an 8 ms deferred release

Status: accepted

The board showed double letters on `ä`, `r`, and `i`. A symmetric 6 ms debounce reduced but did not remove them, and it added 6 ms to every keydown. The firmware now uses `asym_eager_defer_pk` with `DEBOUNCE 8`: a press is reported on the first scan, and a release waits for 8 ms of stable contact.

## Considered options

- `sym_defer_pk` at 8 to 10 ms: filters both edges but delays keydown by the same amount.
- `asym_eager_defer_pk` at 5 ms: the previous setting, which still chattered.
- Repair or replace the switches: fixes a worn switch but does not help a board that is still chattering.

## Consequences

Keydown latency stays low, which matters for games. Releases are 8 ms late and taps shorter than 8 ms can be stretched to about 16 ms. If a duplicate appears on press instead of release, switch to `sym_defer_pk` and accept the keydown delay. `asym_eager_defer_pk` caps `DEBOUNCE` at 127 ms.
