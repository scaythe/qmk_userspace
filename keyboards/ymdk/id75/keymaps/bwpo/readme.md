# bwpo keymap for the ID75

A BÉPO-based layout for a 5×15 ortholinear grid, with direct access to the
digits and to the symbols of the BÉPO digit row on the home row. The three
middle columns hold the navigation keys.

The keymap is for the Idobao x YMDK ID75 with an RP2040, the `ymdk/id75/rp2040`
keyboard in QMK. The firmware leaves the underglow LEDs off.

`layout.kle.json` holds the diagram of the layers. To view it, paste its content
in the Raw data tab of
[keyboard-layout-editor](https://www.keyboard-layout-editor.com).

## Flashing

`mise run flash:id75` shows the commit and the date of the latest GitHub release
of this repository, and asks for confirmation. It then downloads the firmware
from this release, waits until the ID75 is in bootloader mode, and flashes it.

With `--local`, `mise run flash:id75` flashes the locally compiled firmware,
`ymdk_id75_rp2040_bwpo.uf2` at the root of the repository, instead of the
release. The task shows the modification date of this file before it asks for
confirmation.

With `--yes` or `-y`, `mise run flash:id75` flashes without asking for
confirmation.

In bootloader mode, the RP2040 of the ID75 shows up as a USB drive named
`RPI-RP2`. The task waits until the desktop mounts this drive, then copies the
firmware to it. The keyboard restarts with the new firmware once the copy ends.
Without `--local`, the task also needs `gh` authenticated on GitHub. mise
installs `gh`, and the `nu` that runs the task, from the `[tools]` section of
`mise.toml`.

To put the ID75 in bootloader mode, tap Lower, then hold the Adjust key and
press the key at the position of B. Two quick presses on the reset button under
the PCB, or holding the top-left key while plugging the keyboard in, also put it
in bootloader mode.

## Host keyboard layout

The default layer sends the keys of a standard QWERTY keyboard, for a host that
uses a QWERTY keyboard layout. Keys on the Adjust layer switch to the following
layers:

- QWERTY is the default layer
- BWPO C is for a host that uses the `bwpo(ortho)` keyboard layout. It sends the
  QWERTY keycodes that this keyboard layout turns into bwpo
- BWPO A is for a host that uses a standard AZERTY keyboard layout. It sends the
  keycodes that this keyboard layout turns into bwpo

The `xkb` folder at the root of this repository contains the `bwpo(ortho)`
keyboard layout. To install it on Linux, copy or symlink that folder to
`~/.config/xkb`.

The Compose key sends Menu, which the `bwpo(ortho)` keyboard layout turns into
Compose. With another keyboard layout, the xkb option `compose:menu` does the
same.

The Lock key sends Super+End. The desktop must bind this shortcut to locking the
session.

## Layers

- The two Symbol keys of the thumb row activate a symbol layer. On the default
  layer, this symbol layer holds the US keys that the grid lacks. On the BWPO C
  layer, the Symbol keys send right Alt instead, which the `bwpo(ortho)`
  keyboard layout uses as AltGr
- Both Alt keys send left Alt, which stays Alt with a keyboard layout that uses
  right Alt as AltGr
- Lower activates the function keys, the numeric keypad, the navigation keys,
  the editing shortcuts and the accented letters â, û, î, ê, ô and ù. The
  numeric keypad gives digits only when Num Lock is on, and the Num Lock key is
  above 7. The accented letters need the `bwpo(ortho)` keyboard layout, except
  ù, which also works with a standard AZERTY keyboard layout
- Holding the Adjust key of the Lower layer activates the Adjust layer, which
  holds the keys for the bootloader and the layers for the host keyboard layouts

## One-shot keys

Lower and the Symbol keys are one-shot layer keys, except the Symbol keys of the
BWPO C layer. The
[readme of the bwpo userspace](../../../../../users/bwpo/readme.md#layer-keys)
describes how they work.

Shift and the Symbol keys of the BWPO C layer are one-shot modifiers. A tap
applies the modifier to the next key only, and holding the key applies it until
its release. If you tap the key and press no other key, the modifier is released
after the delay set by `ONESHOT_TIMEOUT` in `config.h`. The
[readme of the bwpo userspace](../../../../../users/bwpo/readme.md#one-shot-modifiers)
describes how a tap on the key cancels the modifier while it is pending.

The Shift keys turn Caps Lock on and off by sending the Caps Lock keycode, as
the
[readme of the bwpo userspace](../../../../../users/bwpo/readme.md#one-shot-modifiers)
describes. The host must not remap that keycode, as the xkb option
`compose:caps` does.
