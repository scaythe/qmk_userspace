/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum preonic_layers {
  _QWERTY,
  _Q_SYMB,
  _BWPO_FOR_AZERTY,
  _BFA_SFT,
  _BFA_SYMB,
  _BWPO_FOR_CUSTOM,
  _BFC_SYMB,
  _LOWER,
  _RAISE,
  _ADJUST
};

// Holding Lower then Raise, or Raise then Lower, activates the Adjust layer.
#define LOWER OSL(_LOWER)
#define RAISE OSL(_RAISE)
#define ADJUST MO(_ADJUST)

#define O_LSFT OSM(MOD_LSFT)
#define O_RSFT OSM(MOD_RSFT)

#define QWERTY TO(_QWERTY)
#define BWPO_FA TO(_BWPO_FOR_AZERTY)
#define BWPO_FC TO(_BWPO_FOR_CUSTOM)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* qwerty
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Caps |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Delete|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | LAlt |Lower |Symbol|Space |Enter |Symbol|Raise | RAlt | GUI  | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  KC_ESC,  KC_1,    KC_2,    KC_3,  KC_4,         KC_5,   KC_6,   KC_7,         KC_8,    KC_9,    KC_0,    KC_GRV,  \
  KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,         KC_T,   KC_Y,   KC_U,         KC_I,    KC_O,    KC_P,    KC_CAPS, \
  KC_BSPC, KC_A,    KC_S,    KC_D,  KC_F,         KC_G,   KC_H,   KC_J,         KC_K,    KC_L,    KC_SCLN, KC_DEL,  \
  O_LSFT,  KC_Z,    KC_X,    KC_C,  KC_V,         KC_B,   KC_N,   KC_M,         KC_COMM, KC_DOT,  KC_SLSH, O_RSFT,  \
  KC_LCTL, KC_LGUI, KC_LALT, LOWER, OSL(_Q_SYMB), KC_SPC, KC_ENT, OSL(_Q_SYMB), RAISE,   KC_RALT, KC_RGUI, KC_RCTL  \
),

