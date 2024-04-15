#ifndef EDGE_H
#define EDGE_H

#include "point.h"

typedef struct Edge Edge;
typedef struct Edge* EdgePointer;

EdgePointer *edge_vec_create(int tam);
int weight_cmp(double w1, double w2);
void edge_weight_calculator(EdgePointer *ev, PointVec *pv, int pv_size);
void edge_vec_sort(EdgePointer *ev, int size);
void edge_vec_free(EdgePointer *ev, int size);
void edge_vec_print(EdgePointer *ev, int size);

Edge *edge_create();
Point *edge_get_p1(Edge *e);
Point *edge_get_p2(Edge *e);

#endif