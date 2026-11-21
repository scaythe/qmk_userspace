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

static uint8_t get_key_mods_on_both_sides(uint16_t keycode);

// A tap on an OSM key cancels its pending modifier, whether the pending
// modifier comes from the same key or from its mirror on the other side. QMK
// adds the modifier again on a slow tap, and ignores a quick one.
bool process_oneshot_mods(uint16_t keycode, keyrecord_t *record) {
    if (!IS_QK_ONE_SHOT_MOD(keycode) || !record->event.pressed || record->tap.count == 0) return true;
    uint8_t mods = get_key_mods_on_both_sides(keycode);
    if ((get_oneshot_mods() & mods) == 0) return true;
    del_oneshot_mods(mods);
    return false;
}

// The 5-bit modifiers of an OSM keycode hold the four modifiers in the bits of
// MOD_HYPR, and the right side in the fifth bit. The 8-bit modifiers hold the
// left side in the low four bits and the right side in the high four bits.
static uint8_t get_key_mods_on_both_sides(uint16_t keycode) {
    uint8_t mods = QK_ONE_SHOT_MOD_GET_MODS(keycode) & MOD_HYPR;
    return mods | mods << 4;
}
