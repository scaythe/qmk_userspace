# bwpo keymap for the Preonic rev3

A BÉPO-based layout for a 5×12 ortholinear grid, with direct access to the
digits and to the symbols of the BÉPO digit row on the home row.

`layout.kle.json` holds the diagram of the layers. To view it, paste its content
in the Raw data tab of [keyboard-layout-editor](https://www.keyboard-layout-editor.com).

## Host layout

The default layer sends the QWERTY keycodes that the `bwpo(preonic)` xkb layout
maps to the bwpo layout. The `xkb` folder at the root of this repository
contains this layout. To install it on Linux, copy or symlink that folder to
`~/.config/xkb`.

Keys on the Adjust layer switch to the layers that produce the same layout on a
host that uses a standard QWERTY or AZERTY layout.

## Layers

- AltGr activates the symbol layer
- Lower activates the function keys, the navigation keys, the editing shortcuts
  and Play/Pause
- Raise activates the numeric keypad and the accented letters â, û, î, ê, ô and
  ù. The accented letters need the `bwpo(preonic)` xkb layout, except ù, which
  also works on a host with a standard AZERTY layout
- Holding Lower and Raise activates the Adjust layer, which holds the keys for
  the bootloader, the debug mode, the audio and the host layouts

## One-shot keys

Lower, Raise, AltGr and Shift are one-shot keys. A tap applies the layer or the
modifier to the next key only, and holding the key applies it until its release.
If you tap a one-shot key and press no other key, it is released after the delay
set by `ONESHOT_TIMEOUT` in `config.h`.

On the layers for a host with a standard QWERTY or AZERTY layout, Shift is a
regular key.

## Sounds

The keyboard plays a short sound when a Lower, Raise, Adjust or symbol layer, or
a one-shot modifier, is activated or released. The Audio key of the Adjust layer
turns the audio on or off.
