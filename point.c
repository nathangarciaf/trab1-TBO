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

PointVec *point_vec_create(int *size, int *tam){
    PointVec *pv = (PointVec*)calloc(1,sizeof(PointVec) * INIT_TAM);
    *tam = INIT_TAM;
    *size = 0;
    return pv;
}

Point *point_create(){
    Point *p = calloc(1, sizeof(Point));
    p->dim = 0;
    p->coord_size = 0;
    p->coord = NULL;
    p->id = NULL;
    return p;
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

//p1->dim = p2->dim = dim
double euclid_dist(Point *p1, Point *p2){
    int dim = p1->dim;
    double sum = 0;
    for(int i = 0; i < dim; i++){
        sum += ((p1->coord[i] - p2->coord[i]) * (p1->coord[i] - p2->coord[i])); 
    }
    return sqrt(sum);
}

void point_vec_print(PointVec *pv, int size){
    for(int i = 0; i < size; i++){
        point_print(pv[i]);
    }
}

void point_print(Point *p){
    printf("ID do PONTO: %s\nCOORDENADAS DO PONTO: ", p->id);
    for(int i = 0; i < p->dim; i++){
        printf("%.4f  ", p->coord[i]);
    }
    printf("\nDIM: %d E GRUPO: %d",p->dim, p->group);
    printf("\n\n");
}

void point_vec_free(PointVec *pv, int size){
    for(int i = 0; i < size; i++){
        point_free(pv[i]);
    }
    free(pv);
}

char *point_get_id(Point *p){
    return p->id;
}

int point_get_group(Point *p){
    return p->group;
}

int point_vec_search(Point *p, PointVec *pv, int pv_size){
    for(int i = 0; i < pv_size; i++){
        if(pv[i] == p){
            return i;
        }
    }
    return -1;
}

int point_group_find(Point *p, PointVec *pv, int pv_size, int *height){
    int group = point_get_group(p);
    int point_idx = point_vec_search(p, pv, pv_size);

    while(point_idx != group){
        point_idx = pv[point_idx]->group = point_get_group(pv[group]);
        group = point_get_group(pv[point_idx]);
        (*height)++;
    }
    return group;
}

void point_union(Point *p1, Point *p2, PointVec *pv, int pv_size){
    int h1 = 0;
    int group1 = point_group_find(p1, pv, pv_size, &h1);
    int h2 = 0;
    int group2 = point_group_find(p2, pv, pv_size, &h2);
    if(group1 == group2){
        return;
    }
    if(h1 < h2){
        pv[group1]->group = group2;
    }
    else{
        pv[group2]->group = group1;
    }
}

void point_free(Point *p){
    if(p->coord != NULL)
        free(p->coord);
    if(p->id != NULL)
        free(p->id);
    free(p);
}

PointVec * points_reader(PointVec *pv, int *size, int *tam, FILE *f){
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

        if(*size == *tam){
            *tam *= 2;
            pv = realloc(pv, sizeof(PointVec) * (*tam));
        }

        p->group = *size;
        pv[*size] = p;
        (*size)++;
    }

    free(entrada);
    fclose(f);
    return pv;
}