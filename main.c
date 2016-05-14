#include <stdio.h> 
#include <stdlib.h>
#include "parseur.h"

int main(){

    listDoc * L = getInfos("test.txt");
    afficherAll(L);
    return 0; 
} 
