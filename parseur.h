//
// Created by Ruimy Benjamin Mac on 14/05/2016.
//

#ifndef TP3_FOUILLE_PARSEUR_H
#define TP3_FOUILLE_PARSEUR_H

typedef struct {
    int value;
    int nbrAppearance;
}Word;

typedef struct{
    int categorie;
    Word *listWord;
}Document;




#endif //TP3_FOUILLE_PARSEUR_H
