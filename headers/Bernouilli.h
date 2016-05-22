//
// Created by yaya on 16/05/16.
//

#ifndef TP3_FOUILLE_BERNOUILLI_H
#define TP3_FOUILLE_BERNOUILLI_H

#include "parseur.h"

void bernouilliApprentissage(tabDoc* entrainement, double **Pi, double ***PC);

int bernouilliTest(tabDoc *L, double *Pi, double **PC, Document *d);


#endif //TP3_FOUILLE_BERNOUILLI_H
