#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char first[16];
    char family[16];
    unsigned birth;
    unsigned death;
    struct node *next;
} node;

typedef struct node node;

void load(FILE *file, FILE *output) {
    char letter;
    char birthStr[5];
    char deathStr[5];

    char first[16];
    char family[16];
    unsigned birth;
    unsigned death;

    unsigned short  i = 0;

    while (!feof(file)) {

        //Načítání křestního jména.
        letter = fgetc(file);

        while (letter != ' ') {
            first[i] = letter;
            letter = fgetc(file);
            i++;
        }
        first[i] = '\0';
        i = 0;

        //Načítání příjmení.
        letter = fgetc(file);

        while (letter != ' ') {
            family[i] = letter;
            letter = fgetc(file);
            i++;
        }
        family[i] = '\0';
        i = 0;

        //Načtení navíc.
        while (letter != '(') {
            letter = fgetc(file);
        }

        //Načítání data narozeni.
        letter = fgetc(file);

        while (letter != '-' ) {
            birthStr[i] = letter;
            letter = fgetc(file);
            i++;
        }
        birthStr[i] = '\0';
        i = 0;

        birth = strtoul(birthStr, NULL, 10);

        //Načítání data smrti.
        letter = fgetc(file);

        while (letter != ')' ) {
            deathStr[i] = letter;
            letter = fgetc(file);
            i++;
        }
        deathStr[i] = '\0';
        i = 0;

        death = strtoul(deathStr, NULL, 10);

        letter = fgetc(file);

        fwrite(first, sizeof(char[16]), 1, output);
        fwrite(family, sizeof(char[16]), 1, output);
        fwrite(&birth, sizeof(unsigned), 1, output);
        fwrite(&death, sizeof(unsigned), 1, output);
        }

}

void readBin(FILE *inputB, node **a) {
    char first[16];
    char family[16];
    unsigned birth;
    unsigned death;

    while(!feof(inputB)) {
        node *z = malloc(sizeof(node));

        fread(first, sizeof(char[16]), 1, inputB);
        strcpy(z->first,first);

        fread(family, sizeof(char[16]), 1, inputB);
        strcpy(z->family,family);

        fread(&birth, sizeof(unsigned), 1, inputB);
        z->birth = birth;

        fread(&death, sizeof(unsigned), 1, inputB);
        z->death = death;

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
}

//Vypsání seznamu na obrazovku.
void show(node **a) {
    node *temp = *a;

    while (temp->next != NULL) {
        printf("%s %s se narodil %d a zemrel %d", temp->first,  temp->family, temp->birth, temp->death);
        temp = temp->next;
    }
}

int isEmpty(node **a) {
    if (*a == NULL) return 0;
    else return 1;
}

int main()
{
    node *head = NULL;
    FILE *input, *output, *inputB;
    input = fopen("lesEcrivainsFrancaises.txt", "r");
    output = fopen("output.bin", "wb");

    load(input, output);

    fclose(output);
    inputB = fopen("output.bin", "rb");
    readBin(inputB, &head);
    show(&head);
    return 0;
}
