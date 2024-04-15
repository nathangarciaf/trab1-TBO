#include "algorithm.h"
#include <stdio.h>
#include <stdlib.h>

void clustering(EdgeList *mst, PointList *pl, int k){
    for(int i = 0; i < edge_list_used(mst) - (k-1); i++){
        Edge *current_edge = edge_list_get(mst,i);
        if(point_group_find(edge_get_p1(current_edge), pl, NULL) != point_group_find(edge_get_p2(current_edge), pl, NULL)){
            point_union(edge_get_p1(current_edge),edge_get_p2(current_edge), pl);
        }
    }
}

void kruskal_algoritm(EdgeList *mst, EdgeList* el, PointList *pl){
    for(int i = 0; i < edge_list_used(el); i++){
        Edge *current_edge = edge_list_get(el, i);
        if(point_group_find(edge_get_p1(current_edge), pl, NULL) != point_group_find(edge_get_p2(current_edge), pl, NULL)){
            edge_list_add(mst, current_edge);
            point_union(edge_get_p1(current_edge),edge_get_p2(current_edge), pl);
        }
    }

    point_list_reset_groups(pl);
}