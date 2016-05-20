//
// Created by yaya on 16/05/16.
//
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/Bernouilli.h"
#include "../headers/parseur.h"

//On crée une structure pour le parcours des mots
typedef struct TabCatDoc TabCatDoc;
struct TabCatDoc {
    int taille;
    Document ** tab;
};


//Calcule le nombre de documents de catégorie K
int nbDocCat(tabDoc *L, int k){
    int retour = 0;
    for ( int i = 0; i < L->taille;i++){
        if (L->tab[i]->categorie == k){
            retour ++;
        }
    }
    return retour;
}



//Faire appel a cette fonction avant bernouilliTest
void bernouilliApprentissage(tabDoc* L, double **Pi, double ***PC){
    //Initialisation
    int V;
    if ( L == NULL){
       V = 0;
    }else {
        V = L->maxIndice;
    }
    //On crée le tableau df
    int **df = (int**)malloc(29 * sizeof(int*));

    for (int i = 0; i < 29; i++) {
        df[i] = (int *) malloc(V * sizeof(int));
    }

    int m = 52500;
    for(int i = 0; i < 29; i++) {
        for(int j = 0; j< V;j++) {

            df[i][j] = 0;

        }


        (*Pi)[i] =(double) L->tabCat[i]/(double)m;
    }

    Word *Cour;
    for (int k = 0; k < L->taille ; ++k) {
        Cour = L->tab[k]->listWord;
        while(Cour!=NULL){
            df[L->tab[k]->categorie - 1][Cour->value-1]= df[L->tab[k]->categorie - 1][Cour->value-1]+1;
            Cour = Cour->suiv;
        }
    }
    double a;
    for (int j = 0; j < 29; ++j) {

        for ( int i = 0 ; i < V; i++) {
            a = (double)(df[j][i] + 1) / (double)(L->tabCat[j] + 2);
            (*PC)[j][i] = a;

        }
        free(df[j]);
    }
    free(df);
}

int bernouilliTest(tabDoc *L, double *Pi, double **PC, Document *d){
    int retour = 1;
    //initialisation
    double PiF[29] = {0};
    int V = L->maxIndice;
    int tab[V];

    for (int i = 0; i < V ; ++i) {
        tab[i] = 0;
    }
     Word *Cour = d->listWord;
    while(Cour != NULL){
        tab[Cour->value - 1] = 1;
        Cour = Cour->suiv;
    }

    double max = 0;
   //On remplit le tableau PiF
    for (int k = 0; k < 29; k ++){
        PiF[k] = log(Pi[k]);

        for ( int i = 0; i < V; i++){
            if(tab[i] == 1){
                PiF[k] = PiF[k] + log(PC[k][i]);

            }else{
                PiF[k] = PiF[k] + log((1 - PC[k][i]));
            }
        }
    }

    max = PiF[0];
    for (int k = 0; k < 29; k++){
        if (max < PiF[k]){
            retour = k + 1;
            max = PiF[k];
        }
    }

    return retour;
}
