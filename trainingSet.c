//
// Created by Kwan Voong on 16/05/2016.
//

#include <stdlib.h>
#include "trainingSet.h"

//ON APPELLE CETTE FONCTION APRES AVOIR CRÉER NOTRE FONCTION qui crée l'ensemble test


tabDoc* createTrainingSet(tabDoc* L) {
    int i = 0; //indice du training
    int j = 0; // indice du grand tab

    tabDoc* training = malloc(sizeof(tabDoc));

    training->tab = malloc(5 * sizeof(Document*));

    while (i < 5) {

        if (!(L->tab[j]->visite)) {
            training->tab[i] = L->tab[j];
            i++;
        }

        j++; // on avance dans le grand tableau de données de départ
    }

    return training;
}


void supprimerTrainingSet(Document* training) {
    for (int i = 0 ; i < 52500 ; i ++){
        supprimerMot(&training[i]);
    }
}