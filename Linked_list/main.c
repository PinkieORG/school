#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char word[10];
    struct node *next;
} node;

typedef struct node node;

void init(node **a) {
    *a = NULL;
}

int isEmpty(node **a) {
    if (*a == NULL) return 0;
    else return 1;
}

void addBeg(node **a, char *word) {
    node *z = malloc(sizeof(node));
    strcpy(z->word, word);

    z->next = *a;
    *a = z;
}

void addEnd(node **a, char *word) {
    node *z = malloc(sizeof(node));
    strcpy(z->word, word);
    z->next = NULL;

    if (isEmpty(a) == 0) {
        *a = z;
    } else {
        node *temp = *a;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = z;
    }
}

node *findNode(node **a, char *word) {
    node *z = malloc(sizeof(node));
    z = *a;

    if (isEmpty(a) != 0) {
        while (z != NULL) {
            if (strcmp(z->word, word) == 0) {
                return z;
            }
            z = z->next;
        }
        return NULL;
    } else {
    return NULL;
    }
}

void addBeh(node **a, node **beh, char *word) {
    node *z = malloc(sizeof(node));
    strcpy(z->word, word);

    z->next = (*beh)->next;
    (*beh)->next = z;
}

void addBef(node **a, node **bef, char *word) {
    node *z = malloc(sizeof(node));
    strcpy(z->word, word);
    z->next = *bef;
    node *temp = *a;

    while (temp->next != *bef) {
        temp = temp->next;
    }
    temp->next = z;
}

node *create(node **a, unsigned short x, FILE *file) {
    char str[10];
    for (unsigned short i = 0; i < x; i++) {
        //printf("element number %hu: ", i+1);
        fgets(str, 10, file);
        addEnd(a, str);
        //printf("\n");
    }
    return *a;
}

void show(node **a, FILE *file) {
    node *temp = *a;

    while (temp != NULL) {
        fprintf("%s", temp->word);
        fputs(temp->word, file);
        temp = temp->next;
    }
}

node *reverse(node **a) {
    node *prev = NULL;
    node *current = *a;
    node *next;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *a = prev;
    return *a;
}

node *remBeg(node **a) {
    node *temp = *a;
    *a = temp->next;
    temp->next = NULL;
    free(temp);
    return *a;
}

node *append(node **a, node **b) {
    node *temp1 = *a;
    node *temp2 = temp1;

    while (temp2->next != NULL) {
        temp2 = temp2->next;
    }
    temp2->next = *b;
    temp2 = temp1;
    return temp2;
}

void delEl(node **a, node **del) {
    node *temp = *a;
        while ((temp->next != NULL) && (temp->next != *del)) {
            temp = temp->next;
        }
        if (temp->next == *del) {
            temp->next = (*del)->next;
        }
}

int main()
{
    FILE *input1, *input2, *output;
    node *head1, *head2, *head3;
    init(&head1);
    show(&head1, output);

    return 0;
}
