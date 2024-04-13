#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INIT_TAM 5

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
    printf("\n%d",p->dim);
    printf("\n\n");
}

void point_vec_free(PointVec *pv, int size){
    for(int i = 0; i < size; i++){
        point_free(pv[i]);
    }
    free(pv);
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

        pv[*size] = p;
        (*size)++;
    }

    free(entrada);
    fclose(f);
    return pv;
}