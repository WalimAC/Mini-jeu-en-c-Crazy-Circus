#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996)

int calculerNbCartes(int n) {
    if (n < 0) return 0;
    int resultat = 1;
    for (int i = 2; i <= n + 1; i++) {
        resultat *= i;
    }
    return resultat;
}

int compterCartesUtilisees(const Jeu* jeu) {
    int compte = 0;
    for (int i = 0; i < jeu->nbCartes; i++) {
        if (jeu->cartes[i].utilisee) compte++;
    }
    return compte;
}

int initJeu(Jeu* jeu, char** noms, int nbJoueurs) {
    if (!chargerConfig(&jeu->cfg)) return 0;
    if (!initJoueurs(&jeu->joueurs, noms, nbJoueurs)) return 0;
    
    int nbAnimaux = jeu->cfg.nbAnimaux;
    int nbCartesMax = calculerNbCartes(nbAnimaux);
    
    jeu->cartes = malloc(nbCartesMax * sizeof(Carte));
    if (!jeu->cartes) {
        printf("Erreur: allocation mémoire pour les cartes\n");
        return 0;
    }
    
    genererCartes(jeu);
    melangerCartes(jeu); 

    jeu->indexProchaineCarte = 0;
    return 1;
}

void genererCartes(Jeu* jeu) {
    jeu->nbCartes = 0;
    int n = jeu->cfg.nbAnimaux;
    if (n <= 0) return;

    int perm[MAX_ANIMAUX];
    int c[MAX_ANIMAUX];
    for (int i = 0; i < n; i++) {
        perm[i] = i;
        c[i] = 0;
    }
    
    int nbCartesMax = calculerNbCartes(n);

    while (1) {
        for (int coupe = 0; coupe <= n && jeu->nbCartes < nbCartesMax; coupe++) {
            Situation s;
            initSituation(&s);
            for (int i = 0; i < coupe; i++) {
                empilerPodium(&s.bleu, &jeu->cfg.animaux[perm[i]]);
            }
            for (int i = coupe; i < n; i++) {
                empilerPodium(&s.rouge, &jeu->cfg.animaux[perm[i]]);
            }

            jeu->cartes[jeu->nbCartes].sit = s;
            jeu->cartes[jeu->nbCartes].utilisee = 0;
            jeu->nbCartes++;
        }

        int i = 0;
        while (i < n && c[i] >= i) {
            c[i] = 0;
            i++;
        }
        if (i >= n) break; 

        if (i % 2 == 0) {
            int temp = perm[0]; 
            perm[0] = perm[i];
             perm[i] = temp;
        } else {
            int temp = perm[c[i]]; 
            perm[c[i]] = perm[i];
            perm[i] = temp;
        }
        c[i]++;

    }
}

void melangerCartes(Jeu* jeu) {
    for (int i = jeu->nbCartes - 1; i >= 1; i--) {
        int j = rand() % (i + 1);
        Carte temp = jeu->cartes[i];
        jeu->cartes[i] = jeu->cartes[j];
        jeu->cartes[j] = temp;
    }
}

int tirerCarte(Jeu* jeu) {
    int idx = jeu->indexProchaineCarte;
    int nb = jeu->nbCartes;
    if (idx < nb) {
        jeu->objectif = jeu->cartes[idx].sit;
        jeu->indexProchaineCarte++;
        return 1;
    }
    return 0; 
}

