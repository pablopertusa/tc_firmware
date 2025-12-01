#include "linked_list.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    printf("Dame un valor para crear el primer modo: ");
    int value, result_scan;
    result_scan = scanf("%d", &value);
    if (result_scan != 1) {
        fprintf(stderr, "Input mal formateado, valor %d\n", result_scan);
        return 1;
    }
    Node *head = create_list(value);

    char mode;
    printf("check_length = c, print_list = p, add_element = a, remove_element = r, salir = s\n");
    printf("Introduce en qué modo quieres entrar: ");
    result_scan = scanf(" %c", &mode);
    if (result_scan != 1) {
        fprintf(stderr, "Input mal formateado, valor %d\n", result_scan);
        return 1;
    }
    int result_check;
    int action;
    char mode_2;
    int new_node_value;
    while (true) {
        if (mode == 's') {
            break;
        }
        else if (mode == 'c') {
            result_check = check_length(head);
            if (result_check == -1) {
                return 1;
            }
            printf("Longitud de la lista = %d\n", result_check);
        }
        else if (mode == 'p') {
            print_list(head);
        }
        else if (mode == 'a') {
            printf("Dime dónde: ");
            result_scan = scanf(" %d", &action);
            if (result_scan != 1) {
                fprintf(stderr, "Input mal formateado, valor %d\n", result_scan);
                return 1;
            }
            printf("Dime un valor: ");
            result_scan = scanf(" %d", &new_node_value);
            if (result_scan != 1) {
                fprintf(stderr, "Input mal formateado, valor %d\n", result_scan);
                return 1;
            }
            head = add_element(head, action, new_node_value);
            if (head == NULL) {
                fprintf(stderr, "Problema añadiendo elementos\n");
            }
        }
        else if (mode == 'r') {
            printf("Por posición (p), por valor (v)\n");
            printf("Dime el modo para eliminar: ");
            result_scan = scanf(" %c", &mode_2);
            if (result_scan != 1) {
                fprintf(stderr, "Input mal formateado, valor %d\n", result_scan);
                return 1;
            }
            if (mode_2 == 'p') {
                printf("Dime dónde: ");
                result_scan = scanf(" %d", &action);
                if (result_scan != 1) {
                    fprintf(stderr, "Input mal formateado, valor %d\n", result_scan);
                    return 1;
                }
                head = remove_element(head, action);
                if (head == NULL) {
                    printf("Lista vacía, terminando programa\n");
                    return 0;
                }
            }
            else if (mode_2 == 'v') {
                printf("Dime el valor: ");
                result_scan = scanf(" %d", &action);
                if (result_scan != 1) {
                    fprintf(stderr, "Input mal formateado, valor %d\n", result_scan);
                    return 1;
                }
                printf("a = ALL, o = ONCE\n");
                printf("Dime en qué modo: ");
                result_scan = scanf(" %c", &mode_2);
                if (result_scan != 1) {
                    fprintf(stderr, "Input mal formateado, valor %d\n", result_scan);
                    return 1;
                }
                if (mode_2 == 'a') {
                    head = remove_element_by_value(head, ALL, action);
                }
                else if (mode_2 == 'o') {
                    head = remove_element_by_value(head, ONCE, action);
                }
                if (head == NULL) {
                    printf("Lista vacía, terminando programa\n");
                    return 0;
                }
            }
        }
        printf("Ahora qué quieres hacer: ");
        result_scan = scanf(" %c", &mode);
        if (result_scan != 1) {
            fprintf(stderr, "Input mal formateado, valor %d\n", result_scan);
            return 1;
        }
    }
    return 0;
}