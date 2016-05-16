//
// Created by Ruimy Benjamin Mac on 14/05/2016.
//

#ifndef TP3_FOUILLE_PARSEUR_H
#define TP3_FOUILLE_PARSEUR_H


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
    Document * suiv;
    Word *queue;
};

typedef struct {
    Document * doc;
    int maxIndice;
    Document *queue;
}listDoc;

void ajouterMot(Document * d, int valeur, int nbr);
void ajouterDoc(listDoc * L, int categorie, Word * listWord);
listDoc * getInfos(char * FileName);
void afficherAll(listDoc * L);
void afficherDoc(Document * D);
void afficherMot(Word * w);
void supprimerMot(Document *d);
void supprimerDoc(listDoc *d);


#endif //TP3_FOUILLE_PARSEUR_H
