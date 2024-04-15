#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "edge.h"

void clustering(EdgeVec *mst, int mst_size, PointVec *pv, int pv_size, int k);
EdgeVec *kruskal_algoritm(EdgeVec *mst, int *mst_size, int *mst_tam, EdgeVec *ev, int ev_size, PointVec *pv, int pv_size);

#endif  