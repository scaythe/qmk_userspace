# bwpo keymap for the Preonic rev3

A BÉPO-based layout for a 5×12 ortholinear grid, with direct access to the digits and to the symbols of the BÉPO digit row on the home row.

`layout.kle.json` holds the diagram of the layers. To view it, paste its content in the Raw data tab of [keyboard-layout-editor](https://www.keyboard-layout-editor.com).

## Flashing

`mise run flash-preonic` shows the commit and the date of the latest GitHub release of this repository, and asks for confirmation. It then downloads the firmware from this release, waits a few seconds so that you can put the Preonic in bootloader mode, and flashes it.

With `--local`, `mise run flash-preonic` flashes `preonic_rev3_bwpo.bin` instead. `qmk compile` copies this file to the root of the repository. The task shows the modification date of this file before it asks for confirmation.

The task flashes with the `dfu-util` of the distrobox container `qmk`. If this container does not exist, the task creates it from `distrobox.ini` at the root of this repository. Without `--local`, the task also needs `gh` authenticated on GitHub. mise installs `gh`, and the `nu` that runs the task, from the `[tools]` section of `mise.toml`.

## Host keyboard layout

The default layer sends the keys of a standard QWERTY keyboard, for a host that uses a QWERTY keyboard layout. Keys on the Adjust layer switch to the following layers:

- QWERTY is the default layer
- BWPO C is for a host that uses the `bwpo(ortho)` keyboard layout. It sends the QWERTY keycodes that this keyboard layout turns into bwpo
- BWPO A is for a host that uses a standard AZERTY keyboard layout. It sends the keycodes that this keyboard layout turns into bwpo

The `xkb` folder at the root of this repository contains the `bwpo(ortho)` keyboard layout. To install it on Linux, copy or symlink that folder to `~/.config/xkb`.

## Layers

- The two Symbol keys of the thumb row activate a symbol layer. On the default layer, this symbol layer holds the US keys that the grid lacks
- The Alt key of the right hand sends right Alt, which a keyboard layout with AltGr uses as AltGr
- Lower activates the function keys, the navigation keys, the editing shortcuts and Play/Pause
- Raise activates the numeric keypad and the accented letters â, û, î, ê, ô and ù. The accented letters need the `bwpo(ortho)` keyboard layout, except ù, which also works with a standard AZERTY keyboard layout
- Holding Lower and Raise activates the Adjust layer, which holds the keys for the bootloader, the debug mode, the audio and the layers for the host keyboard layouts

## One-shot keys

Lower, Raise and the Symbol keys are one-shot layer keys. The [readme of the bwpo userspace](../../../../users/bwpo/readme.md#layer-keys) describes how they work.

Shift is a one-shot modifier. A tap applies it to the next key only, and holding it applies it until its release. If you tap Shift and press no other key, it is released after the delay set by `ONESHOT_TIMEOUT` in `config.h`. The [readme of the bwpo userspace](../../../../users/bwpo/readme.md#one-shot-modifiers) describes how a tap on Shift cancels it while it is pending.

## Sounds

The keyboard plays a short sound when a Lower, Raise, Adjust or symbol layer, or a one-shot modifier, is activated or released. The Audio key of the Adjust layer turns the audio on or off.
