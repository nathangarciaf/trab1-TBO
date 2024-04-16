#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Point
{
    char *id;
    double *coord;
    int group, dim, coord_size, weight;
};

struct PointList
{
    PointPointer *points;
    int size, used;
};

Point *point_create(){
    Point *p = calloc(1, sizeof(Point));
    p->dim = 0;
    p->coord_size = 0;
    p->weight = 1;
    p->coord = NULL;
    p->id = NULL;
    return p;
}

PointList *point_list_create(){
    PointList *pl = calloc(1,sizeof(PointList));
    pl->size = INIT_TAM;
    pl->used = 0;
    pl->points = calloc(1,sizeof(PointPointer) * pl->size);
    return pl;
}

void point_add_id(Point *p, char* id){
    int len = strlen(id);
    p->id = (char*)calloc(1,sizeof(char) * (len+1));
    strcpy(p->id,id);
}

void point_add_coord(Point *p, char *value){
    if(p->coord == NULL){
        p->coord = (double*)calloc(1, sizeof(double) * INIT_TAM);
        p->coord_size = INIT_TAM;
    }

    if(p->coord_size == p->dim){
        p->coord = realloc(p->coord, sizeof(double) * (p->coord_size*2));
    }

    char *endptr;
    p->coord[p->dim] = strtod(value,&endptr);
    p->dim++;
}

Point *point_list_get_point(PointList *pl, int i){
    return pl->points[i];
}

int point_list_used(PointList *pl){
    return pl->used;
}

//p1->dim = p2->dim = dim
double euclid_dist(Point *p1, Point *p2){
    int dim = p1->dim;
    double sum = 0;
    for(int i = 0; i < dim; i++){
        sum += ((p1->coord[i] - p2->coord[i]) * (p1->coord[i] - p2->coord[i])); 
    }
    return sqrt(sum);
}

void print_groups(PointList *pl, int k){
    //Cria vetor para a checagem de grupos
    int *check = (int*)calloc(1,k*sizeof(int));

    //Define todos os grupos iniciais como -1 para não haver conflitos
    for(int i = 0; i < k; i++){
        check[i] = -1;
    }

    int curr_group = -1, checked = 0, cont_group = 0;
    for(int i = 0; i < pl->used; i++){
        curr_group = point_group_find(pl->points[i], pl);

        //Verificar se o grupo do ponto atual ja foi impresso
        for(int j = 0; j < k; j++){
            if(check[j] == curr_group){
                checked = 1;
                break;
            }
        }

        if(checked == 1){
            checked = 0;
            continue;
        }


        //Caso o grupo nao tenha sido impresso, imprime os pontos do grupo
        int comma = 0;
        for(int j = 0; j < pl->used; j++){
            if(point_get_group(pl->points[j]) == curr_group){
                if(comma != 0){
                    printf(", ");
                }
                printf("%s",point_get_id(pl->points[j]));
                comma++;
            }
        }

        printf("\n");

        //insere o grupo no vetor de checagem
        check[cont_group] = curr_group;
        
        cont_group++;
    }

    free(check);
}

void print_groups_file(PointList *pl, int k, FILE *saida){
    //Cria vetor para a checagem de grupos
    int *check = (int*)calloc(1,k*sizeof(int));

    //Define todos os grupos iniciais como -1 para não haver conflitos
    for(int i = 0; i < k; i++){
        check[i] = -1;
    }

    int curr_group = -1, checked = 0, cont_group = 0;
    for(int i = 0; i < pl->used; i++){
        curr_group = point_group_find(pl->points[i], pl);

        //Verificar se o grupo do ponto atual ja foi impresso
        for(int j = 0; j < k; j++){
            if(check[j] == curr_group){
                checked = 1;
                break;
            }
        }
        if(checked){
            checked = 0;
            continue;
        }

        //Caso o grupo nao tenha sido impresso, imprime os pontos do grupo
        int comma = 0;
        for(int j = 0; j < pl->used; j++){
            if(point_get_group(pl->points[j]) == curr_group){
                if(comma != 0){
                    fprintf(saida,",");
                }
                fprintf(saida,"%s",point_get_id(pl->points[j]));
                comma++;
            }
        }

        fprintf(saida,"\n");

        //insere o grupo no vetor de checagem
        check[cont_group] = curr_group;
        
        cont_group++;
    }

    free(check);
}

