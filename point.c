#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Point
{
    char *id;
    double *coord;
    int group, dim, coord_size;
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

void point_set_id(Point *p, char* id){
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

Point *point_list_get(PointList *pl, int i){
    return pl->points[i];
}

int point_list_used(PointList *pl){
    return pl->used;
}

double euclid_dist(PointList *pl, int p1, int p2){
    Point *point1 = pl->points[p1];
    Point *point2 = pl->points[p2];

    //p1->dim = p2->dim = dim
    int dim = point1->dim;
    double sum = 0;
    for(int i = 0; i < dim; i++){
        sum += ((point1->coord[i] - point2->coord[i]) * (point1->coord[i] - point2->coord[i])); 
    }
    return sqrt(sum);
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
        Point *p = point_list_get(pl, i);
        curr_group = p->group;

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
            Point *q = point_list_get(pl, j);
            if(q->group == curr_group){
                if(comma != 0){
                    fprintf(saida,",");
                }
                fprintf(saida,"%s",q->id);
                comma++;
            }
        }
        fprintf(saida,"\n");

        //insere o grupo no vetor de checagem
        check[cont_group] = curr_group;
        cont_group++;
    }
    free(check);
    fclose(saida);
}

void point_list_print(PointList *pl){
    for(int i = 0; i < pl->used; i++){
        Point *p = point_list_get(pl, i);
        printf("%d - ID do PONTO: %s\n", i, p->id);
        printf("GRUPO: %d", p->group);
        printf("\n");
    }
}

void point_set_group(Point *p, int group){
    p->group = group;
}

int point_cmp(const void *point1, const void *point2){
    const Point *p1 = *(const PointPointer*)(point1);
    const Point *p2 = *(const PointPointer*)(point2);
    return strcmp(p1->id,p2->id);
}

void point_list_sort(PointList *pl){
    qsort(pl->points, pl->used, sizeof(PointPointer), point_cmp);
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
                point_set_id(p,subs);
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