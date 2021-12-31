/*
Copyright 2018 BruceZh <xzhong86@??.com>
*/

#include "keymap_zhong.h"
#include "led.h"

#include "action_layer.h"  // for hook
#include "action_util.h"  // for hook

#define LED_CAPS_ON()   do { } while (0)
#define LED_CAPS_OFF()  do { } while (0)
#define LED_SPCFN_ON()  do { } while (0)
#define LED_SPCFN_OFF() do { } while (0)

/**/

enum {
    LAYER_DEFAULT,
    LAYER_SPCFN,
    LAYER_EDIT,
};
enum {
    KC_mCAPS = KC_FN0,
    KC_WINL ,   KC_WINR ,
    KC_SPCFN,
    KC_mEdit,
};

const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    [LAYER_DEFAULT] = KEYMAP_K60(ESC, GRV, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, MINS, EQL, BSPC, TAB, Q, W, E, R, T, Y, U, I, O, P, LBRC, RBRC, BSLS, mCAPS, A, S, D, mEdit, G, H, J, K, L, SCLN, QUOT, ENT, LSFT, Z, X, C, V, B, N, M, COMM, DOT, SLSH, RSFT, LCTL, LGUI, LALT, SPCFN, RALT, RGUI, APP, RCTL),
    [LAYER_SPCFN] = KEYMAP_K60(GRV, TRNS, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, TRNS, TRNS, NO, NO, WINL, WINR, NO, NO, NO, NO, NO, PSCR, TRNS, TRNS, TRNS, TRNS, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, TRNS, TRNS, NO, DEL, NO, NO, SPC, NO, NO, BSPC, DEL, NO, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS),
    [LAYER_EDIT]  = KEYMAP_K60(TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, NO, TAB, NO, NO, NO, NO, PGUP, UP, END, NO, TRNS, TRNS, TRNS, TRNS, LALT, LCTL, LSFT, NO, NO, HOME, LEFT, DOWN, RGHT, NO, NO, TRNS, TRNS, NO, NO, NO, NO, NO, PGDN, NO, BSPC, DEL, NO, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS),
};

const action_t PROGMEM fn_actions[] = {
    [KC_mCAPS - KC_FN0]   = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_CAPS),
    [KC_WINL  - KC_FN0]   = ACTION_MODS_KEY(MOD_LGUI | MOD_LCTL, KC_LEFT),
    [KC_WINR  - KC_FN0]   = ACTION_MODS_KEY(MOD_LGUI | MOD_LCTL, KC_RIGHT),
    [KC_SPCFN - KC_FN0]   = ACTION_LAYER_TAP_KEY(LAYER_SPCFN, KC_SPACE),
    [KC_mEdit - KC_FN0]   = ACTION_LAYER_TAP_KEY(LAYER_EDIT, KC_F),
};

void hook_layer_change(uint32_t layer_state)
{
    if (layer_state & (1 << LAYER_SPCFN))
        LED_SPCFN_ON();
    else
        LED_SPCFN_OFF();
}

void board_led_set(uint8_t usb_led)
{
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        LED_CAPS_ON();
    else
        LED_CAPS_OFF();
    //if (usb_led & (1<<USB_LED_NUM_LOCK))
    //if (usb_led & (1<<USB_LED_SCROLL_LOCK))
}


// hook for Shift+ESC and Shift+BSPC
#define MOD_SHIFT  (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))
bool hook_process_action(keyrecord_t *record) {
    static bool esc_as_grv = false;
    static bool bspc_as_bsls = false;

    keyevent_t event = record->event;
    action_t action = layer_switch_get_action(event);
    const uint8_t mods = get_mods();
    bool only_shift = (mods & MOD_SHIFT) && !(mods & ~MOD_SHIFT);
    uint8_t key_code = action.key.code;
    if (KC_ESC != key_code && KC_BSPC != key_code)
        return false;

    if (KC_ESC == key_code) {
        if (event.pressed)
            esc_as_grv = only_shift;
        key_code = esc_as_grv ? KC_GRV : KC_ESC;
    }
    if (KC_BSPC == key_code) {
        if (event.pressed)
            bspc_as_bsls = only_shift;
        key_code = bspc_as_bsls ? KC_BSLS : KC_BSPC;
    }
    if (event.pressed)
        register_code(key_code);
    else
        unregister_code(key_code);
    return true;
}

