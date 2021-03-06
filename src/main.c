#include "../headers/parseur.h"
#include "../headers/trainingSet.h"
#include "../headers/testSet.h"
#include "../headers/multinomial.h"
#include "../headers/Bernouilli.h"
#include <stdlib.h>
#include <stdio.h>
#include "math.h"

void initL(tabDoc * L);
void liberer(double ***PC, double **Pi);
double testComparaisonMultinomial(tabDoc * test, double **PC, double *Pi);
double testComparaisonBernouilli(tabDoc * test, double **PC, double *Pi, double a);
void init(double ***PC,double **Pi,int maxIndice);

int main(){


    // ======== Question 1 : Parsing des data ========
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

    double **PC;
    double *Pi;
    double **PCBernouilli;
    double *PiBernouilli;
    init(&PC,&Pi,L->maxIndice);
    init(&PCBernouilli,&PiBernouilli,L->maxIndice);

    // ======== Question 3 ========

    // ======== Question 3a : estimation des paramètres du modèle de Bernoulli ========

    printf("\n\nQuestion 3b :\n");
    printf("Estimation des paramètres du modèle de Bernouilli : ");
    bernouilliApprentissage(training,&PiBernouilli,&PCBernouilli);
    printf("Successful \n");

    // ======== Question 3b : estimation des paramètres du modèle de Multinomial ========



    printf("\n\nQuestion 3b :\n");
    printf("Estimation des paramètres du modèle Multinomial : ");
    multinomialApprentissage(training,&PC,&Pi);
    printf("Successful \n");



    // ======== Question 4 : ========

    printf("\n\nQuestion 4 : \n");
    testComparaisonMultinomial(test,PC,Pi);
    testComparaisonBernouilli(test, PCBernouilli, PiBernouilli,0.01);




    // ======== Question 5 : Multinomial : ========

    printf("\n\nQuestion 5 en cours pour le modèle Multinomial : \n \n");

    double res = 0;
    double var = 0;
    int nbr = 20;
    double tmp;

    for(int i = 0 ; i < nbr; i++){

        printf("Echantillon %i en cours de test : \n\n", i+1);
        initL(L);
        test = createTestSet(L);
        training = createTrainingSet(L);
        multinomialApprentissage(training,&PC,&Pi);
        tmp = testComparaisonMultinomial(test,PC,Pi);
        res = res + tmp;
        var = var + tmp * tmp;

    }
    res = res/nbr;
    var = sqrt(var/nbr - res*res);
    printf("\nNous obtenons donc un pourcentage de compatibilité avec le modèle multinomial en ayant effectué %i tests de : %lf %%\n\n",nbr, res * 100);
    printf("L'écart type de cette série est de : %lf \n\n", var);

    // ======== Question 5 : Bernouilli : ========

    printf("Tester le modèle de Bernouilli 20 fois est très long, si vous désirez le faire cela est possible, "
                   "en revanche,  tester la totalité de l'échantillon test prend 20minutes, celà prendrait donc 7h"
                   " d'effectuer le test complet \n\n");
    printf("Entrez le pourcentage de l'échantillon que vous souhaitez tester : ");
    double rate = 150;
    while(rate > 100 || rate < 0){
        scanf("%lf", &rate);
        if(rate > 100 || rate < 0){
            printf("\nLa valeur que vous devez rentrer doit être comprise entre 0 et 100 : ");
        }
    }
    printf("Tapez le nombre de fois que vous souhaitez effectuer le test ");
    nbr = 30; 
    while(nbr > 20 || nbr < 0) {
        scanf("%i", &nbr);
        if(nbr > 20 || nbr < 0){
            printf("\nLa valeur que vous devez rentrer doit être comprise entre 0 et 20 : ");
        }
    }
    res = 0;
    var = 0;
    for(int i = 0 ; i < nbr; i++){
        printf("Echantillon %i en cours de test : \n\n", i+1);
        initL(L);
        test = createTestSet(L);
        training = createTrainingSet(L);
        bernouilliApprentissage(training,&PiBernouilli,&PCBernouilli);
        tmp = testComparaisonBernouilli(test, PCBernouilli, PiBernouilli,rate/100);
        res = res + tmp;
        var = var + tmp * tmp;
    }
    res = res/nbr;
    var = sqrt(var/nbr - res*res);
    printf("\nNous obtenons donc un pourcentage de compatibilité avec le modèle de Bernouilli en ayant effectué %i tests de : %lf %%\n",nbr, res * 100);
    printf("L'écart type de cette série est de : %lf \n\n", var);


    //Liberation
    liberer(&PC,&Pi);
    liberer(&PCBernouilli,&PiBernouilli);
    supprimerDoc(L);

    printf("\n\nSuppression ok\n");


    return 0;

}

void initL(tabDoc * L){
    for(int i = 0; i < L->taille; i++){
        L->tab[i]->visite = false;
    }
}

double testComparaisonMultinomial(tabDoc * test, double **PC, double *Pi){
    int compt = 0;
    double res;
    for(int i = 0; i < test->taille; i++){
        int a = multinomialTest(PC,Pi,test->tab[i]);
        if (a == test->tab[i]->categorie){
            compt++;
        }
    }
    res = (double)compt/test->taille;
    printf("Taux de bonne classification pour l'échantillon test avec le modèle Multinomial : %lf %% \n", res*100);

    return res;
}


double testComparaisonBernouilli(tabDoc * test, double **PC, double *Pi,double rate){
    int compt = 0;
    double res;
    printf("Wait ! \n");
    for(int i = 0; i < test->taille*rate; i++){
        int a = bernouilliTest(test,Pi,PC,test->tab[i]);
        if (a == test->tab[i]->categorie){
            compt++;
        }
    }
    res = (double)compt/(test->taille*rate);
    printf("Taux de bonne classification pour l'échantillon test avec le modèle de Bernouilli : %lf %% (seulement %lf %% de l'échantillon test utilisé) \n", res*100, rate*100);

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
