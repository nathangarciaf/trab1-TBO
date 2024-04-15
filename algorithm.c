#include "algorithm.h"
#include <stdio.h>
#include <stdlib.h>

void clustering(EdgeVec *mst, int mst_size, PointVec *pv, int pv_size, int k){
    for(int i = 0; i < mst_size - (k-1); i++){
        Edge *current_edge = mst[i];
        int h = 0; //Variável não utilizada, porém necessaria para a funcionalidade da função. Essa variável é util no caso do union
        if(point_group_find(edge_get_p1(current_edge), pv, pv_size, &h) != point_group_find(edge_get_p2(current_edge), pv, pv_size, &h)){
            point_union(edge_get_p1(current_edge),edge_get_p2(current_edge), pv, pv_size);
        }
    }
}

EdgeVec *kruskal_algoritm(EdgeVec *mst, int *mst_size, int *mst_tam, EdgeVec *ev, int ev_size, PointVec *pv, int pv_size){
    for(int i = 0; i < ev_size; i++){
        Edge *current_edge = ev[i];
        int h = 0; //Variável não utilizada, porém necessaria para a funcionalidade da função. Essa variável é util no caso do union
        if(point_group_find(edge_get_p1(current_edge), pv, pv_size, &h) != point_group_find(edge_get_p2(current_edge), pv, pv_size, &h)){
            if(*mst_size == *mst_tam){
                *mst_tam *= 2;
                mst = realloc(mst,sizeof(EdgeVec*) * (*mst_tam));
            }
            mst[*mst_size] = current_edge;
            point_union(edge_get_p1(current_edge),edge_get_p2(current_edge), pv, pv_size);
            (*mst_size)++;
        }
    }

    point_vec_reset_groups(pv, pv_size);
    return mst;
}