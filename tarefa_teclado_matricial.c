#include <stdio.h>
#include "pico/stdlib.h"

#define ROWS 4
#define COLS 4

const char KEYS[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Definição dos pinos do teclado
const uint GPIO_ROWS[ROWS] = {2, 3, 4, 5};
const uint GPIO_COLS[COLS] = {6, 7, 8, 9};
//Leds
const uint GPIO_LEDS[3] = {10, 11, 12};
//Buzzer
const uint GPIO_BUZZER = 21;

//Configurar os pinos
void init_gpio(void) {
    for (int i = 0; i < ROWS; i++) {
        gpio_init(GPIO_ROWS[i]);
        gpio_set_dir(GPIO_ROWS[i], GPIO_OUT);
        gpio_put(GPIO_ROWS[i], 0);
    }

    for (int i = 0; i < COLS; i++) {
        gpio_init(GPIO_COLS[i]);
        gpio_set_dir(GPIO_COLS[i], GPIO_IN);
        gpio_pull_down(GPIO_COLS[i]);
    }

    for (int i = 0; i < 3; i++) {
        gpio_init(GPIO_LEDS[i]);
        gpio_set_dir(GPIO_LEDS[i], GPIO_OUT);
        gpio_put(GPIO_LEDS[i], 0);
    }

    gpio_init(GPIO_BUZZER);
    gpio_set_dir(GPIO_BUZZER, GPIO_OUT);
    gpio_put(GPIO_BUZZER, 0);
}


// Função de controle do buzzer
void control_buzzer(char key) {
    if (key == 'A') {
        gpio_put(GPIO_BUZZER, 1); // Ativa o buzzer
        sleep_ms(500);  // Mantém o buzzer ligado por 500ms
        gpio_put(GPIO_BUZZER, 0); // Desativa o buzzer
    }
}

// Função para ler a tecla pressionada
char read_key(void) {
    for (int row = 0; row < ROWS; row++) {
        gpio_put(GPIO_ROWS[row], 1);
        for (int col = 0; col < COLS; col++) {
            if (gpio_get(GPIO_COLS[col])) {
                gpio_put(GPIO_ROWS[row], 0);
                return KEYS[row][col];
            }
        }
        gpio_put(GPIO_ROWS[row], 0);
    }
    return '\0'; // Retorna nulo se nenhuma tecla for pressionada
}

int main() {
    stdio_init_all();
    init_gpio();

    while (true) {
        char key = read_key();
        if (key != '\0') {
            control_led(key);
            control_buzzer(key);
        }
        sleep_ms(100);
    }

    return 0;
}