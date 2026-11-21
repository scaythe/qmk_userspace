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

// Layer keys are the OSL and MO keys of the keymap. These functions handle them
// in place of QMK, as readme.md describes.

#pragma once

#include QMK_KEYBOARD_H

bool process_layer_keys(uint16_t keycode, keyrecord_t *record);
void post_process_layer_keys(uint16_t keycode, keyrecord_t *record);
void end_expired_pending_layer(void);
