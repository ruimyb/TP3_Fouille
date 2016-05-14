//
// Created by Ruimy Benjamin Mac on 14/05/2016.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parseur.h"



listDoc * getInfos(char * FileName){
    printf("plop1\n");
    FILE* myFile = NULL;
    myFile = fopen(FileName, "r");
    listDoc * L = malloc(sizeof(listDoc));
    L->maxIndice = -1;
    L->doc = NULL;
    Document * d = malloc(sizeof(Document));

    if (myFile != NULL)
    {
        //On peut lire et écrire dans le fichier

        printf("plop2\n");
        int fin = getc(myFile);
        while(fin != EOF){
            d->suiv = NULL;
            d->listWord = NULL;
            d->categorie = -1;
            printf("plop3\n");

            fseek(myFile, -1,SEEK_CUR);
            fscanf(myFile,"%i", &(d->categorie));

            int a = getc(myFile);

            while(a != '\n' && a!= EOF){
                //fseek(myFile, -1,SEEK_CUR);
                int value = 0;
                int nbrAppearance = 0;
                fscanf(myFile,"%i:%i",&value,&nbrAppearance);
                if(value > L->maxIndice){
                    L->maxIndice = value;
                }


                if (a != EOF && a != '\n') {
                    ajouterMot(d, value, nbrAppearance);
                }

                a = getc(myFile);

            }
            ajouterDoc(L,d->categorie,d->listWord);
            fin = getc(myFile);
        }
        fclose(myFile);
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

    //insertion en queue
    Word *dernier = d->listWord;

    if (dernier == NULL) {
        d->listWord=mot;
        mot->suiv = NULL;
    } else {

        while (dernier->suiv != NULL) {
            dernier = dernier->suiv;
        }
        dernier->suiv = mot;
        mot->suiv = NULL;
    }

}

void ajouterDoc(listDoc * L, int categorie, Word * listWord){
    Document * doc = malloc(sizeof(Document));
    doc->categorie = categorie;
    doc->listWord = listWord;

    //insertion en queue
    Document *last = L->doc;

    if (last == NULL) {
        L->doc=doc;
        doc->suiv = NULL;
    } else {

        while (last->suiv != NULL) {
            last = last->suiv;
        }
        last->suiv = doc;
        doc->suiv = NULL;
    }

}

void afficherAll(listDoc * L){
    Document * courant = L->doc;
    printf("La taille du vocabulaire est : %i \n", L->maxIndice);
    while(courant != NULL){
        printf("Affichage du document catégorie %i \n", courant->categorie);
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
    printf("\n");
}
void afficherMot(Word * w){
    printf("%i:%i", w->value,w->nbrAppearance);
}



