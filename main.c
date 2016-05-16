#include <stdio.h> 
#include <stdlib.h>
#include "parseur.h"

int main(){
    //Question parsing
    tabDoc * L = getInfos("test.txt",8);
    printf("Creation oK\n");
    afficherAll(L);
    supprimerDoc(L);
    printf("Suppression ok\n");

    //Question découpage


    return 0;

} 
