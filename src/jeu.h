/**
 * @file jeu.h
 * @brief Logique principale du jeu
 */

#pragma once
#include "config.h"
#include "situation.h"
#include "joueur.h"

/**
 * @brief Calcule le nombre total de cartes selon la formule (n+1)!
 * @param[in] n Nombre d'animaux
 * @return Nombre de cartes = (n+1)!
 */
int calculerNbCartes(int n);

/**
 * @brief Structure représentant une carte objectif
 */

typedef struct {
    Situation sit; // Situation de la carte
    int utilisee; // 1 si déjà utilisée et 0 sinon
} Carte;

/**
 * @brief Structure représentant le jeu
 */

typedef struct {
    Config cfg; // Configuration
    Situation actuelle; // Situation actuelle
    Situation objectif; // Situation à atteindre
    Joueurs joueurs; // Liste des joueurs
    Carte* cartes; // Pointeur vers les cartes (allocation dynamique)
    int nbCartes; // Nombre de cartes
    int indexProchaineCarte; // Index de la prochaine carte à tirer
} Jeu;

/**
 * @brief Initialise le jeu
 * @param[out] jeu Pointeur vers le jeu
 * @param[in] noms Noms des joueurs
 * @param[in] nbJoueurs Nombre de joueurs
 * @return 1 si succès et 0 si erreur
 */

int initJeu(Jeu* jeu, char** noms, int nbJoueurs);

/**
 * @brief Génère toutes les cartes possibles
 * @param[in,out] jeu Pointeur vers le jeu
 */

void genererCartes(Jeu* jeu);

/**
 * @brief Mélanger les Cartes du jeu
 * @param[in,out] jeu Pointeur vers le jeu
 */

void melangerCartes(Jeu* jeu);

/**
 * @brief Tire une carte au hasard
 * @param[in,out] jeu Pointeur vers le jeu
 * @return 1 si une carte a été tirée et 0 si plus de cartes disponibles
 */

int tirerCarte(Jeu* jeu);

/**
 * @brief Affiche la situation actuelle et l'objectif
 * @param[in] jeu Pointeur vers le jeu
 */

void afficherSituationJeu(const Jeu* jeu);

/**
 * @brief Exécute une séquence d'ordres
 * @param[in] jeu Pointeur vers le jeu
 * @param[in] sequence Séquence d'ordres
 * @param[out] resultat Situation résultante
 * @return 1 si valide et 0 sinon
 */

int executerSequence(const Jeu* jeu, const char* sequence, Situation* resultat, char* ordreEchoue);

/**
 * @brief Traite la saisie d'un joueur
 * @param[in,out] jeu Pointeur vers le jeu
 * @param[in] saisie Saisie du joueur
 * @param[out] finPartie Pointeur pour indiquer la fin de la partie
 */

void traiterSaisie(Jeu* jeu, const char* saisie, int* finPartie);

/**
 * @brief Lance une partie complète
 * @param[in,out] jeu Pointeur vers le jeu
 */

void lancerPartie(Jeu* jeu);

/**
 * @brief Libère les ressources du jeu
 * @param[in,out] jeu Pointeur vers le jeu
 */

void quitterJeu(Jeu* jeu);