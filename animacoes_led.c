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
const uint led_red = 12;    // Atribui o pino do led vermelho ao pino 12
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
        {0, 0, 0, 0, 0,
         1, 0, 1, 1, 0,
         1, 1, 0, 1, 0,
         0, 1, 1, 1, 0,
         0, 0, 0, 0, 0}, // 0

        {0, 0, 1, 0, 0,
         0, 0, 1, 0, 0,
         0, 0, 1, 0, 0,
         0, 0, 1, 1, 0,
         0, 0, 1, 0, 0}, // 1

        {0, 0, 0, 0, 0,
         0, 0, 0, 0, 0,
         0, 1, 0, 1, 1,
         0, 0, 0, 0, 0,
         0, 0, 0, 1, 1}, // 2
        {1, 1, 1, 1, 1,
         0, 0, 0, 0, 1,
         0, 1, 1, 1, 1,
         0, 0, 0, 0, 1,
         1, 1, 1, 1, 1}, // 3
        {1, 0, 0, 1, 0,
         1, 0, 0, 1, 0,
         1, 1, 1, 1, 1,
         0, 0, 0, 1, 0,
         0, 0, 0, 1, 0}, // 4
        {1, 1, 1, 1, 1,
         1, 0, 0, 0, 0,
         1, 1, 1, 1, 1,
         0, 0, 0, 0, 1,
         1, 1, 1, 1, 1}, // 5
        {1, 1, 1, 1, 1,
         1, 0, 0, 0, 0,
         1, 1, 1, 1, 1,
         1, 0, 0, 0, 1,
         1, 1, 1, 1, 1}, // 6
        {1, 1, 1, 1, 1,
         0, 0, 0, 0, 1,
         0, 0, 0, 1, 0,
         0, 0, 1, 0, 0,
         0, 1, 0, 0, 0}, // 7
        {1, 1, 1, 1, 1,
         1, 0, 0, 0, 1,
         1, 1, 1, 1, 1,
         1, 0, 0, 0, 1,
         1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 1,
         1, 0, 0, 0, 1,
         1, 1, 1, 1, 1,
         0, 0, 0, 0, 1,
         1, 1, 1, 1, 1}  // 9
    };

    // Garantir que o número esteja entre 0 e 9
    if (numero < 0) numero = 0;
    if (numero > 9) numero = 9;

    // Exibe o número na matriz de LEDs
    for (int i = 0; i < NUM_PIXELS; i++) {
        uint32_t valor_led = matrix_rgb(numeros[numero][i]);
        pio_sm_put_blocking(pio, sm, valor_led);  // Envia o valor para a matriz de LEDs
    }
}

int main() {
    gpio_init(button_A);             // Inicializa o botão A
    gpio_set_dir(button_A, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(button_A);          // Habilita o pull-up interno

    gpio_init(button_B);             // Inicializa o botão B
    gpio_set_dir(button_B, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(button_B);          // Habilita o pull-up interno

    // Inicializa o LED no pino 12
    gpio_init(led_red);
    gpio_set_dir(led_red, GPIO_OUT); // Configura o pino do LED como saída
    gpio_put(led_red, false);        // Garante que o LED comece apagado

    // Configuração da interrupção com callback
    gpio_set_irq_enabled_with_callback(button_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(button_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    // Inicializa o padrão da biblioteca stdio
    stdio_init_all();

    printf("Iniciando a animação da explosão da bomba\n");

    // Inicialização do PIO
    pio = pio0;
    uint offset = pio_add_program(pio, &animacoes_led_program);
    sm = pio_claim_unused_sm(pio, true);
    animacoes_led_program_init(pio, sm, offset, OUT_PIN);

    // Loop principal
    while (true) {
        // Exibe o número atual na matriz de LEDs
        exibir_numero(numero);  // Chama a função para exibir o número atual
        sleep_ms(100);  // Atualiza a cada 100 ms
    }
}

void gpio_irq_handler(uint gpio, uint32_t events) {
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    // Verifica se passou tempo suficiente desde o último evento (debouncing)
    if (current_time - last_time > 300000) {  // 300 ms de debouncing
        last_time = current_time;  // Atualiza o tempo do último evento

        // Verifica se o botão A foi pressionado (estado baixo)
        if (gpio == button_A && !(gpio_get(button_A))) {
            if (events & GPIO_IRQ_EDGE_FALL) {  // Verifica a borda de descida
                numero++;  // Incrementa o número
                if (numero > 9) numero = 9; // Limita o número máximo a 9
                printf("Botão A pressionado. Numero = %d\n", numero);
                gpio_put(led_red, true);  // Acende o LED
            }
        }
        // Verifica se o botão B foi pressionado (estado baixo)
        else if (gpio == button_B && !(gpio_get(button_B))) {
            if (events & GPIO_IRQ_EDGE_FALL) {  // Verifica a borda de descida
                numero--;  // Decrementa o número
                if (numero < 0) numero = 0; // Limita o número mínimo a 0
                printf("Botão B pressionado. Numero = %d\n", numero);
                gpio_put(led_red, false);  // Apaga o LED
            }
        }
    }
}
