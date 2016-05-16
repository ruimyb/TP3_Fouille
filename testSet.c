//
// Created by Kwan Voong on 16/05/2016.
//
#include <stdio.h>
#include <stdlib.h>
#include "testSet.h"
#include "parseur.h"

tabDoc* createTestSet(tabDoc* L) {
    int i = 0; // indice du tableau de l'ensmeble test

    tabDoc* test = malloc(sizeof(tabDoc));

    test->tab = malloc(18203 * sizeof(Document*));
    test->taille = 18203;
    test->maxIndice = 0;

    printf("début du remplissage de l'ensemble test\n");

    srand(time(NULL));

    while (i < 18203) {

        int j = rand() % 70703;

        if (!(L->tab[j]->visite)) {
            L->tab[j]->visite = true;
            test->tab[i] = L->tab[j];
            i++;
        }
    }

    return test;
}
