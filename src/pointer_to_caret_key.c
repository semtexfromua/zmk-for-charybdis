#include <drivers/input_processor.h>
#include <zephyr/input/input.h>
#include <zmk/hid.h>
#include <zmk/keymap.h>
#include <zmk/endpoints.h>

#define CARET_TICK 10 // Можна зробити параметром через overlay

static int32_t caret_delta_x = 0;
static int32_t caret_delta_y = 0;

static int pointer_to_caret_key_process(const struct device *dev, struct input_event *event, uint32_t param1, uint32_t param2, struct zmk_input_processor_state *state) {
    if (event->type != INPUT_EV_REL) {
        return ZMK_INPUT_PROC_CONTINUE;
    }

    caret_delta_x += event->rel.x;
    caret_delta_y += event->rel.y;

    while (caret_delta_x >= CARET_TICK) {
        zmk_hid_press(ZMK_HID_USAGE_KEY(HID_USAGE_KEY_KEYBOARD_RIGHT_ARROW));
        zmk_hid_release(ZMK_HID_USAGE_KEY(HID_USAGE_KEY_KEYBOARD_RIGHT_ARROW));
        caret_delta_x -= CARET_TICK;
    }
    while (caret_delta_x <= -CARET_TICK) {
        zmk_hid_press(ZMK_HID_USAGE_KEY(HID_USAGE_KEY_KEYBOARD_LEFT_ARROW));
        zmk_hid_release(ZMK_HID_USAGE_KEY(HID_USAGE_KEY_KEYBOARD_LEFT_ARROW));
        caret_delta_x += CARET_TICK;
    }
    while (caret_delta_y >= CARET_TICK) {
        zmk_hid_press(ZMK_HID_USAGE_KEY(HID_USAGE_KEY_KEYBOARD_DOWN_ARROW));
        zmk_hid_release(ZMK_HID_USAGE_KEY(HID_USAGE_KEY_KEYBOARD_DOWN_ARROW));
        caret_delta_y -= CARET_TICK;
    }
    while (caret_delta_y <= -CARET_TICK) {
        zmk_hid_press(ZMK_HID_USAGE_KEY(HID_USAGE_KEY_KEYBOARD_UP_ARROW));
        zmk_hid_release(ZMK_HID_USAGE_KEY(HID_USAGE_KEY_KEYBOARD_UP_ARROW));
        caret_delta_y += CARET_TICK;
    }

    // Гасимо pointer-подію, щоб вона не потрапила у HID-звіт миші
    return ZMK_INPUT_PROC_STOP;
}

ZMK_INPUT_PROCESSOR_DEFINE(pointer_to_caret_key_process, pointer_to_caret_key); 
