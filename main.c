#include "main.h"

int main()
{
    Heap *teste;
    int max = 0;
    Heap *aux = createUnit();
    int index[3] = {0, 0, 0};

    teste = createHeap(3);
    max = insertHeap(teste, max, index, 0, 0);
    max = insertHeap(teste, max, index, 1, 1);
    max = insertHeap(teste, max, index, 2, 2);
    printHeap(teste, max);
    max = removeHeap(teste, aux, max, index);
    printHeap(teste, max);
    return 0;
}