#include <stdio.h> 
#include <stdlib.h> 

int main(){

    FILE* monfichier=NULL; 
    monfichier = fopen("test.txt", "r+"); 
    if (monfichier != NULL)
    {
        //On peut lire et écrire dans le fichier
            fprintf(monfichier,"J'aime le C ..."); 
        fclose(monfichier); 
    }
    else
    {
        printf("Impossible d'ouvrir le fichier test.txt\n");
    }
    return 0; 
} 
