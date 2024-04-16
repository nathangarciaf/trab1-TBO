#include "algorithm.h"
#include <stdio.h>
#include <stdlib.h>

void clustering(EdgeList *mst, PointList *pl, int k){
    for(int i = 0; i < edge_list_used(mst) - (k-1); i++){
        Edge *current_edge = edge_list_get(mst,i);
        int grp1 = point_group_find(edge_get_p1(current_edge), pl);
        int grp2 = point_group_find(edge_get_p2(current_edge), pl);
        //printf("PONTO %s DO GRUPO %d PESO %d\nPONTO %s DO GRUPO %d PESO %d\n",point_get_id(edge_get_p1(current_edge)), grp1, point_get_weight(edge_get_p1(current_edge)), point_get_id(edge_get_p2(current_edge)), grp2, point_get_weight(edge_get_p2(current_edge)));
        if(grp1 != grp2){
            point_union(edge_get_p1(current_edge),edge_get_p2(current_edge), pl);
        }
        //printf("PÓS AGRUPAMENTO:::\nPONTO %s DO GRUPO %d PESO %d\nPONTO %s DO GRUPO %d PESO %d\n\n",point_get_id(edge_get_p1(current_edge)), point_group_find(edge_get_p1(current_edge), pl), point_get_weight(edge_get_p1(current_edge)), point_get_id(edge_get_p2(current_edge)), point_group_find(edge_get_p2(current_edge), pl), point_get_weight(edge_get_p2(current_edge)));
    }
}

void kruskal_algoritm(EdgeList *mst, EdgeList* el, PointList *pl){
    for(int i = 0; i < edge_list_used(el); i++){
        Edge *current_edge = edge_list_get(el, i);
        if(point_group_find(edge_get_p1(current_edge), pl) != point_group_find(edge_get_p2(current_edge), pl)){
            point_union(edge_get_p1(current_edge),edge_get_p2(current_edge), pl);
            edge_list_add(mst, current_edge);
        }
    }

    point_list_reset_groups_and_weight(pl);
}