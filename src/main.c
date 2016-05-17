#include "../headers/parseur.h"
#include "../headers/trainingSet.h"
#include "../headers/testSet.h"
#include "../headers/multinomial.h"
#include <stdio.h>

int main(){

    // ======== Question 1 : Parsing des data ========
    //tabDoc * L = getInfos("test.txt",8);
    tabDoc * L = getInfos("./tests/BaseReuters-29", 70703);
    printf("Creation oK\n");
    //afficherAll(L);

    afficherQ1(L);

    // ======== Question 2 : Découpage de l'ensemble de données ========
    tabDoc* test = createTestSet(L);
    //afficherAll(test);

    tabDoc* training = createTrainingSet(L);

    //afficherAll(training);


    // ======== Question 3a : estimation des paramètres du modèle de Bernoulli ========


    // ======== Question 3b : estimation des paramètres du modèle de Multinomial ========

    double **PC;
    double *Pi;
    multinomialApprentissage(test,&PC,&Pi);
    int compt = 0;
    double res;
    for(int i = 0; i < 52500; i++){
        int a = multinomialTest(PC,Pi,L->tab[3]);
        if (a == training->tab[i]->categorie){
            compt++;
        }
    }
    res = compt/52500;
    printf("Pourcentage OK : %lf \n", res);


    // ======== Question 4 : ========

    // ======== Question 5 : ========

    //supprimerDoc(L);
    printf("Suppression ok\n");

    return 0;

}