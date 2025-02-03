#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Definições de pinos
#define LED_R 12

#define BOTAO_A_PIN 5  // Botão A
#define BOTAO_B_PIN 6  // Botão B

volatile int contador = 0;  // Contador global

// Função para configurar o LED
void configurar_led() {
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
}

// Função de interrupção para o Botão A
void botao_a_isr() {
    // Verifica se o botão foi pressionado (estado baixo)
    if (gpio_get(BOTAO_A_PIN) == 0) {  
        contador++;  // Incrementa o contador
        gpio_put(LED_R, 1);  // Acende o LED
        printf("Botão A pressionado, contador: %d\n", contador);  // Depuração
    }
    gpio_acknowledge_irq(BOTAO_A_PIN, GPIO_IRQ_EDGE_FALL);  // Limpa a interrupção
}

// Função de interrupção para o Botão B
void botao_b_isr() {
    // Verifica se o botão foi pressionado (estado baixo)
    if (gpio_get(BOTAO_B_PIN) == 0) {  
        contador--;  // Decrementa o contador
        gpio_put(LED_R, 0);  // Apaga o LED
        printf("Botão B pressionado, contador: %d\n", contador);  // Depuração
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "pico/bootrom.h"
#include "hardware/timer.h"

// Pino de saída
const uint led_red = 13;    // atribui o pino do led vermelho, do led RGB
const uint button_A = 5;    // atribui o pino do botão A à variável
const uint button_B = 6;    // atribui o pino do botão B à variável

// Prototipação da função de interrupção
static void gpio_irq_handler(uint gpio, uint32_t events);

// Variáveis globais
static volatile uint numero = 0;
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)

int main() {
    gpio_init(button_A);             // inicializa o botão A
    gpio_set_dir(button_A, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(button_A);          // Habilita o pull-up interno

    gpio_init(button_B);             // inicializa o botão B
    gpio_set_dir(button_B, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(button_B);          // Habilita o pull-up interno

    // Configuração da interrupção com callback
    gpio_set_irq_enabled_with_callback(button_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    // Configuração da interrupção com callback
    gpio_set_irq_enabled_with_callback(button_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    // Inicializa o padrão da biblioteca stdio
    stdio_init_all();

    printf("Iniciando a animação da explosão da bomba\n");
    printf(" Numero = %d\n", numero);

    // Animação da explosão da bomba
    while (true) {
        gpio_init(led_red);                 // Inicializa o pino do LED
        gpio_set_dir(led_red, GPIO_OUT);    // Configura o pino como saída
        gpio_put(led_red, false);           // Garante que o LED inicie apagado
        
        sleep_ms(200);                      // Aguarda 0.2 segundo antes de ligar
        gpio_put(led_red, true);            // Liga o LED
    }
}

void gpio_irq_handler(uint gpio, uint32_t events) {
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    // Verifica se passou tempo suficiente desde o último evento (debouncing)
    if (current_time - last_time > 300000) {  // 200 ms de debouncing
        last_time = current_time;  // Atualiza o tempo do último evento

        // Verifica se o botão foi pressionado (estado baixo)
        if (gpio == button_A && !(gpio_get(button_A))) {
            if (events & GPIO_IRQ_EDGE_FALL) {  // Verifica a borda de descida
                numero++;  // Incrementa o número
                printf("Botão A pressionado. Numero = %d\n", numero);
            }
        }
        else if (gpio == button_B && !(gpio_get(button_B))) {
            if (events & GPIO_IRQ_EDGE_FALL) {  // Verifica a borda de descida
                numero--;  // Decrementa o número
                printf("Botão B pressionado. Numero = %d\n", numero);
            }
        }
    }

}
