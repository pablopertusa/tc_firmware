#include "linked_list.h"
#include "stdlib.h"
#include <stdio.h>

Node *create_list(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        perror("Durante la creación de la lista");
        return NULL;
    }
    node->num = value;
    node->next = NULL;
    return node;
}

int check_length(Node *node) {
    if (node == NULL) {
        fprintf(stderr, "Nodo nulo recibido para check_length\n");
        return -1;
    }
    int resul = 1;
    while (node->next != NULL) {
        resul++;
        node = node->next;
    }
    return resul;
}

void print_list(Node *head) {
    if (head == NULL) {
        fprintf(stderr, "Nodo nulo recibido para check_length\n");
        return;
    }
    unsigned int acum = 0;
    Node *node = head;
    while (node != NULL) {
        printf("Node %d = %d\n", acum, node->num);
        node = node->next;
        acum++;
    }
}

Node *add_element(Node *head, int pos,  int value) {
    if (head == NULL) {
        fprintf(stderr, "Nodo nulo recibido para add_element\n");
        return NULL;
    }
    int length = check_length(head);
    if (pos > length) {
        fprintf(stderr, "Posición fuera de rango\n");
        return head;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Durante add_element");
        return NULL;
    }
    new_node->num = value;
    if (pos == 0) {
        new_node->next = head;
        return new_node;
    }
    Node *act = head;
    unsigned int acum = 0;
    while (acum < pos - 1) {
        act = act->next;
        acum++;
    }
    new_node->next = act->next;
    act->next = new_node;
    return head;
}

void free_node(Node *node) {
    if (node == NULL) {
        fprintf(stderr, "Nodo nulo recibido para free_node\n");
        return;
    }
    free(node);
}

Node *remove_element(Node *head, int pos) {
    if (head == NULL) {
        fprintf(stderr, "Nodo nulo recibido para check_length\n");
        return NULL;
    }
    int length = check_length(head);
    if (pos > length - 1) {
        fprintf(stderr, "Posición fuera de rango\n");
        return head;
    }
    if (pos == 0) {
        return head->next;
    }
    Node *act = head;
    Node *ant = head; 
    unsigned int acum = 0;
    while (acum < pos) {
        ant = act;
        act = ant->next;
        acum++;
    }
    // es el final
    if (act->next == NULL) {
        ant->next = NULL;
        free_node(act);
        return head;
    }
    // hay uno después
    else {
        ant->next = act->next;
        free(act);
        return head;
    }
}

Node *remove_element_by_value(Node *head, RemoveMode mode, int value) {
    if (head == NULL) {
        fprintf(stderr, "Nodo nulo recibido para check_length\n");
        return NULL;
    }
    Node *act = head;
    Node *ant = NULL;
    Node *result_head = head;
    Node *temp;
    while (act != NULL) {
        if (act->num == value) {
            if (ant == NULL) {
                result_head = act->next;
            }
            else {
                ant->next = act->next;
            }
            temp = act;
            act = act->next;
            free_node(temp);
            if (mode == ONCE) {
                return result_head;
            }
        }
        else {
            ant = act;
            act = act->next;
        }
    }
    return result_head;
}
