# bwpo keymap for the Preonic rev3

A BÉPO-based layout for a 5×12 ortholinear grid, with direct access to the
digits and to the symbols of the BÉPO digit row on the home row.

`layout.kle.json` holds the diagram of the layers. To view it, paste its content
in the Raw data tab of [keyboard-layout-editor](https://www.keyboard-layout-editor.com).

## Flashing

`mise run flash-preonic` shows the commit and the date of the latest GitHub
release of this repository, and asks for confirmation. It then downloads the
firmware from this release, waits a few seconds so that you can put the Preonic
in bootloader mode, and flashes it.

The task flashes with the `dfu-util` of the distrobox container `qmk`. If this
container does not exist, the task creates it from `distrobox.ini` at the root
of this repository. The task also needs `gh` authenticated on GitHub. mise
installs `gh`, and the `nu` that runs the task, from the `[tools]` section of
`mise.toml`.

## Host layout

The default layer is a standard QWERTY layout, for a host with a QWERTY layout.
Keys on the Adjust layer switch to other layers:

- BWPO C, for a host that uses the `bwpo(ortho)` xkb layout. It sends the
  QWERTY keycodes that this xkb layout turns into the bwpo layout
- BWPO A produces the bwpo layout on a host that uses a standard AZERTY layout
- QWERTY switches back to the default layer

The `xkb` folder at the root of this repository contains the `bwpo(ortho)` xkb
layout. To install it on Linux, copy or symlink that folder to `~/.config/xkb`.

## Layers

- The two Symbol keys of the thumb row activate a symbol layer. On the default
  layer, this symbol layer holds the US keys that the grid lacks. On the Lower
  and Raise layers, the Symbol keys are AltGr keys
- The Alt key of the right hand sends right Alt, which a host layout with AltGr
  uses as AltGr
- Lower activates the function keys, the navigation keys, the editing shortcuts
  and Play/Pause
- Raise activates the numeric keypad and the accented letters â, û, î, ê, ô and
  ù. The accented letters need the `bwpo(ortho)` xkb layout, except ù, which
  also works on a host with a standard AZERTY layout
- Holding Lower and Raise activates the Adjust layer, which holds the keys for
  the bootloader, the debug mode, the audio and the host layouts

## One-shot keys

Lower, Raise, the Symbol keys and Shift are one-shot keys. A tap applies the
layer or the modifier to the next key only, and holding the key applies it until
its release. If you tap a one-shot key and press no other key, it is released
after the delay set by `ONESHOT_TIMEOUT` in `config.h`.

On the BWPO A layer, Shift is a regular key.

## Sounds

The keyboard plays a short sound when a Lower, Raise, Adjust or symbol layer, or
a one-shot modifier, is activated or released. The Audio key of the Adjust layer
turns the audio on or off.
