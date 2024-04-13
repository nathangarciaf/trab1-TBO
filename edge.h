#ifndef EDGE_H
#define EDGE_H

#include "point.h"

typedef struct Edge Edge;
typedef struct Edge* EdgeVec;

EdgeVec *edge_vec_create(int tam);
Edge *edge_create();
void edge_weight_calculator(EdgeVec *ev, PointVec *pv, int pv_size);
void edge_vec_free(EdgeVec *ev, int size);
void print_ev(EdgeVec *ev, int size);

#endif