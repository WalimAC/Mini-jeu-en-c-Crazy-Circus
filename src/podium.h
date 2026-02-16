/**
 * @file podium.h
 * @brief Gestion d'un podium (pile d'animaux)
 */

#pragma once
#include "animal.h"

enum { MAX_ANIMAUX_PODIUM = 10 };

/**
 * @brief Structure représentant un podium (pile d'animaux)
 */

typedef struct {
    Animal animaux[MAX_ANIMAUX_PODIUM]; // Tableau des animaux
    int nb; // Nombre d'animaux sur le podium
} Podium;

/**
 * @brief Initialise un podium vide
 * @param[out] p Pointeur vers le podium
 */

void initPodium(Podium* p);

/**
 * @brief Vérifie si un podium est vide
 * @param[in] p Pointeur vers le podium
 * @return 1 si vide et 0 sinon
 */

int estVidePodium(const Podium* p);

/**
 * @brief Ajoute un animal au sommet du podium
 * @param[in,out] p Pointeur vers le podium
 * @param[in] a Pointeur vers l'animal à ajouter
 */

void empilerPodium(Podium* p, const Animal* a);

/**
 * @brief Retire l'animal au sommet du podium
 * @param[in,out] p Pointeur vers le podium
 * @param[out] a Pointeur où stocker l'animal retiré
 */

void depilerPodium(Podium* p, Animal* a);

/**
 * @brief Obtient l'animal au sommet sans le retirer
 * @param[in] p Pointeur vers le podium
 * @param[out] a Pointeur où stocker l'animal
 */

void sommetPodium(const Podium* p, Animal* a);

/**
 * @brief Obtient l'animal à la base sans le retirer
 * @param[in] p Pointeur vers le podium
 * @param[out] a Pointeur où stocker l'animal
 */

void basePodium(const Podium* p, Animal* a);

/**
 * @brief Fait monter l'animal de la base au sommet
 * @param[in,out] p Pointeur vers le podium
 */

void monterBasePodium(Podium* p);

/**
 * @brief Copie un podium dans un autre
 * @param[in] p1 Podium à copier
 * @param[out] p2 Podium copier
 */

void copierPodium(const Podium* p1, Podium* p2);

/**
 * @brief Affiche un podium
 * @param[in] p Pointeur vers le podium
 */

void affichePodium(const Podium* p);

/**
 * @brief Compare deux podiums
 * @param[in] p1 Premier podium
 * @param[in] p2 Second podium
 * @return 1 si identiques et 0 sinon
 */

int podiumsEgaux(const Podium* p1, const Podium* p2);