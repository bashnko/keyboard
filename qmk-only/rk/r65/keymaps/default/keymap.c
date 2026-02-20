#include QMK_KEYBOARD_H

#ifndef RGB_MOD
#    define RGB_MOD _______
#endif
#ifndef RGB_HUI
#    define RGB_HUI _______
#endif
#ifndef RGB_VAI
#    define RGB_VAI _______
#endif
#ifndef RGB_SPD
#    define RGB_SPD _______
#endif
#ifndef RGB_VAD
#    define RGB_VAD _______
#endif
#ifndef RGB_SPI
#    define RGB_SPI _______
#endif

enum layer_names {
    _BASE,             // 0
    _SYMBOLS_RIGHT,    // 1
    _SYMBOLS_LEFT,     // 2
    _NUMBERS,          // 3
    _ALT_A,            // 4
    _ALT_A_FN,         // 5
    _ALT_B,            // 6
    _ALT_B_FN,         // 7
    _BOOT              // 8
};

enum custom_keycodes {
    SWITCH_FN = SAFE_RANGE,
    CAPS_CTRL_SPACE
};

bool fn_mode = false;

enum combo_events {
    JK_ESC,
};

const uint16_t PROGMEM jk_combo[] = {LT(2, KC_J), RCTL_T(KC_K), COMBO_END};

combo_t key_combos[] = {
    [JK_ESC] = COMBO(jk_combo, KC_ESC),
};

const uint16_t number_to_function[] PROGMEM = {
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == SWITCH_FN) {
        if (record->event.pressed) {
            fn_mode = !fn_mode;
        }
        return false;
    }

    if (keycode == CAPS_CTRL_SPACE) {
        if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_SPC);
        } else {
            unregister_code(KC_SPC);
            unregister_code(KC_LCTL);
        }
        return false;
    }



    if (fn_mode) {
        if ( ( keycode >= KC_1 && keycode <= KC_0 ) || keycode == KC_MINS || keycode == KC_EQL ) {
            uint8_t index = keycode - KC_1;
            if (keycode == KC_MINS) { index = 10;}
            else if (keycode == KC_EQL) { index = 11;}
            if (record->event.pressed) {
                register_code(pgm_read_word(&number_to_function[index]));
            } else {
                unregister_code(pgm_read_word(&number_to_function[index]));
            }
            return false;
        }
    }

    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(3, KC_A):
          return 150;
        default:
            return TAPPING_TERM;
    }
}



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // qwerty
    // [_BASE] = LAYOUT(
    //     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_MUTE,
    //     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
    //     CAPS_CTRL_SPACE, LT(3, KC_A), LSFT_T(KC_S), LCTL_T(KC_D), LT(1, KC_F), KC_G, KC_H, LT(2, KC_J), RCTL_T(KC_K), RSFT_T(KC_L), KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
    //     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
    //     KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RGHT
    // ),


    //colemak-dh
    [_BASE] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        CAPS_CTRL_SPACE, LT(3, KC_A), LSFT_T(KC_S), LCTL_T(KC_D), LT(1, KC_F), KC_G, KC_H, LT(2, KC_J), RCTL_T(KC_K), RSFT_T(KC_L), KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    //layer1
    [_SYMBOLS_RIGHT] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_LCBR,    KC_RCBR,    KC_MINS,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        _______, KC_A, KC_S, LCTL_T(KC_D), LT(1, KC_F), KC_G, KC_H, KC_LPRN, KC_RPRN, KC_COLN, KC_DQT, KC_QUOT, KC_ENT, KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_GRV,    KC_PIPE,    KC_PLUS, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT, KC_BSPC, KC_RALT, _______, KC_LEFT, KC_DOWN, KC_RGHT
    ),


    //layer2
    [_SYMBOLS_LEFT] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_MUTE,
        KC_TAB, KC_EXLM, KC_AT, KC_HASH, KC_DOLLAR, KC_PERC, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        KC_CAPS, KC_AMPR, KC_PAST, KC_LBRC, KC_RBRC, KC_TAB, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
        KC_BSLS, KC_LSFT,  KC_CIRC, KC_UNDS, KC_TILD, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT, KC_ENT, KC_RALT, MO(3), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    //layer3
    [_NUMBERS] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_PGUP,    KC_1,    KC_2,    KC_3,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_PGDN,    KC_4,    KC_5, KC_6, KC_0,  KC_QUOT, KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_GRV,  KC_7, KC_8, KC_9,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT, KC_BSPC,  KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_ALT_A] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_MUTE,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(5), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_ALT_A_FN] = LAYOUT(
        KC_GRV, KC_MYCM, KC_HOME, KC_MAIL, KC_CALC, KC_SLCT, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, MO(8), _______, KC_HOME, KC_SCRL, RGB_MOD, KC_INS,
        _______, TO(4), TO(6), _______, _______, _______, _______, _______, _______, MO(8), _______, KC_PSCR, _______, KC_PAUSE,
        _______, _______, _______, _______, _______, NK_TOGG, _______, _______, RGB_HUI, _______, _______, MO(8), RGB_VAI, KC_END,
        SWITCH_FN, GU_TOGG, _______, EE_CLR, _______, _______, RGB_SPD, RGB_VAD, RGB_SPI
    ),

    [_ALT_B] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_MUTE,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(7), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_ALT_B_FN] = LAYOUT(
        KC_GRV, KC_BRMD, KC_BRMU, KC_F3, KC_F4, KC_BRID, KC_BRIU, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, MO(8), _______, KC_HOME, KC_SCRL, RGB_MOD, KC_INS,
        _______, TO(4), TO(6), _______, _______, _______, _______, _______, _______, MO(8), _______, KC_PSCR, _______, KC_PAUSE,
        _______, _______, _______, _______, _______, NK_TOGG, _______, _______, RGB_HUI, _______, _______, MO(8), RGB_VAI, KC_END,
        SWITCH_FN, _______, _______, EE_CLR, _______, _______, RGB_SPD, RGB_VAD, RGB_SPI
    ),

    [_BOOT] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [4] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [5] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [6] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [7] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [8] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif

