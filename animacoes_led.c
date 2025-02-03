    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include "pico/stdlib.h"
    #include "hardware/pio.h"
    #include "hardware/clocks.h"
    #include "hardware/adc.h"
    #include "pico/bootrom.h"
    #include "hardware/timer.h"

    //arquivo .pio
    #include "animacoes_led.pio.h"

    //número de LEDs
    #define NUM_PIXELS 25

    //pino de saída
    #define OUT_PIN 7

    //Variáveis Globais
    PIO pio;
    uint sm;

    // Pino de saída
    const uint led_red = 12;    // Atribui o pino do led ao pino 12
    const uint button_A = 5;    // Atribui o pino do botão A à variável
    const uint button_B = 6;    // Atribui o pino do botão B à variável

    // Prototipação da função de interrupção
    static void gpio_irq_handler(uint gpio, uint32_t events);

    // Variáveis globais
    static volatile uint numero = 0;
    static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)

    uint32_t matrix_rgb(double intensity) {
        unsigned char value = intensity * 255;
        return (value << 16) | (value << 8) | value;
    }

    void exibir_numero(int numero) {
        // Matriz de LEDs representando os números de 0 a 9
        double numeros[10][25] = {
        {0, 1, 1, 1, 0,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        0, 1, 1, 1, 0}, //0

        {0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 1,
        0, 1, 1, 0, 0,
        0, 0, 1, 0, 0}, // 1

        {1, 1, 1, 1, 1,
        0, 1, 0, 0, 0,
        0, 1, 0, 0, 0,
        1, 0, 0, 0, 1,
        0, 1, 1, 1, 0}, // 2

        {1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        0, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1}, // 3

        {1, 0, 0, 0, 0,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1}, // 4

        {1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1}, // 5

         {1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1}, // 6

        {0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 1, 1}, // 7

        {1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1}, // 8

        {1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1}  // 9
        };
        if (numero < 0) numero = 0;
        if (numero > 9) numero = 9;
        for (int i = 0; i < NUM_PIXELS; i++) {
            uint32_t valor_led = matrix_rgb(numeros[numero][i]);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
    }

    int main() {
        gpio_init(button_A);
        gpio_set_dir(button_A, GPIO_IN);
        gpio_pull_up(button_A);

        gpio_init(button_B);
        gpio_set_dir(button_B, GPIO_IN);
        gpio_pull_up(button_B);

        // Inicializa o LED no pino 12
        gpio_init(led_red);
        gpio_set_dir(led_red, GPIO_OUT);
        gpio_put(led_red, false);

        // Configuração da interrupção com callback
        gpio_set_irq_enabled_with_callback(button_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
        gpio_set_irq_enabled_with_callback(button_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

        stdio_init_all();
        printf("Iniciando a animação\n");

        // Inicialização do PIO
        pio = pio0;
        uint offset = pio_add_program(pio, &animacoes_led_program);
        sm = pio_claim_unused_sm(pio, true);
        animacoes_led_program_init(pio, sm, offset, OUT_PIN);

        // Loop principal
        while (true) {
            // Pisca o LED 5 vezes por segundo (100ms ligado, 100ms desligado)
            gpio_put(led_red, true);
            sleep_ms(100);
            gpio_put(led_red, false);
            sleep_ms(100);
            
            // Exibe o número atual na matriz de LEDs
            exibir_numero(numero);
        }
    }

    void gpio_irq_handler(uint gpio, uint32_t events) {
        uint32_t current_time = to_us_since_boot(get_absolute_time());

        if (current_time - last_time > 300000) { // Debounce de 300ms
            last_time = current_time;

            if (gpio == button_A && !(gpio_get(button_A))) {
                if (events & GPIO_IRQ_EDGE_FALL) {
                    if (numero >= 9) return;  // Impede incremento além de 9
                    numero++;
                    printf("Botão A pressionado. Numero = %d\n", numero);
                }
            } else if (gpio == button_B && !(gpio_get(button_B))) {
                if (events & GPIO_IRQ_EDGE_FALL) {
                    if (numero <= 0) return;  // Impede decremento abaixo de 0
                    numero--;
                    printf("Botão B pressionado. Numero = %d\n", numero);
                }
            }
        }
    }

