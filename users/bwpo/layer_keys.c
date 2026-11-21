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

#include "layer_keys.h"

// Like QMK, a pending layer ends after ONESHOT_TIMEOUT only when it is defined
// and positive
#if defined(ONESHOT_TIMEOUT) && ONESHOT_TIMEOUT > 0
#    define PENDING_LAYER_TIMES_OUT
#endif

// Number of layer keys that can be held or pending at the same time
#define MAX_LAYER_KEYS 8

typedef struct {
    keypos_t position;
    uint8_t  layer;
    uint16_t pressed_at;
    // A tap on an OSL key leaves its layer pending, a tap on an MO key does not
    bool taps_to_pending;
    // Released after a tap, its layer applies to the next key only
    bool pending;
    bool other_key_pressed;
    // Pressed while its layer was pending
    bool cancels_on_tap;
} layer_key_t;

// From the oldest pressed to the last pressed
static layer_key_t layer_keys[MAX_LAYER_KEYS];
static uint8_t     layer_key_count = 0;

// Layers that the layer keys turned on
static layer_state_t applied_layers = 0;

#ifdef PENDING_LAYER_TIMES_OUT
static uint16_t pending_since;
#endif

static bool is_layer_key(uint16_t keycode);
static bool is_modifier_key(uint16_t keycode);
#ifdef PENDING_LAYER_TIMES_OUT
static bool has_pending_layer_key(void);
#endif
static bool          process_other_key(uint16_t keycode, keyrecord_t *record);
static void          press_layer_key(uint16_t keycode, keypos_t position);
static uint8_t       get_key_layer(uint16_t keycode);
static void          release_layer_key(keypos_t position, uint16_t tapping_term);
static void          leave_layer_pending(layer_key_t *key);
static bool          is_pending_layer(uint8_t layer);
static void          mark_other_key_pressed(void);
static void          remove_pending_layer_key(void);
static void          add_layer_key(layer_key_t key);
static layer_key_t  *find_held_layer_key(keypos_t position);
static bool          leaves_layer_pending(const layer_key_t *key, uint16_t tapping_term);
static bool          is_layer_held_by_another_key(const layer_key_t *key);
static void          remove_layer_key(const layer_key_t *key);
static void          forget_layer_keys(void);
static void          apply_layer_keys(void);
static layer_state_t get_layer_keys_state(void);

bool process_layer_keys(uint16_t keycode, keyrecord_t *record) {
    if (!is_layer_key(keycode)) return process_other_key(keycode, record);
    if (record->event.pressed)
        press_layer_key(keycode, record->event.key);
    else
        release_layer_key(record->event.key, GET_TAPPING_TERM(keycode, record));
    return false;
}

// The pending layer applies to the key that QMK has just processed, and ends
// after it, unless that key is a modifier
void post_process_layer_keys(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed || is_layer_key(keycode) || is_modifier_key(keycode)) return;
    remove_pending_layer_key();
    apply_layer_keys();
}

void end_expired_pending_layer(void) {
#ifdef PENDING_LAYER_TIMES_OUT
    if (!has_pending_layer_key() || timer_elapsed(pending_since) < ONESHOT_TIMEOUT) return;
    remove_pending_layer_key();
    apply_layer_keys();
#endif
}

static bool is_layer_key(uint16_t keycode) {
    return IS_QK_ONE_SHOT_LAYER(keycode) || IS_QK_MOMENTARY(keycode);
}

static bool is_modifier_key(uint16_t keycode) {
    return IS_MODIFIER_KEYCODE(keycode) || IS_QK_ONE_SHOT_MOD(keycode) || IS_QK_LAYER_MOD(keycode);
}

#ifdef PENDING_LAYER_TIMES_OUT
static bool has_pending_layer_key(void) {
    for (uint8_t i = 0; i < layer_key_count; i++)
        if (layer_keys[i].pending) return true;
    return false;
}
#endif

// A TO key turns off every layer, those of the layer keys included
static bool process_other_key(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;
    mark_other_key_pressed();
    if (IS_QK_TO(keycode)) forget_layer_keys();
    return true;
}

