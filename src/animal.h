/**
 * @file animal.h
 * @brief Gestion des animaux
 */

#pragma once

enum { MAX_NOM_ANIMAL = 20 };

/**
 * @brief Structure représentant un animal
 */

typedef struct {
    char nom[MAX_NOM_ANIMAL]; // Nom de l'animal
} Animal;

/**
 * @brief Initialise un animal avec son nom
 * @param[out] a Pointeur vers l'animal à initialiser
 * @param[in] nom Nom de l'animal
 */

void initAnimal(Animal* a, const char* nom);

/**
 * @brief Affiche le nom d'un animal
 * @param[in] a Pointeur vers l'animal
 */

void afficheAnimal(const Animal* a);

/**
 * @brief Compare deux animaux
 * @param[in] a1 Premier animal
 * @param[in] a2 Second animal
 * @return 1 si identiques et 0 sinon
 */

int animauxEgaux(const Animal* a1, const Animal* a2);