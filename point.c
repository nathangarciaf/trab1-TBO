#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INIT_TAM 2

struct Point
{
    char *id;
    float *coord;
    int group, dim, coord_size;
};

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
    if(!p->coord){
        p->coord = (float*)calloc(1, sizeof(float) * INIT_TAM);
        p->coord_size = INIT_TAM;
    }
    else{
        if(p->coord_size == p->dim){
            p->coord = (float*)realloc(p->coord, sizeof(float) * (p->coord_size*2));
        }
    }
    p->coord[p->dim] = atof(value);
    p->dim++;
}

void point_print(Point *p){
    printf("ID do PONTO: %s\nCOORDENADAS DO PONTO: ", p->id);
    for(int i = 0; i < p->dim; i++){
        printf("%.4f  ", p->coord[i]);
    }
    printf("\n\n");
}

void point_free(Point *p){
    if(p->coord != NULL)
        free(p->coord);
    if(p->id != NULL)
        free(p->id);
    free(p);
}