static void press_layer_key(uint16_t keycode, keypos_t position) {
    uint8_t     layer = get_key_layer(keycode);
    layer_key_t key   = {
        .position        = position,
        .layer           = layer,
        .pressed_at      = timer_read(),
        .taps_to_pending = IS_QK_ONE_SHOT_LAYER(keycode),
        .cancels_on_tap  = is_pending_layer(layer),
    };
    mark_other_key_pressed();
    remove_pending_layer_key();
    add_layer_key(key);
    apply_layer_keys();
}

static uint8_t get_key_layer(uint16_t keycode) {
    if (IS_QK_ONE_SHOT_LAYER(keycode)) return QK_ONE_SHOT_LAYER_GET_LAYER(keycode);
    return QK_MOMENTARY_GET_LAYER(keycode);
}

static void release_layer_key(keypos_t position, uint16_t tapping_term) {
    layer_key_t *key = find_held_layer_key(position);
    if (key == NULL) return;
    if (leaves_layer_pending(key, tapping_term))
        leave_layer_pending(key);
    else
        remove_layer_key(key);
    apply_layer_keys();
}

static void leave_layer_pending(layer_key_t *key) {
    key->pending = true;
#ifdef PENDING_LAYER_TIMES_OUT
    pending_since = timer_read();
#endif
}

static bool is_pending_layer(uint8_t layer) {
    for (uint8_t i = 0; i < layer_key_count; i++)
        if (layer_keys[i].pending && layer_keys[i].layer == layer) return true;
    return false;
}

static void mark_other_key_pressed(void) {
    for (uint8_t i = 0; i < layer_key_count; i++)
        layer_keys[i].other_key_pressed = true;
}

static void remove_pending_layer_key(void) {
    for (uint8_t i = layer_key_count; i > 0; i--)
        if (layer_keys[i - 1].pending) remove_layer_key(&layer_keys[i - 1]);
}

// When MAX_LAYER_KEYS layer keys are already held or pending, the key does
// nothing
static void add_layer_key(layer_key_t key) {
    if (layer_key_count == MAX_LAYER_KEYS) return;
    layer_keys[layer_key_count++] = key;
}

static layer_key_t *find_held_layer_key(keypos_t position) {
    for (uint8_t i = 0; i < layer_key_count; i++)
        if (!layer_keys[i].pending && KEYEQ(layer_keys[i].position, position)) return &layer_keys[i];
    return NULL;
}

// A tap on the key of a pending layer cancels that layer. A tap on a key whose
// layer another held key applies does nothing. A press longer than the tapping
// term is a hold, even when no other key is pressed.
static bool leaves_layer_pending(const layer_key_t *key, uint16_t tapping_term) {
    return key->taps_to_pending && !key->other_key_pressed && timer_elapsed(key->pressed_at) < tapping_term && !key->cancels_on_tap && !is_layer_held_by_another_key(key);
}

static bool is_layer_held_by_another_key(const layer_key_t *key) {
    for (uint8_t i = 0; i < layer_key_count; i++)
        if (&layer_keys[i] != key && !layer_keys[i].pending && layer_keys[i].layer == key->layer) return true;
    return false;
}

static void remove_layer_key(const layer_key_t *key) {
    uint8_t index = key - layer_keys;
    for (uint8_t i = index; i + 1 < layer_key_count; i++)
        layer_keys[i] = layer_keys[i + 1];
    layer_key_count--;
}

static void forget_layer_keys(void) {
    layer_key_count = 0;
    applied_layers  = 0;
}

static void apply_layer_keys(void) {
    layer_state_t layers = get_layer_keys_state();
    if (layers == applied_layers) return;
    layer_state_set((layer_state & ~applied_layers) | layers);
    applied_layers = layers;
}

#ifdef LAST_LAYER_KEY_WINS
// Only the layer of the last pressed layer key applies, even when the layer of
// an older key comes after it in the keymap
static layer_state_t get_layer_keys_state(void) {
    if (layer_key_count == 0) return 0;
    return (layer_state_t)1 << layer_keys[layer_key_count - 1].layer;
}
#else
// The layers of all the layer keys apply, and QMK gives precedence to the one
// that comes last in the keymap
static layer_state_t get_layer_keys_state(void) {
    layer_state_t layers = 0;
    for (uint8_t i = 0; i < layer_key_count; i++)
        layers |= (layer_state_t)1 << layer_keys[i].layer;
    return layers;
}
#endif
