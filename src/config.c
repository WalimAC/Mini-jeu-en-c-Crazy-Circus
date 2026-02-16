#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#pragma warning (disable : 4996)

const char* const FILE_NAME = "./src/crazy.cfg";

int chargerConfig(Config* cfg) {
    
    FILE* f = fopen(FILE_NAME, "r");

    if (f == NULL) {
        printf("X  | ERREUR - Fichier non accessible\n");
        return 0;
    }

    cfg->nbAnimaux = 0;
    cfg->nbOrdres = 0;

    enum { BUFFER_SIZE = 10 };
    char buffer[BUFFER_SIZE];

    for (int numLigne = 0; numLigne < 2; numLigne++) {
        
        char* line = (char*)calloc(1, 1);
        char* s = fgets(buffer, BUFFER_SIZE, f);
        while (s != NULL) {
            size_t taille = strlen(buffer);
            assert(taille != 0);
            if (buffer[taille - 1] == '\n') {
                buffer[taille - 1] = '\0';
                if (taille > 1) {
                    line = (char*)realloc(line, strlen(line) + taille);
                    strcat(line, buffer);
                }
                break; 
            }
            else {
                line = (char*)realloc(line, strlen(line) + taille + 1);
                strcat(line, buffer);
            }
            s = fgets(buffer, BUFFER_SIZE, f);
        }

        int offset = 0;
        int caracteresLus = 0;
        char mot[MAX_NOM_ANIMAL];

        while (sscanf(line + offset, "%s%n", mot, &caracteresLus) == 1) {
            if (numLigne == 0) { 
                if (cfg->nbAnimaux < MAX_ANIMAUX) {
                    initAnimal(&cfg->animaux[cfg->nbAnimaux], mot);
                    cfg->nbAnimaux++;
                }
            } else { 
                if (cfg->nbOrdres < MAX_ORDRES) {
                    if (strcmp(mot, "KI") == 0 || strcmp(mot, "LO") == 0 ||
                        strcmp(mot, "SO") == 0 || strcmp(mot, "NI") == 0 ||
                        strcmp(mot, "MA") == 0) {
                        strcpy(cfg->ordres[cfg->nbOrdres], mot);
                        cfg->nbOrdres++;
                    }
                }
            }
            offset += caracteresLus;
        }
        free(line); 
    }

    fclose(f);

    if (cfg->nbAnimaux < 2) {
        printf("X  | ERREUR - Il faut au moins 2 animaux\n");
        return 0;
    }
    if (cfg->nbOrdres < 3) {
        printf("X  | ERREUR - Il faut au moins 3 ordres\n");
        return 0;
    }

    return 1;
}

void afficherOrdres(const Config* cfg) {
    for (int i = 0; i < cfg->nbOrdres; i++) {
        if (i > 0) printf(" | ");
        
        if (strcmp(cfg->ordres[i], "KI") == 0) printf("KI (B -> R)");
        else if (strcmp(cfg->ordres[i], "LO") == 0) printf("LO (B <- R)");
        else if (strcmp(cfg->ordres[i], "SO") == 0) printf("SO (B <-> R)");
        else if (strcmp(cfg->ordres[i], "NI") == 0) printf("NI (B ^)");
        else if (strcmp(cfg->ordres[i], "MA") == 0) printf("MA (R ^)");
    }
    printf("\n");
}

int ordreExiste(const Config* cfg, const char* ordre) {
    for (int i = 0; i < cfg->nbOrdres; i++) {
        if (strcmp(cfg->ordres[i], ordre) == 0) {
            return 1;
        }
    }
    return 0;
}