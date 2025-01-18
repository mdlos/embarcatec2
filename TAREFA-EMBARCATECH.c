#include <stdio.h>
#include "pico/stdlib.h"

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
void liga_buzzer();
void desliga_buzzer(); 
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
                turn_on_led(1, 1, 1); // Liga todos os LEDS
                sleep_ms(1000);
                break;
            case '#':
                liga_buzzer(); // Aiva o buzzer
                sleep_ms(1000);
                desliga_buzzer(); // Desativa o buzzer
                sleep_ms(1000);
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

// Função para configurar o buzzer
void configurar_buzzer() {
    gpio_init(PIN_BUZZER);      // Inicializa o pino do buzzer
    gpio_set_dir(PIN_BUZZER, GPIO_OUT);  // Define como saída
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

// Função para ligar o buzzer
void liga_buzzer() {
    gpio_put(PIN_BUZZER, 1);  // Define o pino como 1 (ligado)
}

// Função para desligar o buzzer
void desliga_buzzer() {
    gpio_put(PIN_BUZZER, 0);  // Define o pino como 0 (desligado)
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