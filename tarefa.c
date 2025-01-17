#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/pwm.h"

// Definições de pinos e constantes
#define PIN_LED_R 13
#define PIN_LED_B 12
#define PIN_LED_G 11
#define PIN_BUZZER 21
#define DEBOUNCE_DELAY 5 // Delay para debounce de teclas em milissegundos

// Mapeamento do teclado matricial
const uint8_t colunas[4] = {4, 3, 2, 1}; // Pinos das colunas
const uint8_t linhas[4] = {5, 6, 7, 8};  // Pinos das linhas
const char teclado[4][4] = 
{
  {'1', '2', '3', 'A'}, 
  {'4', '5', '6', 'B'}, 
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Protótipos das funções
void configurar_leds();
void configurar_buzzer();
void configurar_teclado();
void turn_on_led(bool red, bool blue, bool green);
void tocar_buzzer(int freq, int duration);
void parar_buzzer();
char leitura_teclado(); 

int main() 
{
    stdio_init_all();

    // Configurações iniciais
    configurar_leds();
    configurar_buzzer();
    configurar_teclado();

    while (true) 
    {    
        char tecla = leitura_teclado();

        switch (tecla) {
            case 'A':
                turn_on_led(1, 0, 0); // LED vermelho
                sleep_ms(1000);
                break;
            case 'B':
                turn_on_led(0, 1, 0); // LED verde
                sleep_ms(1000);
                break;
            case 'C':
                turn_on_led(0, 0, 1); // LED azul
                sleep_ms(1000);
                break;
            case 'D':
                turn_on_led(1, 1, 1); // Liga todos os LEDs
                sleep_ms(1000);
                break;
            case '#':
                tocar_buzzer(1000, 500); // Toca som de 1000 Hz por 500 ms
                break;
            case '*':
                tocar_buzzer(500, 1000); // Toca som de 500 Hz por 1 segundo
                break;
            default:
                turn_on_led(0, 0, 0); // Desliga os LEDs
                break;
        }

        sleep_ms(DEBOUNCE_DELAY); // Delay para evitar múltiplas leituras (debounce)
    }

    return 0;
}

// Função para configurar os LEDs
void configurar_leds() {
    gpio_init(PIN_LED_R);
    gpio_set_dir(PIN_LED_R, GPIO_OUT);
    gpio_init(PIN_LED_B);
    gpio_set_dir(PIN_LED_B, GPIO_OUT);
    gpio_init(PIN_LED_G);
    gpio_set_dir(PIN_LED_G, GPIO_OUT);
}

// Função para configurar o buzzer com PWM
void configurar_buzzer() {
    gpio_set_function(PIN_BUZZER, GPIO_FUNC_PWM); // Configura o pino do buzzer como saída PWM
    uint slice_num = pwm_gpio_to_slice_num(PIN_BUZZER); // Obtém o slice do PWM associado ao pino
    pwm_set_enabled(slice_num, true); // Habilita o PWM para o slice
}

// Função para tocar o buzzer com frequência e duração especificadas
void tocar_buzzer(int freq, int duration) {
    uint slice_num = pwm_gpio_to_slice_num(PIN_BUZZER); // Obtém o slice do PWM associado ao pino
    uint clock_freq = 125000000; // Frequência do clock do Pico (125 MHz)
    uint16_t top = clock_freq / freq - 1; // Calcula o divisor para gerar a frequência desejada

    pwm_set_wrap(slice_num, top); // Define o valor máximo do contador PWM
    pwm_set_gpio_level(PIN_BUZZER, top / 2); // Define o duty cycle em 50% (meia onda)
    
    sleep_ms(duration); // Aguarda pelo tempo especificado
    parar_buzzer(); // Para o buzzer após a duração
}

// Função para parar o buzzer
void parar_buzzer() {
    pwm_set_gpio_level(PIN_BUZZER, 0); // Define o nível PWM como 0 (som desligado)
}

// Função para configurar o teclado
void configurar_teclado() {
    for (int i = 0; i < 4; i++) {
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_OUT);
        gpio_put(colunas[i], 1); // Inicializa as colunas com 1 (desligado)
    }

    for (int i = 0; i < 4; i++) {
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_IN);
        gpio_pull_up(linhas[i]); // Habilita pull-up para evitar leituras erradas
    }
}

// Função para acionar os LEDs
void turn_on_led(bool red, bool blue, bool green) {
    gpio_put(PIN_LED_R, red);
    gpio_put(PIN_LED_B, blue);
    gpio_put(PIN_LED_G, green);
}

// Função para ler o teclado
char leitura_teclado() {
    char tecla = 'n'; // Inicializa com 'n' (nenhuma tecla pressionada)

    for (int coluna = 0; coluna < 4; coluna++) {
        gpio_put(colunas[coluna], 0); // Ativa a coluna (coloca como 0)

        for (int linha = 0; linha < 4; linha++) {
            if (gpio_get(linhas[linha]) == 0) { // Se uma tecla foi pressionada
                tecla = teclado[3 - linha][coluna]; // Mapeia a tecla pressionada
                while (gpio_get(linhas[linha]) == 0) { // Espera a tecla ser liberada (debounce)
                    sleep_ms(10); // Atraso para evitar múltiplas leituras
                }
                break;
            }
        }

        gpio_put(colunas[coluna], 1); // Desativa a coluna (coloca como 1)

        if (tecla != 'n') break; // Sai do laço se uma tecla foi pressionada
    }

    return tecla; // Retorna a tecla pressionada
}