//Embarcatec 
//Tarefa 1 - Atividade 2: 
//Discentes: Márcio de Arruda Fonseca
//           João Paulo
//           Sara 
//           Paola
//           Pedro
//           Jvrsoare
//           Alexsami
//           Moises Amorim

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
void piscar_leds();

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

        if (tecla != 'n') { // Verifica se uma tecla foi pressionada
            printf("Tecla pressionada: %c\n", tecla);

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
                    turn_on_led(1, 1, 1); // Todos os LEDs
                    sleep_ms(1000);
                    break;
                case '#':
                    tocar_buzzer(1000, 500); // Som de 1000 Hz por 500 ms
                    break;
                case '*':
                    piscar_leds(); // Função de piscar os LEDs
                    break;
                default:
                    turn_on_led(0, 0, 0); // Desliga os LEDs
                    break;
            }
        }

        sleep_ms(DEBOUNCE_DELAY); // Delay para debounce
    }

    return 0;
}

// Configura os LEDs
void configurar_leds() {
    gpio_init(PIN_LED_R);
    gpio_set_dir(PIN_LED_R, GPIO_OUT);
    gpio_init(PIN_LED_B);
    gpio_set_dir(PIN_LED_B, GPIO_OUT);
    gpio_init(PIN_LED_G);
    gpio_set_dir(PIN_LED_G, GPIO_OUT);
}

// Configura o buzzer com PWM
void configurar_buzzer() {
    gpio_set_function(PIN_BUZZER, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(PIN_BUZZER);
    pwm_set_enabled(slice_num, true);
}

// Toca o buzzer com frequência e duração especificadas
void tocar_buzzer(int freq, int duration) {
    uint slice_num = pwm_gpio_to_slice_num(PIN_BUZZER);
    uint clock_freq = 125000000;
    uint16_t top = clock_freq / freq - 1;

    pwm_set_wrap(slice_num, top);
    pwm_set_gpio_level(PIN_BUZZER, top / 2);

    sleep_ms(duration);
    parar_buzzer();
}

// Para o buzzer
void parar_buzzer() {
    pwm_set_gpio_level(PIN_BUZZER, 0);
}

// Configura o teclado matricial
void configurar_teclado() {
    for (int i = 0; i < 4; i++) {
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_OUT);
        gpio_put(colunas[i], 1);
    }

    for (int i = 0; i < 4; i++) {
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_IN);
        gpio_pull_up(linhas[i]);
    }
}

// Lê a tecla pressionada
char leitura_teclado() {
    char tecla = 'n';

    for (int coluna = 0; coluna < 4; coluna++) {
        gpio_put(colunas[coluna], 0);

        for (int linha = 0; linha < 4; linha++) {
            if (gpio_get(linhas[linha]) == 0) {
                tecla = teclado[3 - linha][coluna];
                while (gpio_get(linhas[linha]) == 0) {
                    sleep_ms(10);
                }
                break;
            }
        }

        gpio_put(colunas[coluna], 1);

        if (tecla != 'n') break;
    }

    return tecla;
}

// Pisca os LEDs sequencialmente
void piscar_leds() {
    for (int i = 0; i < 3; i++) {
        turn_on_led(1, 0, 0);
        sleep_ms(200);
        turn_on_led(0, 1, 0);
        sleep_ms(200);
        turn_on_led(0, 0, 1);
        sleep_ms(200);
    }
    turn_on_led(0, 0, 0);
}

// Acende os LEDs com as cores especificadas
void turn_on_led(bool red, bool blue, bool green) {
    gpio_put(PIN_LED_R, red);
    gpio_put(PIN_LED_B, blue);
    gpio_put(PIN_LED_G, green);
}

