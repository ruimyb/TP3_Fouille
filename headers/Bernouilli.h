//
// Created by yaya on 16/05/16.
//

#ifndef TP3_FOUILLE_BERNOUILLI_H
#define TP3_FOUILLE_BERNOUILLI_H

#include "parseur.h"

void bernouilliApprentissage(tabDoc* entrainement, double **Pi, double ***PC);

int bernouilliTest(tabDoc *L, double *Pi, double **PC, Document *d);


//Nous dit si le document doc contient le mot "mot"
bool contient(Document *doc, int mot);

//Calcule le nombre de documents de categorie k contenant le mot i
int nbDocMots(tabDoc *L, int categorie, int mot);



#endif //TP3_FOUILLE_BERNOUILLI_H
