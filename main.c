#include "parseur.h"
#include "testSet.h"
#include "trainingSet.h"
#include <stdio.h>

int main(){

    // ======== Question 1 : Parsing des data ========
    //tabDoc * L = getInfos("test.txt",8);
    tabDoc * L = getInfos("BaseReuters-29", 70703);
    printf("Creation oK\n");
    //afficherAll(L);
    supprimerDoc(L);
    printf("Suppression ok\n");

    // ======== Question 2 : Découpage de l'ensemble de données ========
    tabDoc* test = createTestSet(L);
    afficherAll(test);

    tabDoc* training = createTrainingSet(L);
    afficherAll(training);

    // ======== Question 3a : estimation des paramètres du modèle de Bernoulli ========


    // ======== Question 3b : estimation des paramètres du modèle de Multinomial ========

    // ======== Question 4 : ========

    // ======== Question 5 : ========

    return 0;

}