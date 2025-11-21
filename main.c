#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define BYTE_SIZE 8

// asumo que los índices de los leds van de derecha a izquierda, el 0 es el LSB

int toggle_led(unsigned char *leds, int i);
void print_leds(unsigned char *leds);
int check_led(unsigned char *leds, int i);
int automatic_turn_on(unsigned char *leds);
int automatic_turn_off(unsigned char *leds);

int main() {
    unsigned char leds = 0;
    char mode, action_1;
    int action_2, result_scan, result;
    const char *msg_1 = "Sistema de 8 LEDs, iniciando...\n";
    const char *msg_2 = "Introduce [modos = {a,m,s}]: ";
    const char *msg_3 = "Elige en qué modo continuar: ";
    const char *msg_4 = "Introduce [instrucción = {c, t}] [posición = {0-7}]: ";
    const char *msg_5 = "Introduce tipo de automático [tipo = {e, a}] ";
    printf("%s", msg_1);
    printf("Estado actual de los leds:\n");
    print_leds(&leds);
    printf("%s", msg_2);
    scanf("%c", &mode);
    while (true) {
        if (mode == 's') {
            break;
        }
        else if (mode == 'm') {
            printf("%s", msg_4);
            result_scan = scanf(" %c %d", &action_1, &action_2);
            if (result_scan != 2) {
                fprintf(stderr, "Input mal formateado, valor %d\n", result_scan);
                return 1;
            }
            if (action_1 == 'c') {
                result = check_led(&leds, action_2);
                if (result == -1) {
                    fprintf(stderr, "Problema chequeando led\n");
                    return 1;
                }
                else if (result == 1) {
                    printf("El led %d está encendido\n", action_2);
                }
                else if (result == 0) {
                    printf("El led %d está apagado\n", action_2);
                }
            }
            else if (action_1 == 't') {
                result = toggle_led(&leds, action_2);
                if (result) {
                    printf("El led %d se ha cambiado\n", action_2);
                }
                else {
                    fprintf(stderr, "Problema cambiando led\n");
                    return 1;
                }
            }
        }
        else if (mode == 'a') {
            printf("%s", msg_5);
            result_scan = scanf(" %c", &action_1);
            if (result_scan != 1) {
                fprintf(stderr, "Input mal formateado, valor %d\n", result_scan);
                return 1;
            }
            if (action_1 == 'e') {
                automatic_turn_on(&leds);
            }
            else if (action_1 == 'a') {
                automatic_turn_off(&leds);
            }
            else {
                fprintf(stderr, "Acción inválida: %c", action_1);
                return 1;
            }
        }
        printf("Estado actual de los leds:\n");
        print_leds(&leds);
        printf("%s", msg_3);
        scanf(" %c", &mode);
    }
}

void print_leds(unsigned char *leds) {
    if (leds == NULL) {
        fprintf(stderr, "Null pointer to leds\n");
        return;
    }
    unsigned char bit;
    for (int i = BYTE_SIZE - 1; i >= 0; i--) {
        bit = (*leds >> i) & 1U;
        printf("%d",bit);
    }
    printf("\n");
}

int check_led(unsigned char *leds, int i) {
    if (leds == NULL) {
        fprintf(stderr, "Null pointer to leds\n");
        return -1;
    }
    unsigned char aux;
    int is_on;
    if (i < 0 || i >= 8) {
        fprintf(stderr, "Invalid position\n");
        return -1;
    }
    is_on = (int)(((*leds) >> (i)) & 1U);
    return is_on;
}

int toggle_led(unsigned char *leds, int i) {
    // 0 si hay fallo 1 si no
    if (leds == NULL) {
        fprintf(stderr, "Null pointer to leds\n");
        return 0;
    }
    unsigned char is_on, aux;
    if (i < 0 || i >= 8) {
        fprintf(stderr, "Invalid position\n");
        return 0;
    }
    is_on = ((*leds) >> (i)) & 1U;
    if (is_on) {
        aux = pow(2, BYTE_SIZE) - 1 - pow(2, i); // todos los bits a 1 menos el i
        aux = *leds & aux;
    }
    else {
        aux = pow(2, i); // todos a 0 menos el i
        aux = *leds | aux;
    }
    *leds = aux;
    return 1;
}

int automatic_turn_on(unsigned char *leds) {
    // 0 si hay fallo 1 si no
    int result = 1;
    struct timespec t;
    t.tv_nsec = 500000000;
    t.tv_sec = 0;
    if (leds == NULL) {
        fprintf(stderr, "Null led pointer in automatic\n");
        return 0;
    }
    for (int i = 0; i <  BYTE_SIZE; i++) {
        if (!check_led(leds, i)) {
            printf("Encendiendo led %d\n", i);
            result = result && toggle_led(leds, i);
            nanosleep(&t, NULL);
        }
    }
    return result;
}

int automatic_turn_off(unsigned char *leds) {
    // 0 si hay fallo 1 si no
    int result = 1;
    struct timespec t;
    t.tv_nsec = 500000000;
    t.tv_sec = 0;
    if (leds == NULL) {
        fprintf(stderr, "Null led pointer in automatic\n");
        return 0;
    }
    for (int i = 0; i <  BYTE_SIZE; i++) {
        if (check_led(leds, i) == 1) {
            printf("Apagando led %d\n", i);
            result = result && toggle_led(leds, i);
            nanosleep(&t, NULL);
        }
    }
    return result;
}