/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2023 Andreas Loeffler <al@exitzero.de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


/*
  Features:
  - using combo to insert (opening and ending) braces/quotes
    and place cursor inside
  - lower layer key short tap to press enter (to numbers with only left hand)
  - caps-lock indicator (left/right shift keys light up red)
  - underglow as layer indicator
  - some macros (emacs short-cuts)
  - media keys include volume and screen brightness control

  - no via and oled configured (save memory)
 */

#include QMK_KEYBOARD_H

enum custom_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
    LAYER3,
    LAYER4,

    FN_MO13,
    FN_MO23,
    FN_LT13ENT
};

// Layer names
enum layer_names {
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

#ifdef TAP_DANCE_ENABLE
enum {
    TD_ESC_BSPC,
    TD_LSFT_CAPS,
    TD_RSFT_CAPS,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ESC_BSPC]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC,  KC_BSPC),
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_RSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
};

// Add tap dance item to your keymap in place of a keycode
/* const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { */
/*     // ... */
/*     TD(TD_ESC_CAPS) */
/*     // ... */
/* }; */

#define KC_TD_ESC_BSPC  TD(TD_ESC_BSPC)
#define KC_TD_LSFT_CAPS TD(TD_LSFT_CAPS)
#define KC_TD_RSFT_CAPS TD(TD_RSFT_CAPS)
#else
#define KC_TD_ESC_BSPC  KC_ESC
#define KC_TD_LSFT_CAPS KC_LSFT
#define KC_TD_RSFT_CAPS KC_RSFT
#endif // TAP_DANCE_ENABLE

// D, F, J, K
/* #define KC_CTL_D LCTL_T(KC_D) */
/* #define KC_ALT_F LALT_T(KC_F) */
/* #define KC_ALT_J RALT_T(KC_J) */
/* #define KC_CTL_K RCTL_T(KC_K) */

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case LCTL_T(KC_D):
    case LALT_T(KC_F):
    case RALT_T(KC_J):
    case RCTL_T(KC_K):
        return TAPPING_TERM + 250;
    default:
        return TAPPING_TERM;
    }
}

