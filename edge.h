#ifndef EDGE_H
#define EDGE_H

#include "point.h"

typedef struct Edge Edge;
typedef struct EdgeList EdgeList;
typedef struct Edge* EdgePointer;

Edge *edge_create();
int edge_get_p1(Edge *e);
int edge_get_p2(Edge *e);

EdgeList *edge_list_create(int n_points);
Edge *edge_list_get(EdgeList *el, int i);
void edge_list_add(EdgeList *el, Edge *e);
int edge_list_used(EdgeList *el);

void edge_weight_calculator(EdgeList *el, PointList *pl);

void edge_list_sort(EdgeList *el);
int edge_cmp(const void *edge1, const void *edge2);
int weight_cmp(double w1, double w2);

void edge_list_print(EdgeList *el);

void edge_list_free(EdgeList *el);
void mst_free(EdgeList *mst);

#endif