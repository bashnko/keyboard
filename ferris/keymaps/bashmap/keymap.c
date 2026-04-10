#include QMK_KEYBOARD_H

void matrix_init_user(void) {
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

enum custom_keycodes {
    CTRL_SPC = SAFE_RANGE,
    CTRL_BSPC,
    CTRL_Y,
    SFT_TAB
};

// Macros 
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTRL_SPC:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_SPC);
                unregister_code(KC_LCTL);
            }
            return false;
        case CTRL_BSPC:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_BSPC);
                unregister_code(KC_LCTL);
            }
            return false;
         case CTRL_Y:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_Y);
                unregister_code(KC_LCTL);
            }
            return false;
        case SFT_TAB:
            if (record->event.pressed){
                register_code(KC_LSFT);
                tap_code(KC_TAB);
                unregister_code(KC_LSFT);
            }
            return false;
    }
    return true;
}

enum combo_events {
    MOD_KEY
};
const uint16_t PROGMEM mod_key[] = {LT(1, KC_ENT), LT(2, KC_SPC), COMBO_END};
combo_t key_combos[]= {
    [MOD_KEY] = COMBO(mod_key, KC_LGUI)
};

// per key tapping-term
// uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case LT(2, KC_SPC):
//             return 140;
//         default:
//             return TAPPING_TERM;
//     }
// }

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //base
	[0] = LAYOUT(
        KC_B, KC_L, KC_D, KC_W, KC_Z, KC_QUOT, KC_F, KC_O, KC_U, KC_J,
        KC_N, KC_R, KC_T, KC_S, KC_G, KC_Y, KC_H, KC_A, KC_E, KC_I,
        KC_Q, LT(3,KC_X), KC_M, KC_C, KC_V, KC_K, KC_P, KC_COMM, KC_DOT, KC_SLSH,
                  KC_LSFT, LT(1, KC_ENT), LT(2, KC_SPC), RCTL_T(KC_ESC)
    ),

    //symbol
	[1] = LAYOUT(
        KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_NO, KC_LCBR, KC_RCBR, KC_MINS, KC_NO,
        KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC, KC_TAB, KC_EQL, KC_LPRN, KC_RPRN, KC_COLN, KC_DQT,
        KC_BSLS, KC_CIRC, KC_UNDS, KC_TILD, KC_NO, KC_GRV, KC_PIPE, KC_PLUS, KC_NO, KC_SCLN, 
                          KC_1, KC_2, KC_3, KC_4
    ),

    //num
	[2] = LAYOUT(
        KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, SFT_TAB, KC_1, KC_2, KC_3, KC_NO,
        CTRL_SPC, KC_ASTR, KC_LBRC, KC_RBRC, KC_TAB, KC_EQL, KC_4, KC_5, KC_6, KC_0,
        KC_BSLS, KC_CIRC, KC_UNDS, KC_TILD, KC_NO, KC_NO, KC_7, KC_8, KC_9, KC_NO,
                          KC_LGUI, CTRL_BSPC, KC_3, KC_4
    ),

    //nav
	[3] = LAYOUT(
        KC_Q, KC_W, KC_E, KC_R, QK_BOOT, KC_Y, KC_PGUP, KC_PGDN, KC_O,   KC_P,
        KC_A, KC_S, KC_LCTL, KC_F, KC_G, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_SCLN,
        KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
                          KC_1, KC_2, CTRL_Y, KC_4
    ),
	[4] = LAYOUT(
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,
        KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,
        KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
                          KC_1, KC_2, KC_3, KC_4
    )
};
