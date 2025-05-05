# ZMK Config для Charybdis з трекболом PMW3610

Це репозиторій з конфігурацією ZMK для клавіатури Charybdis з трекболом PMW3610, включаючи CARET-режим, який перетворює рух трекболу на натискання стрілок.

## Особливості

- Використовується офіційний ZMK (main/nightly)
- Драйвер PMW3610 підключено як external module
- Реалізовано підтримку CARET-режиму (режим трекбол → стрілки)
- Повна підтримка розділеної (split) клавіатури

## CARET-режим

CARET-режим дозволяє використовувати трекбол для руху курсору як стрілками клавіатури. При активації цього режиму, рух трекболу буде перетворюватись на натискання клавіш стрілок UP/DOWN/LEFT/RIGHT.

### Як використовувати:

1. Активуйте шар 1 (`&mo 1` у вашому keymap)
2. Рухайте трекбол для навігації по тексту стрілками

### Налаштування чутливості:

Для налаштування чутливості CARET-режиму можна змінити параметр `caret-tick` у файлі `config/boards/shields/charybdis/charybdis_right.overlay`:

```dts
pointer_to_caret_key: pointer_to_caret_key {
    compatible = "zmk,input-processor-caret";
    caret-tick = <10>; // Менше значення = більша чутливість
};
```

## Збірка та Прошивка

1. Встановіть ZMK за офіційною інструкцією
2. Клонуйте цей репозиторій
3. Виконайте команди для збірки:

```bash
west build -b nice_nano_v2 -- -DSHIELD="charybdis_left"
west build -b nice_nano_v2 -- -DSHIELD="charybdis_right"
```

## Структура Проекту

- `config/boards/shields/charybdis/` - оверлеї та конфігурація для щита
- `config/dts/bindings/` - devicetree bindings для кастомних компонентів
- `src/` - вихідний код для кастомного input processor (CARET-режим)
- `config/charybdis.keymap` - розкладка клавіатури

## Ліцензія

MIT

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
