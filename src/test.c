#include "animal.h"
#include "podium.h"
#include "situation.h"
#include "config.h"
#include <stdio.h>
#include <assert.h>

void testAnimal() {
    Animal a1, a2;
    initAnimal(&a1, "LION");
    initAnimal(&a2, "LION");
    assert(animauxEgaux(&a1, &a2));
    
    initAnimal(&a2, "OURS");
    assert(!animauxEgaux(&a1, &a2));
    printf("Va | Valide - Test Animal \n\n");
}

void testPodium() {
    Podium p;
    initPodium(&p);
    assert(estVidePodium(&p));
    
    Animal lion, ours;
    initAnimal(&lion, "LION");
    initAnimal(&ours, "OURS");
    
    empilerPodium(&p, &lion);
    assert(!estVidePodium(&p));
    assert(p.nb == 1);
    
    empilerPodium(&p, &ours);
    assert(p.nb == 2);
    
    Animal sommet;
    sommetPodium(&p, &sommet);
    assert(animauxEgaux(&sommet, &ours));
    
    Animal base;
    basePodium(&p, &base);
    assert(animauxEgaux(&base, &lion));
    
    Animal depile;
    depilerPodium(&p, &depile);
    assert(animauxEgaux(&depile, &ours));
    assert(p.nb == 1);
    
    printf("Va | Valide - Test Podium\n\n");
}

void testMonterBase() {
    Podium p;
    initPodium(&p);
    
    Animal lion, ours, elephant;
    initAnimal(&lion, "LION");
    initAnimal(&ours, "OURS");
    initAnimal(&elephant, "ELEPHANT");
    
    empilerPodium(&p, &lion);
    empilerPodium(&p, &ours);
    empilerPodium(&p, &elephant);
    
    monterBasePodium(&p);
    
    Animal sommet;
    sommetPodium(&p, &sommet);
    assert(animauxEgaux(&sommet, &lion));
    
    printf("Va | Valide - Test monterBase\n\n");
}

void testSituation() {
    Situation s;
    initSituation(&s);
    
    Animal lion, ours;
    initAnimal(&lion, "LION");
    initAnimal(&ours, "OURS");
    
    empilerPodium(&s.bleu, &lion);
    empilerPodium(&s.rouge, &ours);
    
    assert(!estVidePodium(&s.bleu));
    assert(!estVidePodium(&s.rouge));
    
    printf("Va | Valide - Test Situation\n\n");
}

void testOrdreKI() {
    Situation s;
    initSituation(&s);
    
    Animal lion, ours;
    initAnimal(&lion, "LION");
    initAnimal(&ours, "OURS");
    
    empilerPodium(&s.bleu, &lion);
    empilerPodium(&s.bleu, &ours);
    
    executerKI(&s);
    
    assert(s.bleu.nb == 1);
    assert(s.rouge.nb == 1);
    
    Animal sommetRouge;
    sommetPodium(&s.rouge, &sommetRouge);
    assert(animauxEgaux(&sommetRouge, &ours));
    
    printf("Va | Valide - Test ordre KI\n\n");
}

void testOrdreSO() {
    Situation s;
    initSituation(&s);
    
    Animal lion, ours;
    initAnimal(&lion, "LION");
    initAnimal(&ours, "OURS");
    
    empilerPodium(&s.bleu, &lion);
    empilerPodium(&s.rouge, &ours);
    
    executerSO(&s);
    
    Animal sommetBleu, sommetRouge;
    sommetPodium(&s.bleu, &sommetBleu);
    sommetPodium(&s.rouge, &sommetRouge);
    
    assert(animauxEgaux(&sommetBleu, &ours));
    assert(animauxEgaux(&sommetRouge, &lion));
    
    printf("Va | Valide - Test ordre SO\n\n");
}

void testConfig() {
    Config cfg;
    
    if (chargerConfig(&cfg)) {
        assert(cfg.nbAnimaux >= 2);
        assert(cfg.nbOrdres >= 3);
        printf("Va | Valide - Test Config\n\n");
    } else {
        printf("X  | ECHEC - Test Config (fichier crazy.cfg manquant ou invalide)\n");
    }
}

int main() {
    printf("\n\n________ TESTS UNITAIRES ________\n\n");
    testAnimal();
    testPodium();
    testMonterBase();
    testSituation();
    testOrdreKI();
    testOrdreSO();
    testConfig();
    printf("\n________ TOUS LES TESTS PASSES AVEC SUCCESS ________\n\n");
    return 0;
}