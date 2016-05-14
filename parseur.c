//
// Created by Ruimy Benjamin Mac on 14/05/2016.
//

#include <stdio.h>
#include <stdlib.h>
#include "parseur.h"

int fill(char * FileName){
    FILE* myFile = NULL;
    myFile = fopen(FileName, "r+");
    if (myFile != NULL)
    {
        //On peut lire et écrire dans le fichier
        fprintf(myFile,"J'aime le C ...");
        fclose(myFile);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier test.txt\n");
    }
    return 0;
}

