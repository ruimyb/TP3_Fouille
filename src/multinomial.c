//
// Created by Ruimy Benjamin Mac on 16/05/2016.
//

#include "../headers/multinomial.h"
#include "parseur.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void multinomialApprentissage(tabDoc * tabDoc1, double ***PC, double **Pi){
    *PC = (double **) malloc(29 * sizeof(double));
    *Pi = (double *) malloc(29 * sizeof(double));
    int **tf = (int**)malloc(29 * sizeof(int));

    for (int i = 0; i < 29; i++) {
        (*PC)[i] = (double *) malloc(tabDoc1->maxIndice * sizeof(double));
        tf[i] = (int *) malloc(tabDoc1->maxIndice * sizeof(int));
    }


    int D[29] = {0};

    // N[i] = tabCat[i]
    int maxIndex = 0;
    int tailleVocab = 0;
    for(int i = 0; i < 29; i++){

        (*Pi)[i] = (double)tabDoc1->tabCat[i]/tabDoc1->taille;

        for(int j = 0; j < tabDoc1->maxIndice; j++){
            tf[i][j] = 0;
            Word * Courant = tabDoc1->tab[i]->listWord;
            while(Courant != NULL){
                if(Courant->value == j){
                    tf[i][j] = tf[i][j] + 1;
                    if(Courant->value > tailleVocab){
                        tailleVocab = Courant->value;
                    }
                    if(maxIndex < Courant->value){
                        maxIndex = Courant->value;
                    }
                }
                Courant = Courant->suiv;
            }
        }
    }
    tabDoc1->maxIndice = maxIndex;

    for(int i = 0; i < 29; i++){
        for(int j = 0; j < tabDoc1->maxIndice; j++){
            (*PC)[i][j] = (double)(tf[i][j] + 1)/((double)(D[i] + tabDoc1->maxIndice));
        }
        free(tf[i]);
    }

    free(tf);

}



int multinomialTest(double **PC, double *Pi, Document * d){
    double PiF[29] = {0};
    Word * w;

    for(int k = 0; k < 29; k++){
        w = d->listWord;

        PiF[k] = log(Pi[k]);

        while(w != NULL){
            PiF[k] = PiF[k] + (double)w->nbrAppearance * log(PC[k][w->value]);
            w = w->suiv;
        }
        //  printf("%lf", PiF[k]);
    }
    int max = 0;
    for(int i = 0; i < 29; i++){
        if(PiF[i] > PiF[max]){
            max = i;
        }
    }
    return max+1;

}