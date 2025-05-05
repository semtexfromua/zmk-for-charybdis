# ZMK Charybdis Custom Config

## Особливості
- Оригінальний драйвер PMW3610 (inorichi/zmk-pmw3610-driver)
- Кастомний input processor для CARET-режиму (pointer-to-caret)
- Підтримка SCROLL/SNIPE/CARET режимів через DeviceTree

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
- Поріг для CARET-режиму (чутливість) — у charybdis.dtsi, параметр `caret-tick`.
- Шар для CARET-режиму — у charybdis_right.overlay, секція `caret { layers = <1>; ... }`.
- Кастомний processor у src/pointer_to_caret_key.c

## Troubleshooting
- Якщо не працює CARET-режим — перевірте, що шар 1 активується у keymap.
- Якщо не компілюється src/ — переконайтесь, що є src/CMakeLists.txt і build.yaml містить extra-cmake-modules.
- Якщо west update падає — перевірте, що у west.yml немає зайвих проектів.

## Контакти/Питання
- Відкривайте issues або пишіть у дискусії репозиторію. 