// TEMPLATE
// ,-----------------------------------------------------------------------.       ,-----------------------------------------------------------------------.
// |           |           |           |           |           |           |       |           |           |           |           |           |           |
// |-----------+-----------+-----------+-----------+-----------+-----------|       |-----------+-----------+-----------+-----------+-----------+-----------|
// |           |           |           |           |           |           |       |           |           |           |           |           |           |
// |-----------+-----------+-----------+-----------+-----------+-----------|       |-----------+-----------+-----------+-----------+-----------+-----------|
// |           |           |           |           |           |           |       |           |           |           |           |           |           |
// `-----------+-----------+-----------+--+--------+--+--------+--+--------+--. .-----------+--+--------+--+--------+--+-----------+-----------+-----------'
//                                        |           |           |           | |           |           |           |
//                                        `-----------------------------------' `-----------------------------------'


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_split_3x6_3(
// ,-----------------------------------------------------------------------.       ,-----------------------------------------------------------------------.
KC_TD_ESC_BSPC,   KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,               KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
// |-----------+-----------+-----------+-----------+-----------+-----------|       |-----------+-----------+-----------+-----------+-----------+-----------|
      KC_TAB,     KC_A,       KC_S,       KC_D,       KC_F,       KC_G,               KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
// |-----------+-----------+-----------+-----------+-----------+-----------|       |-----------+-----------+-----------+-----------+-----------+-----------|
KC_TD_LSFT_CAPS,  KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,               KC_N,       KC_M,     KC_COMM,      KC_DOT,     KC_SLSH, KC_TD_RSFT_CAPS,
// `-----------+-----------+-----------+--+--------+--+--------+--+--------+--. .-----------+--+--------+--+--------+--+-----------+-----------+-----------'
                                            KC_LCTL, LT(_LOWER, KC_ENT),KC_SPC,    KC_ENT,    FN_MO23,     KC_RALT
//                                        `-----------+-----------+-----------' `-----------+-----------+-----------'
    ),

    [_COLEMAK] = LAYOUT(
// ,-----------------------------------------------------------------------.       ,-----------------------------------------------------------------------.
KC_TD_ESC_BSPC,   KC_Q,       KC_W,       KC_F,    KC_P,    KC_G,                      KC_J,      KC_L,       KC_U,       KC_Y,       KC_SCLN,    KC_BSPC,
// |-----------+-----------+-----------+-----------+-----------+-----------|       |-----------+-----------+-----------+-----------+-----------+-----------|
      KC_TAB,     KC_A,       KC_R,       KC_S,    KC_T,    KC_D,                      KC_H,      KC_N,       KC_E,       KC_I,       KC_O,       KC_QUOT,
// |-----------+-----------+-----------+-----------+-----------+-----------|       |-----------+-----------+-----------+-----------+-----------+-----------|
KC_TD_LSFT_CAPS,  KC_Z,       KC_X,       KC_C,    KC_V,    KC_B,                      KC_K,      KC_M,  KC_COMM,         KC_DOT,     KC_SLSH, KC_TD_RSFT_CAPS,
// `-----------+-----------+-----------+--+--------+--+--------+--+--------+--. .-----------+--+--------+--+--------+--+-----------+-----------+-----------'
                                          KC_LCTL,LT(_LOWER, KC_ENT),KC_SPC,       KC_ENT,    FN_MO23,     KC_RALT
//                                        `-----------+-----------+-----------' `-----------+-----------+-----------'
    ),

    [_LOWER] = LAYOUT_split_3x6_3(
// ,-----------------------------------------------------------------------.       ,-----------------------------------------------------------------------.
      KC_LALT,   KC_LCBR,    KC_7,       KC_8,       KC_9,       KC_RCBR,            KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_PLUS,    KC_EQL,     KC_BSPC,
// |-----------+-----------+-----------+-----------+-----------+-----------|       |-----------+-----------+-----------+-----------+-----------+-----------|
      KC_TAB,    KC_LBRC,    KC_4,       KC_5,       KC_6,       KC_RBRC,            KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    KC_RCTL,
// |-----------+-----------+-----------+-----------+-----------+-----------|       |-----------+-----------+-----------+-----------+-----------+-----------|
      KC_LSFT,   KC_0,       KC_1,       KC_2,       KC_3,       KC_PIPE,            KC_UNDS,    KC_MINS,    KC_LPRN,    KC_RPRN,    KC_BSLS,    KC_RSFT,
// `-----------+-----------+-----------+--+--------+--+--------+--+--------+--. .-----------+--+--------+--+--------+--+-----------+-----------+-----------'
                                             KC_LCTL,   KC_TRNS,    KC_SPC,        KC_ENT,    KC_TRNS,    KC_RALT
//                                        `-----------+-----------+-----------' `-----------+-----------+-----------'

    ),

    [_RAISE] = LAYOUT_split_3x6_3(
// ,-----------------------------------------------------------------------.       ,-----------------------------------------------------------------------.
      KC_LALT,  QK_MACRO_0, QK_MACRO_1, QK_MACRO_2,  KC_F11,     KC_F12,             KC_PGUP,    KC_HOME,    KC_UP,      KC_END,     KC_GRV,     KC_BSPC,
// |-----------+-----------+-----------+-----------+-----------+-----------|       |-----------+-----------+-----------+-----------+-----------+-----------|
      KC_TAB,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,              KC_PGDN,    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_SPC,     KC_RCTL,
// |-----------+-----------+-----------+-----------+-----------+-----------|       |-----------+-----------+-----------+-----------+-----------+-----------|
      KC_LSFT,   KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,             KC_TILD,    KC_DEL,     KC_NO,      KC_NO,      KC_INS,     KC_RSFT,
// `-----------+-----------+-----------+--+--------+--+--------+--+--------+--. .-----------+--+--------+--+--------+--+-----------+-----------+-----------'
                                             KC_LCTL,   KC_TRNS,    KC_SPC,        KC_ENT,    KC_TRNS,    KC_RALT
//                                        `-----------+-----------+-----------' `-----------+-----------+-----------'

    ),

    [_ADJUST] = LAYOUT_split_3x6_3(
// ,-----------------------------------------------------------------------.       ,-----------------------------------------------------------------------.
QK_HAPTIC_RESET,QK_MACRO_3,  KC_BTN1,    KC_LSFT,    KC_BTN2,    KC_BTN3,           KC_NUM_LOCK, KC_PSCR,    KC_MS_U,    KC_PAUS,    KC_BRIU,   KC_BRID,
// |-----------+-----------+-----------+-----------+-----------+-----------|       |-----------+-----------+-----------+-----------+-----------+-----------|
      RGB_TOG,   RGB_HUI,    RGB_SAI,    RGB_VAI,    RGB_SPI,    KC_VOLU,           QK_MACRO_9,  KC_MS_L,    KC_MS_D,    KC_MS_R,    QK_MACRO_12, KC_SCROLL_LOCK,
// |-----------+-----------+-----------+-----------+-----------+-----------|       |-----------+-----------+-----------+-----------+-----------+-----------|
      RGB_MOD,   RGB_HUD,    RGB_SAD,    RGB_VAD,    RGB_SPD,    KC_VOLD,            KC_RGUI,   QK_MACRO_10,QK_MACRO_11,QK_MACRO_12, QK_MACRO_4, QK_MACRO_5,
// `-----------+-----------+-----------+--+--------+--+--------+--+--------+--. .-----------+--+--------+--+--------+--+-----------+-----------+-----------'
                                             KC_LCTL,   KC_TRNS,    KC_SPC,        KC_ENT,    KC_TRNS,    KC_RALT
//                                        `-----------+-----------+-----------' `-----------+-----------+-----------'

    )
};


