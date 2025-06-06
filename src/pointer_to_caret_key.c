#include <drivers/input_processor.h>
#include <zephyr/input/input.h>
#include <zmk/hid.h>
#include <zmk/keymap.h>
#include <zmk/endpoints.h>
#include <devicetree.h>

// Отримуємо значення caret-tick з devicetree, або використовуємо 10 як дефолтне
#define DT_DRV_COMPAT zmk_input_processor_caret
#define CARET_TICK_DEFAULT 10
#define CARET_TICK_FROM_DT(node_id) DT_PROP_OR(node_id, caret_tick, CARET_TICK_DEFAULT)
#define GET_CARET_TICK(inst_id) CARET_TICK_FROM_DT(DT_DRV_INST(inst_id))

static int32_t caret_delta_x = 0;
static int32_t caret_delta_y = 0;

static int pointer_to_caret_key_process(const struct device *dev, struct input_event *event, uint32_t param1, uint32_t param2, struct zmk_input_processor_state *state) {
    if (event->type != INPUT_EV_REL) {
        return ZMK_INPUT_PROC_CONTINUE;
    }

    // Отримуємо значення caret-tick з devicetree для цього екземпляра
    int caret_tick = GET_CARET_TICK(0);
    
    caret_delta_x += event->rel.x;
    caret_delta_y += event->rel.y;

    while (caret_delta_x >= caret_tick) {
        zmk_hid_press(ZMK_HID_USAGE_KEY(HID_USAGE_KEY_KEYBOARD_RIGHT_ARROW));
        zmk_hid_release(ZMK_HID_USAGE_KEY(HID_USAGE_KEY_KEYBOARD_RIGHT_ARROW));
        caret_delta_x -= caret_tick;
    }
    while (caret_delta_x <= -caret_tick) {
        zmk_hid_press(ZMK_HID_USAGE_KEY(HID_USAGE_KEY_KEYBOARD_LEFT_ARROW));
        zmk_hid_release(ZMK_HID_USAGE_KEY(HID_USAGE_KEY_KEYBOARD_LEFT_ARROW));
        caret_delta_x += caret_tick;
    }
    while (caret_delta_y >= caret_tick) {
        zmk_hid_press(ZMK_HID_USAGE_KEY(HID_USAGE_KEY_KEYBOARD_DOWN_ARROW));
        zmk_hid_release(ZMK_HID_USAGE_KEY(HID_USAGE_KEY_KEYBOARD_DOWN_ARROW));
        caret_delta_y -= caret_tick;
    }
    while (caret_delta_y <= -caret_tick) {
        zmk_hid_press(ZMK_HID_USAGE_KEY(HID_USAGE_KEY_KEYBOARD_UP_ARROW));
        zmk_hid_release(ZMK_HID_USAGE_KEY(HID_USAGE_KEY_KEYBOARD_UP_ARROW));
        caret_delta_y += caret_tick;
    }

    // Гасимо pointer-подію, щоб вона не потрапила у HID-звіт миші
    return ZMK_INPUT_PROC_STOP;
}

ZMK_INPUT_PROCESSOR_DEFINE(pointer_to_caret_key_process, pointer_to_caret_key); 