/* qwerty symbols
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   -  |   =  |   '  | nu\  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   [  |   ]  |   \  | nu#  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_Q_SYMB] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_QUOT, KC_NUBS, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, KC_BSLS, KC_NUHS, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* bwpo for azerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | F13  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   B  |   W  |   P  |   O  |   Z  |   M  |   V  |   D  |   L  |   J  | Caps |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp |   A  |   U  |   I  |   E  |   ,  |   C  |   T  |   S  |   R  |   N  |Delete|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift |   "  |   Y  |   X  |   .  |   K  |   '  |   Q  |   G  |   H  |   F  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | LAlt |Lower |Symbol|Space |Enter |Symbol|Raise | RAlt | GUI  | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_BWPO_FOR_AZERTY] = LAYOUT_preonic_grid( \
  _______,                S(KC_1), S(KC_2), S(KC_3), S(KC_4),        S(KC_5), S(KC_6), S(KC_7),        S(KC_8), S(KC_9), S(KC_0), KC_F13,                 \
  _______,                KC_B,    KC_Z,    KC_P,    KC_O,           KC_W,    KC_SCLN, KC_V,           KC_D,    KC_L,    KC_J,    _______,                \
  _______,                KC_Q,    KC_U,    KC_I,    KC_E,           KC_M,    KC_C,    KC_T,           KC_S,    KC_R,    KC_N,    _______,                \
  LM(_BFA_SFT, MOD_LSFT), KC_3,    KC_Y,    KC_X,    S(KC_COMM),     KC_K,    KC_4,    KC_A,           KC_G,    KC_H,    KC_F,    LM(_BFA_SFT, MOD_LSFT), \
  _______,                _______, _______, _______, OSL(_BFA_SYMB), _______, _______, OSL(_BFA_SYMB), _______, _______, _______, _______                 \
),

/* bwpo for azerty shifted
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |  >;< |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  >!< |      |      |  >:< |      |   ?  |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_BFA_SFT] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, KC_COMM, _______, _______, _______, _______, _______, _______, \
  _______, KC_SLSH, _______, _______, KC_DOT,  _______, S(KC_M), _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* bwpo for azerty symbols
 * ,-----------------------------------------------------------------------------------.
 * |      |      |  <!> |  <:> |  <;> |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   |  |   é  |   &  |   [  |   ]  |      |   =  |   %  |   ^  |   $  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   à  |   <  |   >  |   (  |   )  |   @  |   +  |   -  |   /  |   *  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   \  |   {  |   }  |   è  |   ~  |      |   _  |   `  |   #  |   ç  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_BFA_SYMB] = LAYOUT_preonic_grid( \
  _______, _______,    KC_SLSH,    KC_DOT,       KC_COMM,    _______,       _______,    _______,   _______,    _______,    _______, _______, \
  _______, ALGR(KC_6), KC_2,       KC_1,         ALGR(KC_5), ALGR(KC_MINS), _______,    KC_EQL,    S(KC_QUOT), KC_LBRC,    KC_RBRC, _______, \
  _______, KC_0,       KC_NUBS,    S(KC_NUBS),   KC_5,       KC_MINS,       ALGR(KC_0), S(KC_EQL), KC_6,       S(KC_DOT),  KC_NUHS, _______, \
  _______, ALGR(KC_8), ALGR(KC_4), ALGR(KC_EQL), KC_7,       ALGR(KC_2),    _______,    KC_8,      ALGR(KC_7), ALGR(KC_3), KC_9,    _______, \
  _______, _______,    _______,    _______,      _______,    _______,       _______,    _______,   _______,    _______,    _______, _______  \
),

/* bwpo for custom
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | F13  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Caps |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Delete|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | LAlt |Lower |Symbol|Space |Enter |Symbol|Raise | RAlt | GUI  | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_BWPO_FOR_CUSTOM] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______,        _______, _______, _______,        _______, _______, _______, KC_F13,  \
  _______, _______, _______, _______, _______,        _______, _______, _______,        _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,        _______, _______, _______,        _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,        _______, _______, _______,        _______, _______, _______, _______, \
  _______, _______, _______, _______, OSL(_BFC_SYMB), _______, _______, OSL(_BFC_SYMB), _______, _______, _______, _______  \
),

/* bwpo for custom symbols
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   |  |   É  |   &  |   [  |   ]  |      |   =  |   %  |   ^  |   $  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   À  |   <  |   >  |   (  |   )  |   @  |   +  |   -  |   /  |   *  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   \  |   {  |   }  |   È  |   ~  |      |   _  |   `  |   #  |   Ç  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_BFC_SYMB] = LAYOUT_preonic_grid( \
  _______, _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,       _______,      _______,       _______, \
  _______, ALGR(KC_Q), ALGR(KC_W), ALGR(KC_E), ALGR(KC_R), ALGR(KC_T), ALGR(KC_Y), ALGR(KC_U), ALGR(KC_I),    ALGR(KC_O),   ALGR(KC_P),    _______, \
  _______, ALGR(KC_A), ALGR(KC_S), ALGR(KC_D), ALGR(KC_F), ALGR(KC_G), ALGR(KC_H), ALGR(KC_J), ALGR(KC_K),    KC_NUBS,      ALGR(KC_SCLN), _______, \
  _______, ALGR(KC_Z), ALGR(KC_X), ALGR(KC_C), ALGR(KC_V), ALGR(KC_B), ALGR(KC_N), ALGR(KC_M), ALGR(KC_COMM), ALGR(KC_DOT), ALGR(KC_SLSH), _______, \
  _______, _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,       _______,      _______,       _______  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  F13 |  F14 |  F15 |  F16 |  F17 |  F18 |  F19 |  F20 |  F21 |  F22 |  F23 |  F24 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | XXXX | XXXX | XXXX | Play | Esc  | PgUp | Home |  Up  |  End |Insert|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Undo |  Cut | Copy |Paste |  F13 | PgDn | Left | Down |Right |PrtScr|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |Adjust|      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid( \
  KC_F13,  KC_F14,     KC_F15,     KC_F16,     KC_F17,     KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  \
  KC_F1,   KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_MPLY,    KC_ESC,  KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_INS,  _______, \
  _______, LCTL(KC_T), LCTL(KC_C), LCTL(KC_H), LCTL(KC_U), KC_F13,  KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PSCR, _______, \
  _______, _______,    _______,    _______,    _______,    _______, _______, _______, ADJUST,  _______, _______, _______  \
),

/* Raise
 * The accented letters need the bwpo(ortho) xkb layout, which puts them on
 * US keys that the grid lacks. The ù key also gives ù with an AZERTY layout.
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |      |      |      |      |      |      |      |      |      |      | F13  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |      |      |      |      |      |   *  |   7  |   8  |   9  |  -   | Caps |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp |   â  |   û  |   î  |   ê  |   ô  |   /  |   4  |   5  |   6  |  +   |Delete|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift |      |      |      |      |   ù  |   0  |   1  |   2  |   3  |Enter |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |Adjust|Symbol|Space |Enter |Symbol|Raise | Alt  | GUI  | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F13,  \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAST, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, _______, \
  _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_PSLS, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, _______, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_QUOT, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, _______, \
  _______, _______, _______, ADJUST,  _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Boot | Debug| Audio|      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |QWERTY|BWPO A|BWPO C|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  XXXXXXX, QK_BOOT, DB_TOGG, AU_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,  \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QWERTY,  BWPO_FA, BWPO_FC, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
)
};

#ifdef AUDIO_ENABLE
// Plays a short sound when a Lower, Raise, Adjust or symbol layer, or a one-shot
// modifier, is activated or released

#define LAYER_BIT(layer) ((layer_state_t)1 << (layer))
#define SYMBOL_LAYERS (LAYER_BIT(_Q_SYMB) | LAYER_BIT(_BFA_SYMB) | LAYER_BIT(_BFC_SYMB))
#define SIGNALED_LAYERS (LAYER_BIT(_LOWER) | LAYER_BIT(_RAISE) | LAYER_BIT(_ADJUST) | SYMBOL_LAYERS)

static float adjust_on_song[][2] = SONG(S__NOTE(_C6));
static float raise_on_song[][2] = SONG(S__NOTE(_G5));
static float symbols_on_song[][2] = SONG(S__NOTE(_E5));
static float lower_on_song[][2] = SONG(S__NOTE(_C5));
static float layer_off_song[][2] = SONG(S__NOTE(_C4));
static float oneshot_mods_on_song[][2] = SONG(S__NOTE(_A5), S__NOTE(_A5));
static float oneshot_mods_off_song[][2] = SONG(S__NOTE(_A4));

static bool layers_turned_on(layer_state_t before, layer_state_t after, layer_state_t layers);
static bool layers_turned_off(layer_state_t before, layer_state_t after, layer_state_t layers);

layer_state_t layer_state_set_user(layer_state_t state) {
  if (layers_turned_on(layer_state, state, LAYER_BIT(_ADJUST)))
    PLAY_SONG(adjust_on_song);
  else if (layers_turned_on(layer_state, state, LAYER_BIT(_RAISE)))
    PLAY_SONG(raise_on_song);
  else if (layers_turned_on(layer_state, state, LAYER_BIT(_LOWER)))
    PLAY_SONG(lower_on_song);
  else if (layers_turned_on(layer_state, state, SYMBOL_LAYERS))
    PLAY_SONG(symbols_on_song);
  else if (layers_turned_off(layer_state, state, SIGNALED_LAYERS))
    PLAY_SONG(layer_off_song);
  return state;
}

void oneshot_mods_changed_user(uint8_t mods) {
  if (mods)
    PLAY_SONG(oneshot_mods_on_song);
  else
    PLAY_SONG(oneshot_mods_off_song);
}

static bool layers_turned_on(layer_state_t before, layer_state_t after, layer_state_t layers) {
  return (~before & after & layers) != 0;
}

static bool layers_turned_off(layer_state_t before, layer_state_t after, layer_state_t layers) {
  return (before & ~after & layers) != 0;
}
#endif
