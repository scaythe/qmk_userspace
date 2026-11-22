# bwpo userspace

Code shared by the bwpo keymaps. QMK builds it with every keymap named `bwpo`.

## Layer keys

`layer_keys.c` handles the OSL and MO keys of the keymaps in place of QMK:

- A press of a layer key that lasts longer than the tapping term of QMK,
  `TAPPING_TERM`, is a hold, even when no other key is pressed. A shorter press
  is a tap
- A held layer key applies its layer until its release
- A tap on an OSL key leaves its layer pending: the layer applies to the next
  key only. If no other key is pressed, the layer ends after the delay set by
  `ONESHOT_TIMEOUT` in the `config.h` of the keymap. If the `config.h` of the
  keymap does not set `ONESHOT_TIMEOUT` to a positive value, the layer stays
  pending until the next key press
- When several layer keys are held or pending, their layers apply together, and
  the one that comes last in the keymap takes precedence, as in QMK
- If the `config.h` of the keymap defines `LAST_LAYER_KEY_WINS`, only the layer
  of the last pressed layer key applies, even when the layer of an older one
  comes after it in the keymap. When the last one is released, the layer of the
  previous one applies again
- A layer key pressed while a layer is pending ends that layer, then has its
  usual effect
- A modifier key, regular or one-shot, leaves a pending layer pending
- A tap on a key of the pending layer cancels that layer. Holding that key
  applies the layer until its release
- A tap on an OSL key does nothing when a held key already applies its layer
- A TO key ends the layers of every layer key

## One-shot modifiers

`oneshot_mods.c` cancels a pending one-shot modifier when its OSM key, or the
OSM key of the same modifier on the other side, is tapped. QMK adds the modifier
again on a slow tap, and ignores a quick one.

Tapping both Shift keys turns Caps Lock on, and tapping one of them turns it
off. When the Shift of the other side is held or pending, or when Caps Lock is
on, a tap on a one-shot Shift sends Caps Lock instead, and cancels a pending
Shift. The host reports the state of Caps Lock through the keyboard LEDs.
