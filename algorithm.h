#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "edge.h"
#include "union.h"

void kruskal_algoritm(EdgeList *mst, EdgeList* el, int pl_size);
void group_designation(EdgeList *mst, PointList *pl,int k);

#endif  