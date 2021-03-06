//
// Created by Ruimy Benjamin Mac on 14/05/2016.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../headers/parseur.h"


tabDoc* getInfos(char * FileName, int taille){
    FILE* myFile = NULL;
    myFile = fopen(FileName, "r");
    tabDoc* L = malloc(sizeof(tabDoc));
    L->maxIndice = -1;
    L -> taille = taille;
    L ->tab = malloc(L -> taille * sizeof(Document*));
    for(int i = 0; i < 29; i++){
        L->tabCat[i] = 0;
    }
    Document * d = malloc(sizeof(Document));
    int j = 0;
    if (myFile != NULL)
    {
        //On peut lire et écrire dans le fichier

        int fin = getc(myFile);
        while(fin != EOF){
            d->listWord = NULL;
            d->queue = NULL;
            d->categorie = -1;

            fseek(myFile, -1,SEEK_CUR);
            fscanf(myFile,"%i", &(d->categorie));
            L->tabCat[d->categorie -1]++;

            int a = getc(myFile);
            int b = getc(myFile);
            d->tailleVocab = 0;
            int value = 0;

            while(b != '\n' && a == ' ' && b!= EOF){
                fseek(myFile, -1,SEEK_CUR);
                int nbrAppearance = 0;
                fscanf(myFile,"%i:%i",&value,&nbrAppearance);
                if(value > d->tailleVocab){
                    d->tailleVocab = value;
                    if(value > L->maxIndice){
                        L->maxIndice = value;
                    }
                }

                if (a != EOF && a != '\n') {
                    ajouterMot(d, value, nbrAppearance);
                }

                a = getc(myFile);
                b = getc(myFile);
            }
            ajouterDoc(L,d->categorie,d->listWord, d->tailleVocab,j);
            fin = getc(myFile);
            j++;
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
    mot -> suiv = NULL;

    //insertion en queue
    Word *dernier = d->listWord;

    if (dernier == NULL) {
        d->listWord=mot;
        d -> queue = mot;
    } else if( dernier == d -> queue){
       d -> queue = mot;
        d -> listWord -> suiv = d -> queue;
    } else {
        d -> queue -> suiv = mot;
        d -> queue = mot;
    }

}

void ajouterDoc(tabDoc * L, int categorie, Word * listWord, int a, int i){
    Document * doc = malloc(sizeof(Document));
    doc->categorie = categorie;
    doc->listWord = listWord;
    doc -> visite = false;
    doc ->tailleVocab = a;
    if ( i < 0 || i >= L -> taille){
        perror("mauvais indice");
    }else {
        L->tab[i] = doc;
    }
}

void afficherQ1(tabDoc *L){
    printf("Réponse à la question 1 : \n");
    printf("La taille du vocabulaire est : %i \n", L->maxIndice);
    for(int i = 0; i < 29; i++){
        printf("Les documents de catégorie %i sont au nombre de : %i \n", i+1,L->tabCat[i]);
    }
}

void afficherAll(tabDoc * L){
    printf("La taille du vocabulaire est : %i \n", L->maxIndice);
    for(int i = 0; i < 29; i++){
        printf("Les documents de catégorie %i sont au nombre de : %i \n", i+1,L->tabCat[i]);
    }
   for( int i = 0 ; i < L-> taille ; i ++){
        printf("Affichage du document catégorie %i \n", L -> tab[i]->categorie);
        afficherDoc((L -> tab[i]));
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

void supprimerMot(Document *d){
    Word * tmp;
    while (d->listWord != d->queue){
        tmp = d->listWord;
        d->listWord = d->listWord->suiv;
        free(tmp);
    }
    free(d->listWord);
}

void supprimerDoc(tabDoc * L){
 for (int i = 0 ; i < L -> taille ; i ++){
     supprimerMot((L->tab[i]));
     free(L->tab[i]);
 }
free(L->tab);

}
