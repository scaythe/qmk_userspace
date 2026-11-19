# bwpo keymap for the Preonic rev3

A BÉPO-based layout for a 5×12 ortholinear grid, with direct access to the
digits and to the symbols of the BÉPO digit row on the home row.

The default layer sends QWERTY keycodes, and the host translates them with the
`bwpo(preonic)` xkb layout. The `xkb` folder at the root of this repository
contains this layout. To install it on Linux, copy that folder to
`~/.config/xkb`.

Lower, Raise, AltGr and Shift are one-shot keys. A tap applies the layer or the
modifier to the next key only, and holding the key applies it until its release.
On the layers for a host with a standard QWERTY or AZERTY layout, Shift is a
regular key. Holding Lower and Raise activates the Adjust layer.

Keys on the Adjust layer switch to the layers that produce the same layout on a
host that uses a standard QWERTY or AZERTY layout.
