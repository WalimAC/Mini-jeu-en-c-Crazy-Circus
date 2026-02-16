/**
 * @file config.h
 * @brief Gestion de la configuration du jeu
 */

#pragma once
#include "animal.h"

enum { MAX_ANIMAUX = 10, MAX_ORDRES = 5, MAX_NOM_ORDRE = 3};

/**
 * @brief Structure représentant la configuration du jeu
 */

typedef struct {
    Animal animaux[MAX_ANIMAUX]; // Liste des animaux
    int nbAnimaux; // Nombre d'animaux
    char ordres[MAX_ORDRES][MAX_NOM_ORDRE]; // Liste des ordres
    int nbOrdres; // Nombre d'ordres
} Config;

/**
 * @brief Charge la configuration depuis le fichier crazy.cfg
 * @param[out] cfg Pointeur vers la configuration
 * @return 1 si succès et 0 si erreur
 */

int chargerConfig(Config* cfg);

/**
 * @brief Affiche les ordres disponibles
 * @param[in] cfg Pointeur vers la configuration
 */

void afficherOrdres(const Config* cfg);

/**
 * @brief Vérifie si un ordre existe dans la configuration
 * @param[in] cfg Pointeur vers la configuration
 * @param[in] ordre Ordre à vérifier
 * @return 1 si l'ordre existe et 0 sinon
 */

int ordreExiste(const Config* cfg, const char* ordre);