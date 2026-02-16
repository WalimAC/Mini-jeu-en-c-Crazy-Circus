#include "joueur.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int initJoueurs(Joueurs* js, char** noms, int nbNoms) {
    if (nbNoms < 2) {
        printf("ERREUR | Il faut au moins 2 joueurs\n");
        return 0;
    }
    
    if (nbNoms > MAX_JOUEURS) {
        printf("ERREUR | Trop de joueurs (max %d)\n", MAX_JOUEURS);
        return 0;
    }
    
    for (int i = 0; i < nbNoms; i++) {
        for (int j = i + 1; j < nbNoms; j++) {
            if (strcmp(noms[i], noms[j]) == 0) {
                printf("ERREUR | Les noms des joueurs doivent etre distincts\n");
                return 0;
            }
        }
    }
    
    js->nb = nbNoms;
    for (int i = 0; i < nbNoms; i++) {
        assert(strlen(noms[i]) < MAX_NOM_JOUEUR);
        strcpy(js->joueurs[i].nom, noms[i]);
        js->joueurs[i].score = 0;
        js->joueurs[i].peutJouer = 1;
    }
    
    return 1;
}

int trouverJoueur(const Joueurs* js, const char* nom) {
    for (int i = 0; i < js->nb; i++) {
        if (strcmp(js->joueurs[i].nom, nom) == 0) {
            return i;
        }
    }
    return -1;
}

void reinitTour(Joueurs* js) {
    for (int i = 0; i < js->nb; i++) {
        js->joueurs[i].peutJouer = 1;
    }
}

int nbJoueursActifs(const Joueurs* js) {
    int nb = 0;
    for (int i = 0; i < js->nb; i++) {
        if (js->joueurs[i].peutJouer) {
            nb++;
        }
    }
    return nb;
}

void afficherScores(const Joueurs* js) {
    Joueur tri[MAX_JOUEURS];
    for (int i = 0; i < js->nb; i++) {
        tri[i] = js->joueurs[i];
    }
    
    for (int i = 0; i < js->nb - 1; i++) {
        for (int j = i + 1; j < js->nb; j++) {
            if (tri[i].score < tri[j].score || (tri[i].score == tri[j].score && strcmp(tri[i].nom, tri[j].nom) > 0)) {
                Joueur tmp = tri[i];
                tri[i] = tri[j];
                tri[j] = tmp;
            }
        }
    }
    
    for (int i = 0; i < js->nb; i++) {
        printf("%s %d\n", tri[i].nom, tri[i].score);
    }
}
