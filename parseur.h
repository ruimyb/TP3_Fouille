//
// Created by Ruimy Benjamin Mac on 14/05/2016.
//

#ifndef TP3_FOUILLE_PARSEUR_H
#define TP3_FOUILLE_PARSEUR_H


#include <jmorecfg.h>

typedef struct Word Word;
struct Word {
    int value;
    int nbrAppearance;
    Word * suiv;
};

typedef struct Document Document;
struct Document{
    int categorie;
    Word *listWord;
    Word *queue;
    boolean visite;
};

typedef struct {
    int taille;
    int maxIndice;
    Document* tab;
}tabDoc;

void ajouterMot(Document * d, int valeur, int nbr);
void ajouterDoc(tabDoc * L, int categorie, Word * listWord, int i);
tabDoc * getInfos(char * FileName, int i);
void afficherAll(tabDoc * L);
void afficherDoc(Document * D);
void afficherMot(Word * w);
void supprimerMot(Document *d);
void supprimerDoc(tabDoc *d);


#endif //TP3_FOUILLE_PARSEUR_H
