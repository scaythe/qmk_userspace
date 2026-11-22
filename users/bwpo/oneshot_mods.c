/* This program is free software: you can redistribute it and/or modify
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

#include "oneshot_mods.h"

// The 5-bit modifiers of an OSM keycode hold the four modifiers in the bits of
// MOD_HYPR, and the right side in the fifth bit. The 8-bit modifiers hold the
// left side in the low four bits and the right side in the high four bits.
static const uint8_t RIGHT_SIDE_BIT = MOD_RCTL & ~MOD_LCTL;

static bool    is_caps_lock_toggle(uint16_t keycode);
static bool    process_caps_lock_toggle(void);
static uint8_t get_key_mods_on_side(uint16_t keycode);
static uint8_t get_mirror_mods(uint8_t mods);
static uint8_t get_key_mods_on_both_sides(uint16_t keycode);

// A tap on an OSM key cancels its pending modifier, whether the pending
// modifier comes from the same key or from its mirror on the other side. QMK
// adds the modifier again on a slow tap, and ignores a quick one. A tap on a
// one-shot Shift toggles Caps Lock instead in the cases that
// is_caps_lock_toggle describes.
bool process_oneshot_mods(uint16_t keycode, keyrecord_t *record) {
    if (!IS_QK_ONE_SHOT_MOD(keycode) || !record->event.pressed || record->tap.count == 0) return true;
    if (is_caps_lock_toggle(keycode)) return process_caps_lock_toggle();
    uint8_t mods = get_key_mods_on_both_sides(keycode);
    if ((get_oneshot_mods() & mods) == 0) return true;
    del_oneshot_mods(mods);
    return false;
}

// A tap on a one-shot Shift toggles Caps Lock when Caps Lock is on, or when the
// Shift of the other side is held or pending. The host reports the state of
// Caps Lock through the keyboard LEDs.
static bool is_caps_lock_toggle(uint16_t keycode) {
    uint8_t mods = get_key_mods_on_side(keycode);
    if (mods != MOD_BIT(KC_LSFT) && mods != MOD_BIT(KC_RSFT)) return false;
    if (host_keyboard_led_state().caps_lock) return true;
    return (get_mods() | get_oneshot_mods()) & get_mirror_mods(mods);
}

// Sends Caps Lock and cancels a pending Shift. Like the process functions of
// QMK, it returns false, so that QMK does not process the tap of the Shift key.
static bool process_caps_lock_toggle(void) {
    del_oneshot_mods(MOD_MASK_SHIFT);
    tap_code(KC_CAPS);
    return false;
}

static uint8_t get_key_mods_on_side(uint16_t keycode) {
    uint8_t mods      = QK_ONE_SHOT_MOD_GET_MODS(keycode);
    uint8_t four_mods = mods & MOD_HYPR;
    if (mods & RIGHT_SIDE_BIT) return four_mods << 4;
    return four_mods;
}

static uint8_t get_mirror_mods(uint8_t mods) {
    return (uint8_t)(mods << 4 | mods >> 4);
}

static uint8_t get_key_mods_on_both_sides(uint16_t keycode) {
    uint8_t mods = QK_ONE_SHOT_MOD_GET_MODS(keycode) & MOD_HYPR;
    return mods | mods << 4;
}
