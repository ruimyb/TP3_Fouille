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

//Création d'un tableau qui contient tous les documents de classe k
TabCatDoc *tabK(tabDoc *L, int k){
    TabCatDoc *retour = malloc(sizeof(tabDoc));
    retour ->taille = nbDocCat(L,k);
    retour ->tab = malloc((retour->taille) * sizeof(Document*));
    int compt = 0;
    for (int i = 0; i < L->taille; i++ ){
        if ( (L->tab[i])->categorie == k){
            retour->tab[compt] = L->tab[i];
            compt++;
        }
    }
    return retour;
}

//remplissage du tableau X
void remplirX(int *X, TabCatDoc *L){
    Word *Cour;
    for (int i = 0;i < L->taille ;i++){
        Cour = L->tab[i]->listWord;
        while(Cour != NULL){
            X[Cour->value] = X[Cour->value] + 1;
            Cour = Cour->suiv;
        }
    }
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
       int N[29] = {0};
    int m = 52500;
    for(int i = 0; i < 29; i++) {
        for(int j = 0; j< V;j++) {

            df[i][j] = 0;

        }
        N[i] =nbDocCat(L,i);
        //printf("N[%i] = %i\n",i,N[i]);
        (*Pi)[i] =(double) N[i]/(double)m;
        //printf("Pi[%i] = %f\n",i,(*Pi)[i]);
    }
    //Création du tableau X de taille V qui stocke le nombre de doc contenant chaque mot
    int X[V];
    for (int k = 1; k < 30; k++ ){
        for (int j = 0; j < V ; ++j) {
            X[j] = 0;
        }
        TabCatDoc *K = tabK(L,k);
        remplirX(X,K);
        for(int i = 0; i < V; i++){
            df[k-1][i] = X[i];
        }
        free(K);
    }
    double a;
    for (int j = 0; j < 29; ++j) {

        for ( int i = 0 ; i < V; i++) {
            a = (double)(df[j][i] + 1) / (double)(N[j] + 2);
            (*PC)[j][i] = a;
            //printf(" PC[%i][%i] = %f\n",j,i,(*PC)[j][i]);
        }
        free(df[j]);
    }
    free(df);
    printf("free total OK\n");
}

int bernouilliTest(tabDoc *L, double *Pi, double **PC, Document *d){
    int retour = 1;
    //initialisation
    double PiF[29] = {0};
    int V = L ->maxIndice;
    int tab[V];

    for (int i = 0; i < V ; ++i) {
        tab[V] = 0;
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
        //printf("Pi[%i] = %f\n",k,Pi[k]);
        //printf("log(Pi[%i]) = %f\n",k,log(Pi[k]));
        for ( int i = 0; i < V; i++){
            if(tab[i] == 1){
                PiF[k] = PiF[k] + log(PC[k][i]);
                printf("On est dans le cas 1, PC[%i][%i] = %f\n",k,i,PC[k][i]);
               //printf("PiF[%i] = %f\n",k,PiF[k]);
            }else{
                PiF[k] = PiF[k] + log((1 - PC[k][i]));
                //printf("PiF[%i] = %f\n",k,PiF[k]);
                printf("On est dans le cas 0, PC[%i][%i] = %f\n",k,i,PC[k][i]);
            }
        }
        printf("PiF[%i] = %f\n",k,PiF[k]);
    }
    //On cherche l'indice max
    max = PiF[0];
    for (int k = 0; k < 29; k++){
        if (max < PiF[k]){
            retour = k + 1;
            max = PiF[k];
        }
    }
    return retour;
}
