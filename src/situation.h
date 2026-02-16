/**
 * @file situation.h
 * @brief Gestion d'une situation de jeu (2 podiums)
 */

#pragma once
#include "podium.h"

/**
 * @brief Structure représentant une situation de jeu
 */

typedef struct {
    Podium bleu;  // Podium bleu
    Podium rouge; // Podium rouge
} Situation;

/**
 * @brief Initialise une situation vide
 * @param[out] s Pointeur vers la situation
 */

void initSituation(Situation* s);

/**
 * @brief Copie une situation dans une autre
 * @param[in]  s1 Situation initial
 * @param[out] s2 Situation final
 */

void copierSituation(const Situation* s1, Situation* s2);

/**
 * @brief Compare deux situations
 * @param[in] s1 Première situation
 * @param[in] s2 Seconde situation
 * @return 1 si identiques et 0 sinon
 */

int situationsEgales(const Situation* s1, const Situation* s2);

/**
 * @brief Affiche une situation de jeu
 * @param[in] s Pointeur vers la situation
 */

void afficheSituation(const Situation* s);

/**
 * @brief Exécute l'ordre KI (bleu vers rouge)
 * @param[in,out] s Pointeur vers la situation
 */

void executerKI(Situation* s);

/**
 * @brief Exécute l'ordre LO (rouge vers bleu)
 * @param[in,out] s Pointeur vers la situation
 */

void executerLO(Situation* s);

/**
 * @brief Exécute l'ordre SO (échange des sommets)
 * @param[in,out] s Pointeur vers la situation
 */

void executerSO(Situation* s);

/**
 * @brief Exécute l'ordre NI (base vers sommet du bleu)
 * @param[in,out] s Pointeur vers la situation
 */

void executerNI(Situation* s);

/**
 * @brief Exécute l'ordre MA (base vers sommet du rouge)
 * @param[in,out] s Pointeur vers la situation
 */

void executerMA(Situation* s);