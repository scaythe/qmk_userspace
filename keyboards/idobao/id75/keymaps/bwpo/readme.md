# bwpo keymap for the ID75 v2

A BÉPO-based layout for a 5×15 ortholinear grid, with direct access to the
digits and to the symbols of the BÉPO digit row on the home row. The three
middle columns hold the navigation keys.

`layout.kle.json` holds the diagram of the layers. To view it, paste its content
in the Raw data tab of [keyboard-layout-editor](https://www.keyboard-layout-editor.com).

## Flashing

No task of this repository flashes the ID75. Its bootloader is `atmel-dfu`,
which `dfu-programmer` flashes. The `qmk` distrobox container only provides
`dfu-util`.

To put the ID75 in bootloader mode, tap Lower, then hold the Adjust key and
press the key at the position of B. Holding Esc while plugging the keyboard in
also puts it in bootloader mode.

## Host layout

The default layer is a standard QWERTY layout, for a host with a QWERTY layout.
Keys on the Adjust layer switch to the layers that produce the bwpo layout:

- BWPO C, for a host that uses the `bwpo(ortho)` xkb layout. It sends the
  QWERTY keycodes that this xkb layout turns into the bwpo layout
- BWPO A, for a host that uses a standard AZERTY layout
- QWERTY switches back to the default layer

The `xkb` folder at the root of this repository contains the `bwpo(ortho)` xkb
layout. To install it on Linux, copy or symlink that folder to `~/.config/xkb`.

The Lock key sends Super+End. The desktop must bind this shortcut to locking
the session.

## Layers

- The two Symbol keys of the thumb row activate a symbol layer. On the default
  layer, this symbol layer holds the US keys that the grid lacks
- The Alt key of the right hand sends right Alt, which a host layout with AltGr
  uses as AltGr
- Lower activates the function keys, the numeric keypad, the navigation keys,
  the editing shortcuts and the accented letters â, û, î, ê, ô and ù. The
  numeric keypad gives digits only when Num Lock is on. The accented letters
  need the `bwpo(ortho)` xkb layout, except ù, which also works on a host with a
  standard AZERTY layout
- Holding the Adjust key of the Lower layer activates the Adjust layer, which
  holds the keys for the bootloader and the host layouts

## One-shot keys

Lower and the Symbol keys are one-shot layer keys. The [readme of the bwpo
userspace](../../../../../users/bwpo/readme.md#layer-keys) describes how they
work.

Shift is a one-shot modifier. A tap applies it to the next key only, and holding
it applies it until its release. If you tap Shift and press no other key, it is
released after the delay set by `ONESHOT_TIMEOUT` in `config.h`. On the BWPO A
layer, Shift is a regular key.
