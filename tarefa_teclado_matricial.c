
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

