#include <stdio.h>
#include "union.h"

//Todos os algoritmos a seguir do UF são referentes ao algoritmo com: Weighted QU + path compression

int find(int *ids, int i){
    while (i != ids[i]) {
        ids[i] = ids[ids[i]];
        i = ids[i];
    }
    return i;
}

void unite(int *ids, int *sizes, int p, int q){
    int i = find(ids, p);
    int j = find(ids, q);
    if(i == j){
        return;
    }

    if(sizes[i] < sizes[j]){
        ids[i] = j;
        sizes[j] += sizes[i];
    }
    else{
        ids[j] = i;
        sizes[i] += sizes[j];
    }
}
