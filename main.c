#include "parseur.h"
#include "testSet.h"
#include "trainingSet.h"

int main(){
    //Question parsing
    tabDoc * L = getInfos("test.txt",8);
    afficherAll(L);
    supprimerDoc(L);

    //Question découpage
    tabDoc* test = createTestSet(L);
    afficherAll(test);

    tabDoc* training = createTrainingSet(L);
    afficherAll(training);

    return 0;

} 
