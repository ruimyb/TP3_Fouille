//
// Created by Kwan Voong on 16/05/2016.
//

#include <stdio.h>
#include <stdlib.h>
#include "trainingSet.h"
#include "parseur.h"

//ON APPELLE CETTE FONCTION APRES AVOIR CRÉER NOTRE FONCTION qui crée l'ensemble test


tabDoc* createTrainingSet(tabDoc* L) {
    int i = 0; //indice du training
    int j = 0; // indice du grand tab

    tabDoc* training = malloc(sizeof(tabDoc));

    training->tab = malloc(52500 * sizeof(Document*));
    training->taille = 52500;
    training->maxIndice = 0;

    printf("début du remplissage de l'ensemble entrainement\n");

    while (i < 52500) {

        if (!(L->tab[j]->visite)) {
            training->tab[i] = L->tab[j];
            i++;
        }

        j++; // on avance dans le grand tableau de données de départ
    }

    return training;
}
