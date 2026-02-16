#include "animal.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

void initAnimal(Animal* a, const char* nom) {
    assert(strlen(nom) < MAX_NOM_ANIMAL);
    strcpy(a->nom, nom);
}

void afficheAnimal(const Animal* a) {
    printf("%s", a->nom);
}

int animauxEgaux(const Animal* a1, const Animal* a2) {
    return strcmp(a1->nom, a2->nom) == 0;
}