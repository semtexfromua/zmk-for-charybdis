zmk-config for charybdis 

# CARET режим для трекболу

- Реалізовано через кастомний input processor (pointer_to_caret_key).
- Підключено у charybdis_right.overlay для шару 1.
- Дельта та поріг налаштовуються у charybdis.dtsi.
- Драйвер не змінювався, усе через overlay та processor. 
