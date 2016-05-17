//
// Created by yaya on 16/05/16.
//
#include <stddef.h>
#include <math.h>
#include "Bernouilli.h"
#include "parseur.h"

//Calcule le nombre de documents de la categorie "categorie"
int nbDocCat(tabDoc *L, int categorie){
    int i = 0;
    for(int j = 0; j < L -> taille; j++ ){
        if ( L->tab[j]->categorie == categorie){
            i++;
        }
    }
    return i;
}

//Nous dit si le document doc contient le mot "mot"
bool contient(Document *doc, int mot){
    bool retour = false;
    Word *cour = doc ->listWord;
    while(cour  != NULL  ){
        if(cour ->value == mot){
            retour = true;
        }
        cour = cour ->suiv;
    }
    return retour;
}

//Calcule le nombre de documents de categorie k contenant le mot i
int nbDocMots(tabDoc *L, int categorie, int mot){
    int i = 0;
    Word *cour;
    bool present;
    for (int k = 0 ; k < L -> taille; k++){
        if ( (L->tab)[k] ->categorie == categorie ){
            present = contient((L->tab)[k] ,mot);
            if (present){
                i++;
            }
        }
    }

    return i;
}

//Faire appel a cette fonction avant bernouilliTest
void bernouilliApprentissage(tabDoc* L, double *Pi, double **PC){
    //Initialisation
    int V;
    if ( L == NULL){
       V = 0;
    }else {
        V = L->maxIndice;
    }
    int df[29][V];// = {0};
    int N[29] = {0};
    int m = 52500;

    // On va d'abord calculer le tableau Pi
    for (int k = 1; k < 30; k++ ){
        N[k-1] = nbDocCat(L,k);
        Pi[k-1] = N[k-1]/m;
        for (int i = 1; i < V + 1; i++){
            df[k][i]  = nbDocMots(L,k,i);
        }
    }

    //On calcule le tableau PC
    for (int k = 0; k < 28; k++){
        for(int i = 0; i < V; i++){
            PC[k][i] = (df[k][i] + 1) / (N[k] + 2);
        }
    }
}

int bernouilliTest(tabDoc *L, double *Pi, double **PC, Document *d){
    int retour = 0;
    //initialisation
    double PiF[29] = {0};
    int V = L ->maxIndice;
    int tab[V];
    bool present;
    for ( int i = 1; i < V + 1; i++){
        present = contient(d,i);
        if (present) {
            tab[i - 1] = 1;
        }else{
            tab[i - 1] = 0;
        }
    }

    double max = 0;
    for (int k = 0; k < 29; k ++){
        PiF[k] = log(Pi[k]);
        for ( int i = 0; i < V; i++){
            if(tab[i] == 1){
                PiF[k] = PiF[k] + log(PC[k][i]);
            }else{
                PiF[k] = PiF[k] + log(1 - PC[k][i]);
            }
        }
        if (max < PiF[k]){
            retour = k;
        }
    }

    return retour;
}
