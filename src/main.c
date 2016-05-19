#include "../headers/parseur.h"
#include "../headers/trainingSet.h"
#include "../headers/testSet.h"
#include "../headers/Bernouilli.h"
#include "../headers/multinomial.h"
#include <stdlib.h>
#include <stdio.h>

void initL(tabDoc * L);
void liberer(double ***PC, double **Pi);
int testComparaison(tabDoc * test, double **PC, double *Pi);
void init(double ***PC,double **Pi,int maxIndice);

int main(){


    // ======== Question 1 : Parsing des data ========
    //tabDoc * L = getInfos("test.txt",8);
    tabDoc * L = getInfos("./tests/BaseReuters-29", 70703);
    printf("Creation oK\n");
    //afficherAll(L);

    //afficherQ1(L);

    // ======== Question 2 : Découpage de l'ensemble de données ========
    tabDoc* test = createTestSet(L);
    //afficherAll(test);

    tabDoc* training = createTrainingSet(L);

    //afficherAll(training);


    // ======== Question 3a : estimation des paramètres du modèle de Bernoulli ========

    //ON initialise
    double **PC;
    double *Pi;
    printf("MaxIndice vaut %i", L -> maxIndice);
    init(&PC,&Pi,L->maxIndice);
    printf("Initialisation des tableaux Pi et PC OK\n");
    //On applique Bernouilli Apprentissage
    printf("On applique Bernouilli Apprentissage\n");
    bernouilliApprentissage(training,&Pi,&PC);
    printf("Bernouilli Apprentissage sur la base d'entrainement OK\n");

    int compt = 0;
    double res;
    int a =0;
    for (int j = 0; j < test ->taille; ++j) {
       a =  bernouilliTest(test,Pi,PC,test ->tab[j]);
        if (a == test->tab[j]->categorie){
            compt++;
        }
    }
    printf("Bernouilli test sur la base de test OK\n");
    res = (double)compt/test->taille;
    printf("Pourcentage de compatibilité sur l'échantillon test : %lf \n", res*100);

    liberer(&PC,&Pi);

    // ======== Question 3b : estimation des paramètres du modèle de Multinomial ========

    /*double **PC;
    double *Pi;
    printf("Test de la taille du voc du doc 1 %i \n", test->tab[0]->tailleVocab);



    init(&PC,&Pi,L->maxIndice);

    multinomialApprentissage(training,&PC,&Pi);
    printf("La taille de l'échantillon test est : %i \n" ,test->maxIndice);
    printf("La taille de l'échantillon training est : %i \n" ,training->maxIndice);
    testComparaison(test,PC,Pi);
    liberer(&PC,&Pi);*/


    // ======== Question 4 : ========

    // ======== Question 5 : ========





    //Liberation
    supprimerDoc(training);
    supprimerDoc(test);
    supprimerDoc(L);
    printf("Suppression ok\n");


    return 0;

}

void initL(tabDoc * L){
    for(int i = 0; i < L->taille; i++){
        L->tab[i]->visite = false;
    }
}

int testComparaison(tabDoc * test, double **PC, double *Pi){
    int compt = 0;
    double res;
    for(int i = 0; i < test->taille; i++){
        int a = multinomialTest(PC,Pi,test->tab[i]);
        if (a == test->tab[i]->categorie){
            compt++;
        }
    }
    res = (double)compt/test->taille;
    printf("Pourcentage de compatibilité sur l'échantillon test : %lf \n", res*100);
}

void init(double ***PC,double **Pi,int maxIndice){
    *PC = (double **) malloc(29 * sizeof(double*));
    *Pi = (double *) malloc(29 * sizeof(double));
    for (int i = 0; i < 29; i++) {
        (*PC)[i] = (double *) calloc(0,maxIndice * sizeof(double));
    }
}

void liberer(double ***PC, double **Pi){
    for(int i = 0; i < 29; i++){

        free((*PC)[i]);
    }

    free(*PC);
    free(*Pi);
}
