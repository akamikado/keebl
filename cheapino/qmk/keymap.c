#include QMK_KEYBOARD_H

tap_dance_action_t tap_dance_actions[] = {};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // QWERTY Layout
    [0] = LAYOUT_split_3x5_3(
       KC_Q,         KC_W,         KC_E,         KC_R,          KC_T,        KC_Y,  KC_U,         KC_I,         KC_O,         KC_P,
       LALT_T(KC_A), LGUI_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F),  KC_G,        KC_H,  RCTL_T(KC_J), RSFT_T(KC_K), RGUI_T(KC_L), RALT_T(KC_SCLN), 
       KC_Z,         KC_X,         KC_C,         KC_V,          KC_B,        KC_N,  KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,
                                   TO(1),        KC_BSPC,       TO(3),       KC_NO, KC_SPC,       KC_ENT
       ),

    [1] = LAYOUT_split_3x5_3(
       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,      KC_7,    KC_8,    KC_9,    KC_0, 
       KC_LALT, KC_LGUI, KC_LSFT, KC_LCTL, KC_TAB,      KC_DELETE, KC_RCTL, KC_RSFT, KC_RGUI, KC_RALT,
       KC_NO,   KC_GRV,  KC_MINS, KC_EQL,  KC_QUOT,     KC_LBRC,   KC_RBRC, KC_BSLS, KC_NO,   KC_NO,
                         TO(1),   KC_TRNS, KC_TRNS,     KC_TRNS,   KC_TRNS, TO(0)
       ),

    [2] = LAYOUT_split_3x5_3(
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8, KC_F9,    KC_F10, 
       KC_LALT, KC_LGUI, KC_LSFT, KC_LCTL, KC_NO,        KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_NO, 
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_NO,   KC_NO, KC_NO,    KC_NO,
                         TO(1),   KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, TO(0)
       ),

    };


uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    // Disable key repeating for all keys except j, k and l
    case RCTL_T(KC_J):
    case RSFT_T(KC_K):
    case RGUI_T(KC_L):
          return QUICK_TAP_TERM;
    default:
          return 0;
  }
}

const uint16_t PROGMEM to2_layer0[] = {KC_ENT, TO(1), COMBO_END};
const uint16_t PROGMEM to2_default[] = {TO(0), TO(1), COMBO_END};

const uint16_t PROGMEM spc_bspc_esc[] = {KC_BSPC, KC_SPC, COMBO_END};

const uint16_t PROGMEM f11[] = {KC_F1, KC_F10, COMBO_END};
const uint16_t PROGMEM f12[] = {KC_F2, KC_F10, COMBO_END};

combo_t key_combos[] = {
  COMBO(to2_layer0, TO(2)),
  COMBO(to2_default, TO(2)),

  COMBO(spc_bspc_esc, KC_ESC),

  COMBO(f11, KC_F11),
  COMBO(f12, KC_F12),
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_split_3x5_3(
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
                  'L', 'L', 'L',  'R', 'R', 'R'
    );

#define IDLE_TIMEOUT_MS 5000

static uint32_t reset_layer(uint32_t trigger_time, void* cb_arg) {
  switch (layer_state) {
    case 1:
    case 2:
      layer_move(0);
      break;
  }
  return 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  // Reset keyboard to layer 0 when idle for IDLE_TIMEOUT_MS
  static deferred_token idle_token = INVALID_DEFERRED_TOKEN;
  if (!extend_deferred_exec(idle_token, IDLE_TIMEOUT_MS)) {
    idle_token = defer_exec(IDLE_TIMEOUT_MS, reset_layer, NULL);
  }

  return true;
}