// combo events
#ifdef COMBO_ENABLE

enum combo_events {
    ROUND_BRC,
    CURLY_BRC,
    SQUARE_BRC,
    ANGLE_BRC,
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    A_UML,
    O_UML,
    U_UML,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM round_brc_combo[]     = {KC_J, KC_K, COMBO_END};    // jk
const uint16_t PROGMEM curly_brc_combo[]     = {KC_J, KC_L, COMBO_END};    // jl
const uint16_t PROGMEM square_brc_combo[]    = {KC_U, KC_I, COMBO_END};    // ui
const uint16_t PROGMEM angle_brc_combo[]     = {KC_U, KC_O, COMBO_END};    // uo
const uint16_t PROGMEM single_quote_combo[]  = {KC_COMM, KC_M, COMBO_END}; // m,
const uint16_t PROGMEM double_quote_combo[]  = {KC_DOT,  KC_M, COMBO_END}; // m.
const uint16_t PROGMEM a_uml_combo[]  = {KC_A, KC_J, COMBO_END}; // ja
const uint16_t PROGMEM o_uml_combo[]  = {KC_F, KC_O, COMBO_END}; // fo
const uint16_t PROGMEM u_uml_combo[]  = {KC_F, KC_U, COMBO_END}; // uf


combo_t key_combos[] = {
    [ROUND_BRC]    = COMBO_ACTION(round_brc_combo),
    [CURLY_BRC]    = COMBO_ACTION(curly_brc_combo),
    [SQUARE_BRC]   = COMBO_ACTION(square_brc_combo),
    [ANGLE_BRC]    = COMBO_ACTION(angle_brc_combo),
    [SINGLE_QUOTE] = COMBO_ACTION(single_quote_combo),
    [DOUBLE_QUOTE] = COMBO_ACTION(double_quote_combo),
    [A_UML]        = COMBO_ACTION(a_uml_combo),
    [O_UML]        = COMBO_ACTION(o_uml_combo),
    [U_UML]        = COMBO_ACTION(u_uml_combo)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
    case ROUND_BRC:
        if (pressed) {
            tap_code16(S(KC_9));
            tap_code16(S(KC_0));
            tap_code16(KC_LEFT);
        }
        break;
    case CURLY_BRC:
        if (pressed) {
            tap_code16(S(KC_LBRC));
            tap_code16(S(KC_RBRC));
            tap_code16(KC_LEFT);
        }
        break;
    case SQUARE_BRC:
        if (pressed) {
            tap_code16(KC_LBRC);
            tap_code16(KC_RBRC);
            tap_code16(KC_LEFT);
        }
        break;
    case ANGLE_BRC:
        if (pressed) {
            tap_code16(S(KC_COMM));
            tap_code16(S(KC_DOT));
            tap_code16(KC_LEFT);
        }
        break;
    case SINGLE_QUOTE:
        if (pressed) {
            tap_code16(KC_QUOT);
            tap_code16(KC_QUOT);
            tap_code16(KC_LEFT);
        }
        break;
    case DOUBLE_QUOTE:
        if (pressed) {
            tap_code16(S(KC_QUOT));
            tap_code16(S(KC_QUOT));
            tap_code16(KC_LEFT);
        }
        break;
    case A_UML:
        if (pressed) {
            tap_code16(KC_RGUI);
            tap_code16(S(KC_QUOT));
            tap_code16(KC_A);
        }
        break;
    case O_UML:
        if (pressed) {
            tap_code16(KC_RGUI);
            tap_code16(S(KC_QUOT));
            tap_code16(KC_O);
        }
        break;
    case U_UML:
        if (pressed) {
            tap_code16(KC_RGUI);
            tap_code16(S(KC_QUOT));
            tap_code16(KC_U);
        }
        break;
    }
}
#endif  // COMBO_ENABLE


