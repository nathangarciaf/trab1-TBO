#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "edge.h"

void kruskal_algoritm(EdgeList *mst, EdgeList* el, PointList *pl);

void clustering(EdgeList *mst, PointList *pl, int k);

#endif  