#include "parseur.h"
#include "testSet.h"
#include "trainingSet.h"

int main(){
    //Question parsing
    tabDoc * L = getInfos("BaseReuters-29",70703);
    printf("Creation oK\n");
    afficherAll(L);
    supprimerDoc(L);
    printf("Suppression ok\n");

    //Question découpage
    tabDoc* test = createTestSet(L);
    afficherAll(test);

    tabDoc* training = createTrainingSet(L);
    afficherAll(training);

    return 0;

}