#ifdef OLED_ENABLE
#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
    case L_BASE:
        oled_write_ln_P(PSTR("Default"), false);
        break;
    case L_LOWER:
        oled_write_ln_P(PSTR("Lower"), false);
        break;
    case L_RAISE:
        oled_write_ln_P(PSTR("Raise"), false);
        break;
    case L_ADJUST:
    case L_ADJUST|L_LOWER:
    case L_ADJUST|L_RAISE:
    case L_ADJUST|L_LOWER|L_RAISE:
        oled_write_ln_P(PSTR("Adjust"), false);
        break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
      (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
      name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}
#endif // OLED_ENABLE



// Change LED color to red when CAPS LOCK is active
// Change underglow depending on layer Thx to @rpbaptist
#define THEME_HSV 132, 255, 125
extern led_config_t g_led_config;
void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t led_type) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_config.hsv.v) {
        hsv.v = rgb_matrix_config.hsv.v;
    }

    RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(26, 255, 0, 0);
        // Only works with SPLIT_LED_STATE_ENABLE
        rgb_matrix_set_color(53, 255, 0, 0);
    }

    switch (get_highest_layer(layer_state)) {
    case _LOWER:
        rgb_matrix_layer_helper(HSV_PURPLE, LED_FLAG_UNDERGLOW);
        break;
    case _RAISE:
        rgb_matrix_layer_helper(HSV_GOLDENROD, LED_FLAG_UNDERGLOW);
        break;
    case _ADJUST:
        rgb_matrix_layer_helper(HSV_GREEN, LED_FLAG_UNDERGLOW);
        break;
    default: {
        // fixme: handle additional base layer e.g. if we toggle between qwert and colemak
        rgb_matrix_layer_helper(THEME_HSV, LED_FLAG_UNDERGLOW);
        break;
    }
    }
    return false;
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {

#ifdef OLED_ENABLE
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
#endif

    switch (keycode) {
    case FN_MO13:
        if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
    case FN_MO23:
        if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
    case FN_LT13ENT:
        // like fn_mo13 but use layer tap to get enter when tapped
        break;

        // process macros
    case QK_MACRO_0:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("x") "set-variable" SS_TAP(X_ENT) "c-basic-offset" SS_TAP(X_ENT) "2");
        }
        break;
    case QK_MACRO_1:
        if (record->event.pressed) {
            SEND_STRING("emacs *.trace.gz &" SS_TAP(X_ENT));
        }
        break;
    case QK_MACRO_2:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_ESC) ":wq" SS_TAP(X_ENT));
        }
        break;
    case QK_MACRO_3:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("c") "r");
        }
        break;
    case QK_MACRO_4:
        if (record->event.pressed) {
            SEND_STRING(SS_RALT("x") "find-grep-dired" SS_TAP(X_ENT));
        }
        break;
    case QK_MACRO_5:
        if (record->event.pressed) {
            SEND_STRING(SS_RALT("x") "comment-region" SS_TAP(X_ENT));
        }
        break;
    case QK_MACRO_6:
        if (record->event.pressed) {
            SEND_STRING("Macro 06 Key was pressed!");
        }
        break;
    case QK_MACRO_7:
        if (record->event.pressed) {
            SEND_STRING("Macro 07 Key was pressed!");
        }
        break;
    case QK_MACRO_8:
        if (record->event.pressed) {
            SEND_STRING("Macro 08 Key was pressed!");
        }
        break;
    case QK_MACRO_9: // ctrl-space + end: mark from cursor to end of line in emacs
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(" ") SS_TAP(X_END));
        }
        break;
    case QK_MACRO_10: // emacs rectangular replace
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("x") "rt");
        }
        break;
    case QK_MACRO_11: // emacs rectangular cut
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("x") "rk");
        }
        break;
    case QK_MACRO_12: // emacs rectangular yank (paste)
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("x") "ry");
        }
        break;
    case QK_MACRO_13:
        if (record->event.pressed) {
            SEND_STRING("Macro 13 Key was pressed!");
        }
        break;
    case QK_MACRO_14:
        if (record->event.pressed) {
            SEND_STRING("Macro 14 Key was pressed!");
        }
        break;
    case QK_MACRO_15:
        if (record->event.pressed) {
            // when keycode QK_MACRO_15 is pressed
            SEND_STRING("#Macro 15: QMK Firmware 0.20.5_lefty01");
        } else {
            // when keycode MACRO0 is released
        }
        break;
    }  // switch keycode

    return true;
}  // process_record_user()


layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

