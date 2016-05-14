#include <stdio.h> 
#include <stdlib.h>
#include "parseur.h"

int main(){

    printf("LOURD");
    listDoc * L = getInfos("test.txt");
    afficherAll(L);
    return 0; 
} 
