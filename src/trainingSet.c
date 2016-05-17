//
// Created by Kwan Voong on 16/05/2016.
//

#include <stdio.h>
#include <stdlib.h>
#include "../headers/trainingSet.h"

//ON APPELLE CETTE FONCTION APRES AVOIR CRÉER NOTRE FONCTION qui crée l'ensemble test


tabDoc* createTrainingSet(tabDoc* L) {
    int i = 0; //indice du training
    int j = 0; // indice du grand tab

    tabDoc* training = malloc(sizeof(tabDoc));

    training->tab = malloc(52500 * sizeof(Document*));
    training->taille = 52500;
    training->maxIndice = L->maxIndice;
    for(int i = 0; i < 29; i++){
        training->tabCat[i] = 0;
    }

    printf("début du remplissage de l'ensemble entrainement\n");

    while (i < 52500) {

        if (!(L->tab[j]->visite)) {
            training->tab[i] = L->tab[j];
            training->tabCat[training->tab[i]->categorie - 1] = training->tabCat[training->tab[i]->categorie - 1] + 1;
            i++;
        }

        j++; // on avance dans le grand tableau de données de départ
    }

    return training;
}
