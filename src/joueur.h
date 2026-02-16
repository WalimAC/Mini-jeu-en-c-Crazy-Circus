/**
 * @file joueur.h
 * @brief Gestion des joueurs
 */

#pragma once

enum { MAX_NOM_JOUEUR = 30, MAX_JOUEURS = 10 };

/**
 * @brief Structure représentant un joueur
 */

typedef struct {
    char nom[MAX_NOM_JOUEUR]; // Nom du joueur
    int score; // Score du joueur
    int peutJouer; // 1 si peut jouer ce tour et 0 sinon
} Joueur;

/**
 * @brief Liste de joueurs
 */

typedef struct {
    Joueur joueurs[MAX_JOUEURS]; // Tableau des joueurs
    int nb; // Nombre de joueurs
} Joueurs;

/**
 * @brief Initialise la liste de joueurs
 * @param[out] js Pointeur vers la liste
 * @param[in] noms Tableau des noms
 * @param[in] nbNoms Nombre de noms
 * @return 1 si succès et 0 si erreur
 */

int initJoueurs(Joueurs* js, char** noms, int nbNoms);

/**
 * @brief Trouve un joueur par son nom
 * @param[in] js Pointeur vers la liste
 * @param[in] nom Nom du joueur
 * @return Index du joueur ou -1 si non trouvé
 */

int trouverJoueur(const Joueurs* js, const char* nom);

/**
 * @brief Réinitialise les joueurs pour un nouveau tour
 * @param[in,out] js Pointeur vers la liste
 */

void reinitTour(Joueurs* js);

/**
 * @brief Compte le nombre de joueurs pouvant encore jouer
 * @param[in] js Pointeur vers la liste
 * @return Nombre de joueurs pouvant jouer
 */

int nbJoueursActifs(const Joueurs* js);

/**
 * @brief Affiche les scores finaux
 * @param[in] js Pointeur vers la liste
 */

void afficherScores(const Joueurs* js);