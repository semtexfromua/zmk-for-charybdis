# ZMK Charybdis Custom Config

## Особливості
- Драйвер PMW3610: [badjeff/zmk-pmw3610-driver](https://github.com/badjeff/zmk-pmw3610-driver)
- Підтримка SCROLL/SNIPE/CARET режимів через DeviceTree та input processors
- Кастомний CARET-режим (pointer-to-caret) реалізується через input processor (overlay)

## Як це працює
- На шарі 1 трекбол працює як стрілки (CARET-режим)
- На інших шарах — як миша або скрол

## Як зібрати
1. Переконайтесь, що у вас є Zephyr toolchain та west.
2. Запустіть:
   ```sh
   west update
   west build -b nice_nano_v2 -- -DSHIELD=charybdis_right
   ```
3. Завантажте прошивку на пристрій.

## Як це налаштувати
- Параметри драйвера (CPI, інверсія, awake, IRQ) — у overlay (див. README драйвера)
- Поріг для CARET-режиму (чутливість) — у input processor overlay
- Шар для CARET-режиму — у overlay, секція `caret { layers = <1>; ... }`

## Troubleshooting
- Якщо не працює CARET-режим — перевірте, що шар 1 активується у keymap.
- Якщо не компілюється — перевірте, що драйвер підключено через west.yml.
- Якщо west update падає — перевірте, що у west.yml немає зайвих проектів.

## Контакти/Питання
- Відкривайте issues або пишіть у дискусії репозиторію. 
