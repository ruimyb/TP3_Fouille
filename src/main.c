#include "../headers/parseur.h"
#include "../headers/trainingSet.h"
#include "../headers/testSet.h"
#include "../headers/multinomial.h"
#include <stdlib.h>
#include <stdio.h>

void initL(tabDoc * L);
void liberer(double ***PC, double **Pi);
double testComparaison(tabDoc * test, double **PC, double *Pi);
void init(double ***PC,double **Pi,int maxIndice);

int main(){


    // ======== Question 1 : Parsing des data ========
    //tabDoc * L = getInfos("test.txt",8);
    tabDoc * L = getInfos("./tests/BaseReuters-29", 70703);
    printf("Creation oK\n");
    //afficherAll(L);

    afficherQ1(L);

    // ======== Question 2 : Découpage de l'ensemble de données ========
    printf("\n\nQuestion 2 : \n");
    printf("Création de l'échantillon de test : ");
    tabDoc* test = createTestSet(L);
    printf("Successful\n");
    //afficherAll(test);
    printf("Création de l'échantillon d'apprentissage : ");
    tabDoc* training = createTrainingSet(L);
    printf("Successful \n");

    //afficherAll(training);


    // ======== Question 3a : estimation des paramètres du modèle de Bernoulli ========


    // ======== Question 3b : estimation des paramètres du modèle de Multinomial ========

    double **PC;
    double *Pi;
    init(&PC,&Pi,L->maxIndice);

    printf("\n\nQuestion 3 pour l'estimation des paramètres du modèle Multinomial : ");
    multinomialApprentissage(training,&PC,&Pi);
    printf("Successful \n");



    // ======== Question 4 : ========
    printf("\n\nQuestion 4 : ");
    testComparaison(test,PC,Pi);
    // ======== Question 5 : Multinomial : ========

    printf("\n\nQuestion 5 en cours pour le modèle Multinomial : \n \n");

    double res = 0;
    int nbr = 20;
    for(int i = 0 ; i < nbr; i++){
        printf("Echantillon %i en cours de test : \n\n", i+1);
        initL(L);
        test = createTestSet(L);
        training = createTrainingSet(L);
        multinomialApprentissage(training,&PC,&Pi);
        res = res + testComparaison(test,PC,Pi);

    }

    printf("\nNous obtenons donc un pourcentage de compatibilité en ayant effectué %i tests de : %lf \n",nbr, res/nbr);





    //Liberation
    liberer(&PC,&Pi);
    supprimerDoc(L);

    printf("Suppression ok\n");


    return 0;

}

void initL(tabDoc * L){
    for(int i = 0; i < L->taille; i++){
        L->tab[i]->visite = false;
    }
}

double testComparaison(tabDoc * test, double **PC, double *Pi){
    int compt = 0;
    double res;
    for(int i = 0; i < test->taille; i++){
        int a = multinomialTest(PC,Pi,test->tab[i]);
        if (a == test->tab[i]->categorie){
            compt++;
        }
    }
    res = (double)compt/test->taille;
    printf("Taux de bonne classification pour l'échantillon test : %lf \n", res*100);

    return res;
}

void init(double ***PC,double **Pi,int maxIndice){
    *PC = (double **) malloc(29 * sizeof(double*));
    *Pi = malloc(29 * sizeof(double));
    for (int i = 0; i < 29; i++) {
        (*PC)[i] = (double *) malloc(maxIndice * sizeof(double));
    }
}

void liberer(double ***PC, double **Pi){
    for(int i = 0; i < 29; i++){

        free((*PC)[i]);
    }

    free(*PC);
    free(*Pi);
}
