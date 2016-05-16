#include <stdio.h> 
#include <stdlib.h>
#include "parseur.h"

int main(){
    //Question parsing
    tabDoc * L = getInfos("test.txt",8);
    afficherAll(L);

    //Question découpage

    return 0;

} 
