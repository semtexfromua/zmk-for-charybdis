// pmw3610_keymap_transform.c

#include <zmk/event_manager.h>
#include <zmk/events/pointer_state_changed.h>
#include <zmk/hid.h>

#define SENSITIVITY 8 // adjust sensitivity as needed

static int handle_pointer_move(struct zmk_pointer_state_changed *event) {
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

ZMK_LISTENER(pmw3610_keymap_transform, handle_pointer_move);
ZMK_SUBSCRIPTION(pmw3610_keymap_transform, zmk_pointer_state_changed);
