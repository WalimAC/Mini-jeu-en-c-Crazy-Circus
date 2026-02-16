#include "situation.h"
#include <stdio.h>

void initSituation(Situation* s) {
    initPodium(&s->bleu);
    initPodium(&s->rouge);
}

void copierSituation(const Situation* s1, Situation* s2) {
    copierPodium(&s1->bleu, &s2->bleu);
    copierPodium(&s1->rouge, &s2->rouge);
}

int situationsEgales(const Situation* s1, const Situation* s2) {
    return podiumsEgaux(&s1->bleu, &s2->bleu) && 
           podiumsEgaux(&s1->rouge, &s2->rouge);
}

void afficheSituation(const Situation* s) {
    affichePodium(&s->bleu);
    printf("\n");
    printf("---- ----\n");
    printf("BLEU ROUGE");
}

void executerKI(Situation* s) {
    if (!estVidePodium(&s->bleu)) {
        Animal a;
        depilerPodium(&s->bleu, &a);
        empilerPodium(&s->rouge, &a);
    }
}

void executerLO(Situation* s) {
    if (!estVidePodium(&s->rouge)) {
        Animal a;
        depilerPodium(&s->rouge, &a);
        empilerPodium(&s->bleu, &a);
    }
}

void executerSO(Situation* s) {
    if (!estVidePodium(&s->bleu) && !estVidePodium(&s->rouge)) {
        Animal aBleu, aRouge;
        depilerPodium(&s->bleu, &aBleu);
        depilerPodium(&s->rouge, &aRouge);
        empilerPodium(&s->bleu, &aRouge);
        empilerPodium(&s->rouge, &aBleu);
    }
}

void executerNI(Situation* s) {
    if (!estVidePodium(&s->bleu)) {
        monterBasePodium(&s->bleu);
    }
}

void executerMA(Situation* s) {
    if (!estVidePodium(&s->rouge)) {
        monterBasePodium(&s->rouge);
    }
}