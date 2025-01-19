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
//           Ramom Silva

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
void piscar_leds(float time, int repeticoes); // Função para piscar os LEDs
void turn_leds_sequence(int value);
void tocar_brilha_brilha_com_leds(); //Toca musica Brilha Brilha e acende leds de acordo com a nota

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
                    tocar_brilha_brilha_com_leds(); // Toca a musica Brilha Brilha
                    break;
                case '*':
                    tocar_buzzer(500, 1000); // Som de 500 Hz por 1 segundo
                    break;
                case '0':
                    piscar_leds(500, 1); // Função para piscar os LEDs
                    break;
                case '1':
                    turn_leds_sequence(1);
                    break;
                case '2':
                    turn_leds_sequence(2);
                    break;
                case '3':
                    turn_leds_sequence(3);
                    break;    
                case '4':
                    turn_leds_sequence(4);
                    break;
                case '5':
                    turn_leds_sequence(5);
                    break;
                case '6':
                    turn_leds_sequence(6);
                    break;
                case '7':
                    turn_leds_sequence(7);
                    break;
                case '8':
                    turn_leds_sequence(8);
                    break;
                case '9':
                    turn_leds_sequence(9);
                    break;
            }
        }

        sleep_ms(DEBOUNCE_DELAY); // Delay para debounce
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
    uint32_t durationLed = duration / 3; // Gerar um valor para o tempo de cada led

    pwm_set_wrap(slice_num, top); // Define o valor máximo do contador PWM
    pwm_set_gpio_level(PIN_BUZZER, top / 2); // Define o duty cycle em 50% (meia onda)
    piscar_leds(durationLed, 3); //Piscar leds enquanto tiver som
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

void turn_leds_sequence(int value){
   while (value > 0) {
        turn_on_led(0, 0, 1);
        sleep_ms(200);
        turn_on_led(0, 0, 0);
        sleep_ms(200);
        if(value == 1){
            break;
        }
        turn_on_led(0, 1, 0);
        sleep_ms(200);
        turn_on_led(0, 0, 0);
        sleep_ms(200);
        if(value == 2){
            break;
        }
        turn_on_led(1, 0, 0);
        sleep_ms(200);
        turn_on_led(0, 0, 0);
        sleep_ms(200);
        if(value == 3){
            break;
        }
        value-=3;
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

// Função para piscar os LEDs
void piscar_leds(float time, int repeticoes) {
    int i = 0;

    while(i < repeticoes) {
        turn_on_led(1, 0, 0); // Acende LED vermelho
        sleep_ms(time); // Espera 500 ms
        turn_on_led(0, 0, 0); // Desliga todos os LEDs
        sleep_ms(time); // Espera 500 ms

        turn_on_led(0, 1, 0); // Acende LED verde
        sleep_ms(time); // Espera 500 ms
        turn_on_led(0, 0, 0); // Desliga todos os LEDs
        sleep_ms(time); // Espera 500 ms

        turn_on_led(0, 0, 1); // Acende LED azul
        sleep_ms(time); // Espera 500 ms
        turn_on_led(0, 0, 0); // Desliga todos os LEDs
        sleep_ms(time); // Espera 500 ms
        i++;
    }
    parar_buzzer(); // Para o buzzer após a duração
}


// Função principal para tocar "Brilha Brilha Estrelinha" com LEDs
void tocar_brilha_brilha_com_leds() {
    // Primeira linha: "Brilha, brilha, estrelinha"
    turn_on_led(1, 0, 0); // LED vermelho
    tocar_buzzer(392, 500); // Sol
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(1, 0, 0); // LED vermelho
    tocar_buzzer(392, 500); // Sol
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(0, 1, 0); // LED verde
    tocar_buzzer(440, 500); // Lá
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(0, 1, 0); // LED verde
    tocar_buzzer(440, 500); // Lá
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(0, 0, 1); // LED azul
    tocar_buzzer(494, 500); // Si
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(0, 0, 1); // LED azul
    tocar_buzzer(494, 500); // Si
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(1, 0, 0); // LED vermelho
    tocar_buzzer(440, 1000); // Lá
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(500);

    // Segunda linha: "Como eu quero te ver brilhar"
    turn_on_led(1, 0, 0); // LED vermelho
    tocar_buzzer(392, 500); // Sol
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(1, 0, 0); // LED vermelho
    tocar_buzzer(392, 500); // Sol
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(0, 1, 0); // LED verde
    tocar_buzzer(349, 500); // Fá
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(0, 1, 0); // LED verde
    tocar_buzzer(349, 500); // Fá
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(0, 0, 1); // LED azul
    tocar_buzzer(330, 500); // Mi
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(0, 0, 1); // LED azul
    tocar_buzzer(330, 500); // Mi
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(1, 0, 0); // LED vermelho
    tocar_buzzer(294, 1000); // Ré
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(500);

    // Terceira linha: "Brilha, brilha, estrelinha"
    turn_on_led(1, 0, 0); // LED vermelho
    tocar_buzzer(392, 500); // Sol
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(1, 0, 0); // LED vermelho
    tocar_buzzer(392, 500); // Sol
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(0, 1, 0); // LED verde
    tocar_buzzer(440, 500); // Lá
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(0, 1, 0); // LED verde
    tocar_buzzer(440, 500); // Lá
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(0, 0, 1); // LED azul
    tocar_buzzer(494, 500); // Si
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(0, 0, 1); // LED azul
    tocar_buzzer(494, 500); // Si
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(1, 0, 0); // LED vermelho
    tocar_buzzer(440, 1000); // Lá
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(500);

    // Quarta linha: "Como eu quero te ver brilhar"
    turn_on_led(1, 0, 0); // LED vermelho
    tocar_buzzer(392, 500); // Sol
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(1, 0, 0); // LED vermelho
    tocar_buzzer(392, 500); // Sol
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(0, 1, 0); // LED verde
    tocar_buzzer(349, 500); // Fá
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(0, 1, 0); // LED verde
    tocar_buzzer(349, 500); // Fá
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(0, 0, 1); // LED azul
    tocar_buzzer(330, 500); // Mi
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(0, 0, 1); // LED azul
    tocar_buzzer(330, 500); // Mi
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(250);

    turn_on_led(1, 0, 0); // LED vermelho
    tocar_buzzer(294, 1000); // Ré
    turn_on_led(0, 0, 0); // Apagar LEDs
    sleep_ms(500);
}






