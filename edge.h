#ifndef EDGE_H
#define EDGE_H

#include "point.h"

typedef struct Edge Edge;
typedef struct Edge* EdgeVec;

EdgeVec *edge_vec_create(int tam);
EdgeVec *kruskal_algoritm();
int weight_cmp(double w1, double w2);
void edge_weight_calculator(EdgeVec *ev, PointVec *pv, int pv_size);
void edge_vec_sort(EdgeVec *ev, int size);
void edge_vec_free(EdgeVec *ev, int size);
void edge_vec_print(EdgeVec *ev, int size);

Edge *edge_create();

#endif