#ifndef linked_list
#define linked_list

typedef enum {
    ONCE,
    ALL
} RemoveMode;

typedef struct node {
    int num;
    struct node *next;
} Node;

Node *create_list(int value);
void free_node(Node *node);
int check_length(Node *node);
void print_list(Node *head);
Node *add_element(Node *head, int pos,  int value);
Node *remove_element(Node *head, int pos);
Node *remove_element_by_value(Node *head, RemoveMode mode, int value);

#endif