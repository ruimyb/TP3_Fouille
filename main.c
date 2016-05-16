#include <stdio.h> 
#include <stdlib.h>
#include "parseur.h"

int main(){

    tabDoc * L = getInfos("test.txt",8);
    afficherAll(L);
    supprimerDoc(L);
    return 0; 
} 