void point_list_print(PointList *pl){
    for(int i = 0; i < pl->used; i++){
        point_print(pl->points[i]);
    }
}

void point_print(Point *p){
    printf("ID do PONTO: %s\n", p->id);
    printf("GRUPO: %d", p->group);
    printf("\n");
}

char *point_get_id(Point *p){
    return p->id;
}

void point_set_group(Point *p, int group){
    p->group = group;
}

void point_set_weight(Point *p, int weight){
    p->weight = weight;
}

int point_get_weight(Point *p){
    return p->weight;
}

int point_get_group(Point *p){
    return p->group;
}

void point_list_reset_groups_and_weight(PointList *pl){
    for(int i = 0; i < pl->used; i++){
        point_set_group(pl->points[i], i);
        point_set_weight(pl->points[i], 1);
    }
}

int point_list_search(PointList *pl, Point *p){
    for(int i = 0; i < pl->used; i++){
        if(pl->points[i] == p){
            return i;
        }
    }
    return -1;
}

int point_vec_search(Point *p, PointPointer *pv, int pv_size){
    for(int i = 0; i < pv_size; i++){
        if(pv[i] == p){
            return i;
        }
    }
    return -1;
}

int point_group_find(Point *p, PointList *pl){
    int group = point_get_group(p);
    int point_idx = point_list_search(pl, p);

    while(point_idx != group){
        int curr_group = point_get_group(pl->points[group]);
        point_set_group(pl->points[point_idx], curr_group);
        point_idx = curr_group;
        group = point_get_group(pl->points[point_idx]);
    }
    return group;
}

int point_cmp(const void *point1, const void *point2){
    const Point *p1 = *(const PointPointer*)(point1);
    const Point *p2 = *(const PointPointer*)(point2);
    return strcmp(p1->id,p2->id);
}


void point_list_sort(PointList *pl){
    qsort(pl->points, pl->used, sizeof(PointPointer), point_cmp);
}


void point_union(Point *p1, Point *p2, PointList *pl){
    int group1 = point_group_find(p1, pl);
    int group2 = point_group_find(p2, pl);
    if(group1 == group2){
        return;
    }

    Point *p1_father = point_list_get_point(pl, group1);
    Point *p2_father = point_list_get_point(pl, group2);

    //printf("DENTRO DO AGRUPAMENTO::\nPESO DE %s: %d\nPESO DE %s: %d\n",p1->id,p1->weight, p2->id, p2->weight);
    if(p1_father->weight < p2_father->weight){
        point_set_group(pl->points[group1], group2);
        p2_father->weight += p1_father->weight;
    }
    else{
        point_set_group(pl->points[group2], group1);
        p1_father->weight += p2_father->weight;
    }
}

void point_free(Point *p){
    if(p->coord != NULL)
        free(p->coord);
    if(p->id != NULL)
        free(p->id);
    free(p);
}

void point_list_free(PointList *pl){
    for(int i = 0; i < pl->used; i++){
        point_free(pl->points[i]);
    }
    free(pl->points);
    free(pl);
}

PointList *points_reader(PointList *pl, FILE *f){
    char *entrada = NULL;
    size_t size_t = 0;

    int len = getline(&entrada, &size_t, f);
    while(len > 0){
        int cont = 0;
        char *subs = strtok(entrada,",");
        Point *p = point_create();
        while(subs){
            if(cont == 0){
                point_add_id(p,subs);
            }
            else{
                point_add_coord(p,subs);
            }
            cont++;
            subs = strtok(NULL, ",");
        }
        len = getline(&entrada, &size_t, f);

        if(pl->size == pl->used){
            pl->size *= 2;
            pl->points = realloc(pl->points, sizeof(PointPointer)*pl->size);
        }

        p->group = pl->used;
        pl->points[pl->used] = p;
        pl->used++;
    }

    free(entrada);
    fclose(f);
    return pl;
}