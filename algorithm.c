#include "algorithm.h"
#include <stdio.h>
#include <stdlib.h>

void kruskal_algoritm(EdgeList *mst, EdgeList* el, int pl_size){
    //Vetor com os indices referentes aos pontos e seus respectivos grupos(ids[i] = grupo de i)
    int *ids = calloc(1,sizeof(int) * pl_size);
    //Vetor com os pesos de cada ponto(sizes[i] = peso da arvóre pendurada em i)
    int *sizes = calloc(1,sizeof(int) * pl_size);
    for(int i = 0; i < pl_size; i++){
        ids[i] = i;
        sizes[i] = 1;
    }

    for(int i = 0; i < edge_list_used(el); i++){
        Edge *current_edge = edge_list_get(el, i);
        int p = edge_get_p1(current_edge);
        int q = edge_get_p2(current_edge);
        if(find(ids, p) != find(ids, q)){
            unite(ids, sizes, p, q);
            edge_list_add(mst, current_edge);
        }
    }

    free(ids);
    free(sizes);
}

void clustering(EdgeList *mst, PointList *pl, int k){
    int pl_size = point_list_used(pl);
    //Vetor com os indices referentes aos pontos e seus respectivos grupos(ids[i] = grupo de i)
    int *ids = calloc(1,sizeof(int) * pl_size);
    //Vetor com os pesos de cada ponto(sizes[i] = peso da arvóre pendurada em i)
    int *sizes = calloc(1,sizeof(int) * pl_size);
    for(int i = 0; i < pl_size; i++){
        ids[i] = i;
        sizes[i] = 1;
    }

    for(int i = 0; i < edge_list_used(mst) - (k-1); i++){
        Edge *current_edge = edge_list_get(mst,i);
        int p = edge_get_p1(current_edge);
        int q = edge_get_p2(current_edge);

        if(find(ids, p) != find(ids, q)){
            unite(ids, sizes, p, q);
        }
    }

    //Atualiza os grupos na lista de pontos
    for(int i = 0; i < pl_size; i++){
        point_set_group(point_list_get(pl,i), find(ids,i));
    }

    free(ids);
    free(sizes);
}