#include "edge.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Edge
{
    int p1, p2;
    double weight;
};

struct EdgeList
{
    EdgePointer *edges;
    int size, used;
};

EdgeList *edge_list_create(int n_points){
    EdgeList *el = calloc(1,sizeof(EdgeList));
    el->used = 0;
    //O tamanho da matriz triangular inferior (número maximo de arestas para n x n pontos) é a fórmula abaixo, sendo n = n_points 
    el->size = ((n_points * n_points) / 2) - (n_points/2);
    el->edges = calloc(1, sizeof(EdgePointer)*el->size);
    return el;
}

Edge *edge_create(){
    Edge *edge = (Edge*)calloc(1, sizeof(Edge));
    edge->p1 = -1;
    edge->p2 = -1;
    edge->weight = 0;
    return edge;
}

int edge_get_p1(Edge *e){
    return e->p1;
}

int edge_get_p2(Edge *e){
    return e->p2;
}

Edge *edge_list_get(EdgeList *el, int i){
    return el->edges[i];
}

int edge_list_used(EdgeList *el){
    return el->used;
}

void edge_list_add(EdgeList *el, Edge *e){
    el->edges[el->used] = e;
    el->used++;
}

void edge_weight_calculator(EdgeList *el, PointList *pl){
    int pl_size = point_list_used(pl);
    for(int i = 0; i < pl_size; i++){
        for(int j = i + 1; j < pl_size; j++){
            Edge *e = edge_create();
            e->weight = euclid_dist(pl, i, j);
            e->p1 = i;
            e->p2 = j;
            edge_list_add(el, e);
        }
    }
}

int edge_cmp(const void *edge1, const void *edge2){
    const Edge *e1 = *(const EdgePointer*)(edge1);
    const Edge *e2 = *(const EdgePointer*)(edge2);
    return weight_cmp(e1->weight,e2->weight);
}

int weight_cmp(double w1, double w2){
    if(w1 > w2){
        return 1;
    }
    else if(w1 < w2){
        return -1;
    }
    else{
        return 0;
    }
    return 0;
}

void edge_list_sort(EdgeList *el){
    qsort(el->edges, el->used, sizeof(Edge*),edge_cmp);
}

void edge_list_free(EdgeList *el){
    for(int i = 0; i < el->used; i++){
        free(el->edges[i]);
    }
    free(el->edges);
    free(el);
}

//Função espécifica pois a MST não possui arestas próprias, apenas os endereços das arestas da EdgeList principal
void mst_free(EdgeList *mst){
    free(mst->edges);
    free(mst);
}