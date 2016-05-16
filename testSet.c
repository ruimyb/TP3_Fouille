//
// Created by Kwan Voong on 16/05/2016.
//

#include <stdlib.h>
#include "testSet.h"

tabDoc* createTestSet(tabDoc* L) {
    int i = 0; // indice du tableau de l'ensmeble test

    tabDoc* test = malloc(sizeof(tabDoc));

    test->tab = malloc(3 * sizeof(Document*));

    while (i < 3) {

        srand(time(NULL));

        int j = rand() % 8;

        if (!(L->tab[j]->visite)) {
            L->tab[j]->visite = true;
            test->tab[i] = L->tab[j];
            i++;
        }
    }

    return test;
}
