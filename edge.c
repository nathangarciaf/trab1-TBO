#include "edge.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Edge
{
    Point *p1, *p2;
    double weight;
};

EdgeVec *edge_vec_create(int tam){
    EdgeVec *ev = (EdgeVec*)calloc(1, sizeof(EdgeVec) * tam);
    return ev;
}

Edge *edge_create(){
    Edge *edge = (Edge*)calloc(1, sizeof(Edge));
    edge->p1 = NULL;
    edge->p2 = NULL;
    edge->weight = 0;
    return edge;
}

void edge_weight_calculator(EdgeVec *ev, PointVec *pv, int pv_size){
    int ev_idx = 0;
    for(int i = 0; i < pv_size; i++){
        for(int j = i + 1; j < pv_size ; j++){
            ev[ev_idx] = edge_create();
            ev[ev_idx]->weight = euclid_dist(pv[i], pv[j]);
            ev[ev_idx]->p1 = pv[i];
            ev[ev_idx]->p2 = pv[j];
            ev_idx++;
        }
    }
}

int weight_cmp(double w1, double w2){
    return w1 - w2;
}

void edge_vec_sort(EdgeVec *ev, int size){
    int (*double_cmp)(double,double) ;
    qsort(ev,(size_t)size,sizeof(Edge*),);
}

void edge_vec_print(EdgeVec *ev, int size){
    for(int i = 0; i < size; i++){
        if(!ev[i]){
            printf("CASA %d DO EV É NULA\n",i);
        }
        else{
            printf("DISTANCIA ENTRE %s & %s: %f\n",point_get_id(ev[i]->p1), point_get_id(ev[i]->p2), ev[i]->weight);
        }
    }
}

void edge_vec_free(EdgeVec *ev, int size){
    for(int i = 0; i < size; i++){
        free(ev[i]);
    }
    free(ev);
}