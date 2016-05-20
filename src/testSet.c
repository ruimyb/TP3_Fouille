//
// Created by Kwan Voong on 16/05/2016.
//
#include <stdio.h>
#include <stdlib.h>
#include "../headers/testSet.h"


tabDoc* createTestSet(tabDoc* L) {
    int i = 0; // indice du tableau de l'ensmeble test

    tabDoc* test = malloc(sizeof(tabDoc));

    test->tab = malloc(18203 * sizeof(Document*));
    test->taille = 18203;
    test->maxIndice = 0;
    for(int i = 0; i < 29; i++){
        test->tabCat[i] = 0;
    }


    srand(time(NULL));

    while (i < 18203) {

        int j = rand() % 70703;

        if (!(L->tab[j]->visite)) {
            L->tab[j]->visite = true;
            test->tab[i] = L->tab[j];
            if(test->tab[i]->tailleVocab > test->maxIndice){
                test->maxIndice = test->tab[i]->tailleVocab;
            }
            test->tabCat[test->tab[i]->categorie - 1] = test->tabCat[test->tab[i]->categorie - 1] + 1;
            i++;
        }
    }

    return test;
}