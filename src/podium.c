#include "podium.h"
#include <stdio.h>
#include <assert.h>

void initPodium(Podium* p) {
    p->nb = 0;
}

int estVidePodium(const Podium* p) {
    return p->nb == 0;
}

void empilerPodium(Podium* p, const Animal* a) {
    assert(p->nb < MAX_ANIMAUX_PODIUM);
    p->animaux[p->nb] = *a;
    p->nb++;
}

void depilerPodium(Podium* p, Animal* a) {
    assert(!estVidePodium(p));
    p->nb--;
    *a = p->animaux[p->nb];
}

void sommetPodium(const Podium* p, Animal* a) {
    assert(!estVidePodium(p));
    *a = p->animaux[p->nb - 1];
}

void basePodium(const Podium* p, Animal* a) {
    assert(!estVidePodium(p));
    *a = p->animaux[0];
}

void monterBasePodium(Podium* p) {
    assert(!estVidePodium(p));
    if (p->nb > 1) {
        Animal base = p->animaux[0];
        for (int i = 0; i < p->nb - 1; i++) {
            p->animaux[i] = p->animaux[i + 1];
        }
        p->animaux[p->nb - 1] = base;
    }
}

void copierPodium(const Podium* p1, Podium* p2) {
    p2->nb = p1->nb;
    for (int i = 0; i < p1->nb; i++) {
        p2->animaux[i] = p1->animaux[i];
    }
}

void affichePodium(const Podium* p) {
    for (int i = p->nb - 1; i >= 0; i--) {
        afficheAnimal(&p->animaux[i]);
        if (i > 0) printf(" ");
    }
}

int podiumsEgaux(const Podium* p1, const Podium* p2) {
    if (p1->nb != p2->nb) return 0;
    for (int i = 0; i < p1->nb; i++) {
        if (!animauxEgaux(&p1->animaux[i], &p2->animaux[i])) {
            return 0;
        }
    }
    return 1;
}