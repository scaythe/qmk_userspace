# bwpo keymap for the Preonic rev3

A BÉPO-based layout for a 5×12 ortholinear grid, with direct access to the
digits and to the symbols of the BÉPO digit row on the home row.

The default layer sends QWERTY keycodes, and the host translates them with the
`bwpo(preonic)` xkb layout. The `xkb` folder at the root of this repository
contains this layout. To install it on Linux, copy that folder to
`~/.config/xkb`.

Lower and Raise are one-shot layer keys. A tap activates the layer for the next
key only, and holding the key activates the layer until its release. Holding
both activates the Adjust layer.

Keys on the Adjust layer switch to the layers that produce the same layout on a
host that uses a standard QWERTY or AZERTY layout.
