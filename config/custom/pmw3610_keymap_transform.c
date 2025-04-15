#include <zmk/event_manager.h>
#include <zmk/events/mouse_move_state_changed.h>
#include <zmk/hid.h>
#include <zmk/keymap.h>
#include <zmk/events/layer_state_changed.h>

#define SENSITIVITY 8
#define TARGET_LAYER 2  // шар на якому буде активний модуль

static bool active_layer = false;

static int handle_layer_change(struct zmk_layer_state_changed *event) {
    active_layer = zmk_keymap_highest_layer_active() == TARGET_LAYER;
    return 0;
}

static int handle_mouse_move(struct zmk_mouse_move_state_changed *event) {
    if (!active_layer) return 0;

    int dx = event->dx;
    int dy = event->dy;

    if (dx >= SENSITIVITY) {
        zmk_hid_press(ZMK_HID_USAGE(HID_USAGE_KEY, HID_USAGE_KEY_KEYBOARD_RIGHT_ARROW));
        zmk_hid_release(ZMK_HID_USAGE(HID_USAGE_KEY, HID_USAGE_KEY_KEYBOARD_RIGHT_ARROW));
    } else if (dx <= -SENSITIVITY) {
        zmk_hid_press(ZMK_HID_USAGE(HID_USAGE_KEY, HID_USAGE_KEY_KEYBOARD_LEFT_ARROW));
        zmk_hid_release(ZMK_HID_USAGE(HID_USAGE_KEY, HID_USAGE_KEY_KEYBOARD_LEFT_ARROW));
    }

    if (dy >= SENSITIVITY) {
        zmk_hid_press(ZMK_HID_USAGE(HID_USAGE_KEY, HID_USAGE_KEY_KEYBOARD_DOWN_ARROW));
        zmk_hid_release(ZMK_HID_USAGE(HID_USAGE_KEY, HID_USAGE_KEY_KEYBOARD_DOWN_ARROW));
    } else if (dy <= -SENSITIVITY) {
        zmk_hid_press(ZMK_HID_USAGE(HID_USAGE_KEY, HID_USAGE_KEY_KEYBOARD_UP_ARROW));
        zmk_hid_release(ZMK_HID_USAGE(HID_USAGE_KEY, HID_USAGE_KEY_KEYBOARD_UP_ARROW));
    }

    return 0;
}

ZMK_LISTENER(pmw3610_layer, handle_layer_change);
ZMK_SUBSCRIPTION(pmw3610_layer, zmk_layer_state_changed);

ZMK_LISTENER(pmw3610_mouse, handle_mouse_move);
ZMK_SUBSCRIPTION(pmw3610_mouse, zmk_mouse_move_state_changed);
