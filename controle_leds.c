// Funções de controle dos LEDs

const uint GPIO_LEDS[3] = {10, 11, 12};

void control_led(char key) {
    switch (key) {
        case '1':
            gpio_put(GPIO_LEDS[0], !gpio_get(GPIO_LEDS[0]));
            break;
        case '2':
            gpio_put(GPIO_LEDS[1], !gpio_get(GPIO_LEDS[1]));
            break;
        case '3':
            gpio_put(GPIO_LEDS[2], !gpio_get(GPIO_LEDS[2]));
            break;
    }
}