void afficherSituationJeu(const Jeu* jeu) {
    int largeurs[4] = {4, 4, 4, 4}; 
    const Podium* piles[4];

    piles[0] = &jeu->actuelle.bleu;
    piles[1] = &jeu->actuelle.rouge;
    piles[2] = &jeu->objectif.bleu;
    piles[3] = &jeu->objectif.rouge;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < piles[i]->nb; j++) {
            int taille = (int)strlen(piles[i]->animaux[j].nom);
            if (taille > largeurs[i]) {
                largeurs[i] = taille;
            }
        }
    }

    int h1, h2, hMax;
    
    if (piles[0]->nb > piles[1]->nb) h1 = piles[0]->nb;
    else h1 = piles[1]->nb;

    if (piles[2]->nb > piles[3]->nb) h2 = piles[2]->nb;
    else h2 = piles[3]->nb;

    if (h1 > h2) hMax = h1;
    else hMax = h2;

    for (int lig = hMax - 1; lig >= -2; lig--) {
        for (int col = 0; col < 4; col++) {
            const char* mot = "";
            
            if (lig == -1) {
                mot = "----";
            } else if (lig == -2) {
                if (col % 2 == 0) mot = "BLEU";
                else mot = "ROUGE";
            } else {
                if (lig < piles[col]->nb) {
                    mot = piles[col]->animaux[lig].nom;
                }
            }

            printf("%s", mot);

            int n = (int)strlen(mot);
            int nbEspaces = (largeurs[col] - n) + 2;
            for (int e = 0; e < nbEspaces; e++) {
                printf(" ");
            }

            if (col == 1) {
                if (lig == -1) {
                    printf("==>  "); 
                } else {
                    printf("     ");
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

int executerSequence(const Jeu* jeu, const char* sequence, Situation* resultat, char* ordreEchoue) {
    copierSituation(&jeu->actuelle, resultat);
    
    int taille = strlen(sequence);
    
    for (int i = 0; i < taille; i += 2) {
        if (i + 1 >= taille) {
            if (ordreEchoue) {
                ordreEchoue[0] = sequence[i];
                ordreEchoue[1] = '\0';
            }
            return 0;
        }
        
        char ordre[3] = {sequence[i], sequence[i+1], '\0'};
        
        if (!ordreExiste(&jeu->cfg, ordre)) {
            if (ordreEchoue) {
                ordreEchoue[0] = ordre[0];
                ordreEchoue[1] = ordre[1];
                ordreEchoue[2] = '\0';
            }
            return 0;
        }
        
        if (strcmp(ordre, "KI") == 0) {
            executerKI(resultat);
        } else if (strcmp(ordre, "LO") == 0) {
            executerLO(resultat);
        } else if (strcmp(ordre, "SO") == 0) {
            executerSO(resultat);
        } else if (strcmp(ordre, "NI") == 0) {
            executerNI(resultat);
        } else if (strcmp(ordre, "MA") == 0) {
            executerMA(resultat);
        }
    }
    
    if (ordreEchoue) ordreEchoue[0] = '\0';
    return 1;
}

void traiterSaisie(Jeu* jeu, const char* saisie, int* finPartie) {
    char nomJoueur[MAX_NOM_JOUEUR];
    char sequence[100];
    
    if (sscanf(saisie, "%s %s", nomJoueur, sequence) != 2) {
        printf("Saisie invalide\n\n");
        return;
    }
    
    int idxJoueur = trouverJoueur(&jeu->joueurs, nomJoueur);
    if (idxJoueur == -1) {
        printf("Joueur inconnu\n\n");
        return;
    }
    
    if (!jeu->joueurs.joueurs[idxJoueur].peutJouer) {
        printf("%s ne peut pas jouer\n\n", nomJoueur);
        return;
    }
    
    Situation resultat;
    char ordreEchoue[3] = {'\0'};
    if (!executerSequence(jeu, sequence, &resultat, ordreEchoue)) {
        if (ordreEchoue[1] != '\0') {
            printf("L'ordre %s n'existe pas\n\n", ordreEchoue);
        } else {
            printf("L'ordre %c n'existe pas\n\n", ordreEchoue[0]);
        }
        return;
    }
    
    if (situationsEgales(&resultat, &jeu->objectif)) {
        printf("%s gagne un point\n\n", nomJoueur);
        jeu->joueurs.joueurs[idxJoueur].score++;
        copierSituation(&jeu->objectif, &jeu->actuelle);
        if (jeu->indexProchaineCarte > 0) {
            jeu->cartes[jeu->indexProchaineCarte - 1].utilisee = 1;
        }
        if (compterCartesUtilisees(jeu) >= jeu->nbCartes) {
            *finPartie = 1;
            return;
        }

        if (tirerCarte(jeu)) {
            reinitTour(&jeu->joueurs);
            afficherSituationJeu(jeu);
        } else {
            *finPartie = 1;
        }
    } else {
        printf("La sequence ne conduit pas a la situation attendue -- %s ne peut plus jouer durant ce tour\n\n", nomJoueur);
        
        jeu->joueurs.joueurs[idxJoueur].peutJouer = 0;
        
        if (nbJoueursActifs(&jeu->joueurs) == 1) {
            for (int i = 0; i < jeu->joueurs.nb; i++) {
                if (jeu->joueurs.joueurs[i].peutJouer) {
                    printf("%s gagne un point car lui seul peut encore jouer durant ce tour\n\n", jeu->joueurs.joueurs[i].nom);
                    jeu->joueurs.joueurs[i].score++;
                    break;
                }
            }
            copierSituation(&jeu->objectif, &jeu->actuelle);
            if (jeu->indexProchaineCarte > 0) {
                jeu->cartes[jeu->indexProchaineCarte - 1].utilisee = 1;
            }
            
            if (tirerCarte(jeu)) {
                reinitTour(&jeu->joueurs);
                afficherSituationJeu(jeu);
            } else {
                if (jeu->indexProchaineCarte > 0) {
                    jeu->cartes[jeu->indexProchaineCarte - 1].utilisee = 1;
                }
                if (compterCartesUtilisees(jeu) >= jeu->nbCartes) {
                    *finPartie = 1;
                } else {
                    printf("X  | ERREUR - Plus de cartes disponibles (une err c'est produite).\n\n");
                    *finPartie = 1;
                }
            }
        }
    }
}

void lancerPartie(Jeu* jeu) {
    afficherOrdres(&jeu->cfg);
    printf("\n");

    if (!tirerCarte(jeu)) {
        printf("X  | ERREUR - Aucune carte disponible.\n\n");
        return;
    }

    copierSituation(&jeu->objectif, &jeu->actuelle);
    if (jeu->indexProchaineCarte > 0) {
        jeu->cartes[jeu->indexProchaineCarte - 1].utilisee = 1;
    }

    if (!tirerCarte(jeu)) {
        printf("X  | ERREUR - Pas assez de cartes.\n\n");
        return;
    }

    afficherSituationJeu(jeu);

    int finPartie = 0;
    while (!finPartie) {
        char saisie[200];
        if (fgets(saisie, 200, stdin) != NULL) {
            for (int i = 0; saisie[i] != '\0'; i++) {
                if (saisie[i] == '\n') {
                    saisie[i] = '\0';
                    break;
                }
            }
            traiterSaisie(jeu, saisie, &finPartie);
        }
    }
    
    afficherScores(&jeu->joueurs);
}

void quitterJeu(Jeu* jeu) {
    if (jeu->cartes) {
        free(jeu->cartes);
        jeu->cartes = NULL;
    }
}