//
// Created by Ruimy Benjamin Mac on 14/05/2016.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parseur.h"



listDoc * getInfos(char * FileName){

    FILE* myFile = NULL;
    myFile = fopen(FileName, "r");
    listDoc * L = malloc(sizeof(listDoc));
    L->maxIndice = -1;
    Document * d = malloc(sizeof(Document));
    d->suiv = NULL;
    d->categorie = -1;
    Word * w = malloc(sizeof(Word));
    if (myFile != NULL)
    {
        //On peut lire et écrire dans le fichier

        printf("plop");


        while(1){
            printf("plop2");

            fseek(myFile, -1,SEEK_CUR);
            fscanf(myFile,"%i", &(d->categorie));
            char a = getchar();
            while(a != '\n'){
                int value;
                int nbrAppearance;
                fscanf(myFile,"%i:%i",&value,&nbrAppearance);
                if(value > L->maxIndice){
                    L->maxIndice = value;
                }
                ajouterMot(d,value,nbrAppearance);
            }
            ajouterDoc(L,d->categorie,d->listWord);
        }
        printf("Sortie de boucle");
        fclose(myFile);
        //fin = getchar();
    }
    else
    {
        printf("Impossible d'ouvrir le fichier %s", FileName);
    }
    return L;
}


void ajouterMot(Document * d, int valeur, int nbr){
    Word  * mot = malloc(sizeof(Word));
    mot->value = valeur;
    mot->nbrAppearance = nbr;
    mot->suiv = d->listWord;
    d->listWord = mot;
    //insertion en tête
}

void ajouterDoc(listDoc * L, int categorie, Word * listWord){
    Document * doc = malloc(sizeof(Document));
    doc->categorie = categorie;
    doc->listWord = listWord;
    doc->suiv = L->doc;
    L->doc = doc;
    //insertion en tête
}

void afficherAll(listDoc * L){
    int compt = 1;
    Document * courant = L->doc;
    printf("La taille du vocabulaire est : %i \n", L->maxIndice);
    while(L->doc != NULL){
        printf("Affichage du document %i dont la catégorie est : %i \n", compt, courant->categorie);
        compt++;
        afficherDoc(courant);
        courant = courant->suiv;
    }
}
void afficherDoc(Document * D){
    Word * courant = D->listWord;
    while(courant != NULL){
        afficherMot(courant);
        printf(" ");
        courant = courant->suiv;
    }
};
void afficherMot(Word * w){
    printf("%i:%i", w->value,w->nbrAppearance);
}



