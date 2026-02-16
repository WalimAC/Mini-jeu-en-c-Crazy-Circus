#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    unsigned int seed = (unsigned int)time(NULL);
    srand(seed); 

    Jeu jeu;
    if (!initJeu(&jeu, argv + 1, argc - 1)) {
        return 1;
    }
    
    lancerPartie(&jeu);
    quitterJeu(&jeu);
    
    return 0;
}