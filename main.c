#include "parseur.h"
#include "Bernouilli.h"




#include "testSet.h"
#include "trainingSet.h"
#include "multinomial.h"
#include <stdio.h>

int main(){

    // ======== Question 1 : Parsing des data ========
    tabDoc * L = getInfos("test.txt",8);
    //tabDoc * L = getInfos("BaseReuters-29", 70703);
    printf("Creation oK\n");
    //afficherAll(L);
    printf("\n");
    //afficherQ1(L);

    // ======== Question 2 : Découpage de l'ensemble de données ========
    tabDoc* test = createTestSet(L);
    //afficherAll(test);

    tabDoc* training = createTrainingSet(L);

    //afficherAll(training);


    // ======== Question 3a : estimation des paramètres du modèle de Bernoulli ========

    //Question Bernouilli
  /* int i;
    i = nbDocCat(L, 59);
    printf("On attend 1 document de categorie 59 et on en a %i \n",i);
    i = nbDocCat(L, 100);
    printf("On attend 0 document de categorie 100 et on en a %i \n",i);
    bool present = false;
    int taille = L -> taille;
    printf("taille = %i \n", taille);
    Document *cour = L ->tab[0];

    for (int k = 0; k < taille; k++){

        cour = L->tab[k];
        present = contient(cour, 1);
        if ( present){
            printf("Le document de categorie %i contient le mot 1\n", cour ->categorie);
        }else{
            printf("Le document de categorie %i ne contient pas le mot 1\n",cour ->categorie);
        }
        present = false;
    }*/

    int j = 0;
    j = nbDocMots(L,49, 1);
    printf("On attend 2 doc de type 49 ayant le mot 1 et on en a %i \n",j);
    j = nbDocMots(L,49, 9);
    printf("On attend un doc de type 49 ayant le mot 1 et on en a %i \n",j);
    supprimerDoc(L);
    printf("Suppression ok\n");

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